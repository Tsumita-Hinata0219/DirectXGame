#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"

#include "Camera/RailCamera/RailCamera.h"
#include "DebugCamera.h"
#include "Player/Player.h"
#include "EnemyManager/EnemyManager.h"
#include "Skydome/Skydome.h"
#include "Ground/Ground.h"
#include "Count/Count.h"
#include "Sousa/Sousa.h"

#include "CollisionManager.h"


/* GameSceneクラス */
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


	/// <summary>
	/// プレイヤーバレットを追加する
	/// </summary>
	void AddPlayerBulletList(PlayerBullet* playerBullet) { playerBulelts_.push_back(playerBullet); }

	/// <summary>
	/// エネミーを追加する
	/// </summary>
	void AddEnemyList(Enemy* enemy) { enemys_.push_back(enemy); }

	/// <summary>
	/// エネミーバレットを追加する
	/// </summary>
	void AddEnemyBulletList(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }


private:

	/// <summary>
	/// プレイヤー更新処理
	/// </summary>
	void PlayerUpdate();

	/// <summary>
	/// エネミー更新処理
	/// </summary>
	void EnemyUpdate();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CheckAllCollision();


private:

	// ビュープロジェクション
	ViewProjection viewProjection_{};
	// デバッグカメラ有効フラグ
	bool isDebugCaneraActive_ = false;


	/* ----- DebugCamera デバッグカメラ ----- */
	unique_ptr<DebugCamera> debugCamera_ = nullptr;


	/* ----- RailCamera レールカメラ ----- */
	unique_ptr<RailCamera> railCamera_ = nullptr;


	/* ----- Player プレイヤー ----- */
	unique_ptr<Player> player_ = nullptr;
	std::list<PlayerBullet*> playerBulelts_{};


	/* ----- Enemy エネミー ----- */
	unique_ptr<EnemyManager> enemyManager_ = {};
	std::list<Enemy*> enemys_{};
	std::list<EnemyBullet*> enemyBullets_{};

	/* ----- Count カウント ----- */
	unique_ptr<Count> count_ = nullptr;

	/* ----- CollisionManager コリジョンマネージャー ----- */
	unique_ptr<CollisionManager> collisionManager_ = nullptr;
};

