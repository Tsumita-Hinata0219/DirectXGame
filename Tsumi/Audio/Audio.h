#pragma once

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

#include <fstream>
#include <cassert>

#include "Struct.h"



// チャンクヘッダ
struct ChunkHeader {
	char ID[4];	  // チャンク毎のID
	int32_t size; // チャンクサイズ
};
// RIFFヘッダチャンク
struct RiffHeader {
	ChunkHeader chunk; // "RIFF"
	char type[4];	   // "WAVE"
};
// FMTチャンク
struct FormatChunk {
	ChunkHeader chunk; // "fmt"
	WAVEFORMATEX fmt;  // 波形フォーマット
};
// 音声データ
struct SoundData {
	WAVEFORMATEX wfex;		 // 波形フォーマット
	BYTE* pBuffer;			 // バッファの先頭アドレス
	unsigned int bufferSize; // バッファのサイズ
};


/* Audioクラス */
class Audio {

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Audio* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 音声データの解放
	/// </summary>
	static void Finalize();

	/// <summary>
	/// Soundデータを読み込む
	/// </summary>
	static uint32_t LoadSound(const std::string& filePath);

	/// <summary>
	/// サウンド再生
	/// </summary>
	static void PlayOnSound(uint32_t soundDataNum);

	/// <summary>
	/// サウンド停止
	/// </summary>
	static void StopOnSound(uint32_t soundDataNum);

	/// <summary>
	/// 音声データの解放
	/// </summary>
	static void SoundUnload();


private: // メンバ変数

	ComPtr<IXAudio2> xAudio2_ = nullptr;
	IXAudio2MasteringVoice* masterVoice_;

	static const uint32_t kSoundDataMax_ = 5;
	IXAudio2SourceVoice* pSourceVoice_[kSoundDataMax_]{};
	SoundData soundData_[kSoundDataMax_]{};
	uint32_t soundDataNum_;

};