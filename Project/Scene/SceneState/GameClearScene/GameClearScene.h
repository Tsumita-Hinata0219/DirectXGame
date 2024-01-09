#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"

#include "Skydome/Skydome.h"
#include "Ground/Ground.h"

/* TitleSceneクラス */
class GameClearScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameClearScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClearScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* Scene) override;

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


private:

	// ビュープロジェクション
	ViewProjection viewProjection_{};


	XINPUT_STATE joyState_{};
};