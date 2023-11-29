#include "Audio.h"



/// <summary>
/// インスタンスの取得
/// </summary>
Audio* Audio::GetInstance() {
	static Audio instance;
	return &instance;
}



/// <summary>
/// 初期化処理
/// </summary>
void Audio::Initialize() {

	// XAudio2エンジンのインスタンス生成
	HRESULT result = XAudio2Create(&Audio::GetInstance()->xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));

	// マスターボイス生成
	result = Audio::GetInstance()->xAudio2_->CreateMasteringVoice(&Audio::GetInstance()->masterVoice_);
	assert(SUCCEEDED(result));
}


/// <summary>
/// 音声データの解放
/// </summary>
void Audio::Finalize() {

	Audio::GetInstance()->xAudio2_.Reset();
}



/// <summary>
/// Soundデータを読み込む
/// </summary>
uint32_t Audio::LoadSound(const std::string& filePath) {

	HRESULT result{};
	Audio::GetInstance()->soundDataNum_++;

	/* 1. ファイルオープン */

	// ファイルの入力ストリームのインスタンス
	std::ifstream file("Resources/Audio/" + filePath + ".wav");
	// .wavファイルをバイナリーモードで開く
	file.open(filePath, std::ios_base::binary);
	// ファイルオープン失敗を検出する
	assert(file.is_open());



	/* 2. wavデータ読み込み */

	// RIFFヘッダーの読み込み
	RiffHeader riff{};
	file.read((char*)&riff, sizeof(riff));

	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.ID, "RIFF", 4) != 0) {
		assert(0);
	}
	// タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format{};

	// チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.ID, "fmt", 4) != 0) {
		assert(0);
	}

	// チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Dataチャンクの読み込み
	ChunkHeader data{};
	file.read((char*)&data, sizeof(data));

	// JUNKチャンクを検出した場合
	if (strncmp(data.ID, "JUNK", 4) == 0) {

		// 読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		// 再読み込み
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.ID, "data", 4) != 0) {
		assert(0);
	}

	// Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);



	/* 3. ファイルクローズ */

	file.close();



	/* 4. 読み込んだ音声データをreturn */

	// returnするための音声データ
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataNum_].wfex = format.fmt;
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataNum_].pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataNum_].bufferSize = data.size;

	return Audio::GetInstance()->soundDataNum_;
}


/// <summary>
/// サウンド再生
/// </summary>
void Audio::PlayOnSound(uint32_t soundDataNum) {

	HRESULT result{};

	// 波形フォーマットをもとにSoundVoiceの生成
	result = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->pSourceVoice_[soundDataNum], 
		&Audio::GetInstance()->soundData_[soundDataNum].wfex);
	assert(SUCCEEDED(result));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = Audio::GetInstance()->soundData_[soundDataNum].pBuffer;
	buf.AudioBytes = Audio::GetInstance()->soundData_[soundDataNum].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// 波形データの再生
	result = Audio::GetInstance()->pSourceVoice_[soundDataNum]->SubmitSourceBuffer(&buf);
	result = Audio::GetInstance()->pSourceVoice_[soundDataNum]->Start();
}


/// <summary>
/// サウンド停止
/// </summary>
void Audio::StopOnSound(uint32_t soundDataNum) {

	HRESULT result{};
	
	result = Audio::GetInstance()->pSourceVoice_[soundDataNum]->Stop();

	assert(SUCCEEDED(result));
}


/// <summary>
/// 音声データの解放
/// </summary>
void Audio::SoundUnload() {

	// バッファのメモリ解放
	for (int i = Audio::GetInstance()->soundDataNum_; i > 0; i--) {

		delete[] Audio::GetInstance()->soundData_[i].pBuffer;
		Audio::GetInstance()->soundData_[i].pBuffer = 0;
		Audio::GetInstance()->soundData_[i].bufferSize = 0;
		Audio::GetInstance()->soundData_->wfex = {};
	}
}