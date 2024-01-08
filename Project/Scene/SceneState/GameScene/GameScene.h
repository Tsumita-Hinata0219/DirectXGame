#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"

#include "Player/Player.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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


	/// <summary>
	/// 自弾を追加する
	/// </summary>
	/// <param name="playerBullet">自弾</param>
	void AddPlayerBullet(PlayerBullet* playerBullet) { playerBulelts_.push_back(playerBullet); }


private:

	/// <summary>
	/// プレイヤー更新処理
	/// </summary>
	void PlayerUpdate();


private:

	ViewProjection viewProjection_{};


	/* ----- Player 自キャラ ----- */
	unique_ptr<Player> player_ = nullptr;
	std::list<PlayerBullet*> playerBulelts_{};
};

