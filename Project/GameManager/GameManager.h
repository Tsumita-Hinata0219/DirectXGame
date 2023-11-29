#pragma once

#include "Tsumi.h"
#include "WinApp.h"

#include "IScene.h"
#include "DebugScene.h"
#include "GameScene.h"
#include "Input.h"


/* GameManagerクラス */
class GameManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameManager();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Run();

	/// <summary>
	/// シーンチェンジ
	/// </summary>
	void ChangeSceneState(IScene* newScene);

private:

	IScene* Scene_ = nullptr;

};