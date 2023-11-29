#pragma once

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

#include <fstream>

#include "Struct.h"



/* Audioクラス */
class Audio {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void BeginFrame();


private: // メンバ関数



private: // メンバ変数

	ComPtr<IXAudio2> xAudio2_ = nullptr;
	IXAudio2MasteringVoice* masterVoice_;

};