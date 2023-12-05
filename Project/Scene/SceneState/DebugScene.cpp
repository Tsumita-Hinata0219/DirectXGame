#include "DebugScene.h"



/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {

	Audio::SoundUnload();
}



/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize() {


	texture1_ = TextureManager::LoadTexture("uvChecker.png");
	texture2_ = TextureManager::LoadTexture("monsterBall.png");
	texture3_ = TextureManager::LoadTexture("uvChecker.png");

	sound1_ = Audio::LoadSound("mokugyo.wav");
	sound2_ = Audio::LoadSound("kakkoii.wav");
	sound3_ = Audio::LoadSound("mokugyo.wav");
}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state) {


	if (Input::PressKeys(DIK_S)) {

		if (Input::TriggerKey(DIK_1)) {
			Audio::PlayOnSound(sound1_, true, 1.0f);
		}
		
		if (Input::TriggerKey(DIK_2)) {
			Audio::PlayOnSound(sound2_, false, 1.0f);
		}
		
		if (Input::TriggerKey(DIK_3)) {
			Audio::PlayOnSound(sound3_, false, 1.0f);
		}
	}

	if (Input::TriggerKey(DIK_RETURN)) {
		Audio::StopOnSound(sound1_);
		Audio::StopOnSound(sound2_);
		Audio::StopOnSound(sound3_);
	}


#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw() {


}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw() {


}