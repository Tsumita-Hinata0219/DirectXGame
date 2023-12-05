#pragma once

#include "IScene.h"
#include "GameManager.h"


class DebugScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DebugScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* state) override;

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw() override;

	
private:

	uint32_t texture1_;
	uint32_t texture2_;
	uint32_t texture3_;

	uint32_t sound1_;
	uint32_t sound2_;
	uint32_t sound3_;

};