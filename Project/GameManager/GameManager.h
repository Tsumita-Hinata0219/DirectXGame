#pragma once

#include "IScene.h"
#include "DebugScene.h"


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
	void ChangeSceneState();

private:

	IScene* Scene_ = nullptr;

};