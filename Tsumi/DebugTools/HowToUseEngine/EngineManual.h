#pragma once

#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"


/* EngineManualクラス */
class EngineManual {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EngineManual() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EngineManual() { Audio::SoundUnload(); }

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw(ViewProjection view);

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw(ViewProjection view);

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw(ViewProjection view);


private: // メンバ関数

	/// <summary>
	/// Audioに関する処理まとめたやつ
	/// </summary>
	void AudioUpdate();

private: // メンバ変数

	// PlaneModel
	std::unique_ptr<Model> planeModel_ = nullptr;
	WorldTransform planeModelTransform_{};

	// ObjModel
	std::unique_ptr<Model> objModel_ = nullptr;
	WorldTransform objModelTransform_{};

	// Sprite
	std::unique_ptr<Sprite> spriteA_ = nullptr;
	WorldTransform spriteATransform_{};
	UVTransform uvTransformA_{};

	std::unique_ptr<Sprite> spriteB_ = nullptr;
	WorldTransform spriteBTransform_{};
	UVTransform uvTransformB_{};

	// texHandle
	uint32_t uvCheckerHD_;
	uint32_t monsterBallHD_;
	uint32_t asanohaHD_;
	uint32_t skyHD_;

	// SoundHandle
	uint32_t mokugyoHD_;
	uint32_t kakkoiiHD_;
};
