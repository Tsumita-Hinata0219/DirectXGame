#pragma once

#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"


/* EngineManualクラス */
class EngineManual {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理3D
	/// </summary>
	void Draw3D(ViewProjection view);

	/// <summary>
	/// 描画処理2D
	/// </summary>
	void Draw2D();


private: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EngineManual() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EngineManual() {};


private: // メンバ変数

	// PlaneModel
	std::unique_ptr<Model> planeModel_ = nullptr;
	WorldTransform planeModelTransform_{};


	// ObjModel
	std::unique_ptr<Model> objModel_ = nullptr;
	WorldTransform objModelTransform_{};

	// Sprite
	std::unique_ptr<Sprite> sprite_ = nullptr;
	WorldTransform spriteTransform_{};

	// texHandle
	uint32_t texHD1_;
	uint32_t texHD2_;
	uint32_t texHD3_;
	uint32_t texHD4_;

};
