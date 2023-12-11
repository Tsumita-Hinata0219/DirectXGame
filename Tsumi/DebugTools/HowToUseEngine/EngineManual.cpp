#include "EngineManual.h"



/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize() {

	// テクスチャの読み込み
	uvCheckerHD_ = TextureManager::LoadTexture("uvChecker.png");
	monsterBallHD_ = TextureManager::LoadTexture("monsterBall.png");
	asanohaHD_ = TextureManager::LoadTexture("asanoha.png");
	skyHD_ = TextureManager::LoadTexture("sky.png");


	// サウンドの読み込み
	mokugyoHD_ = Audio::LoadSound("mokugyo.wav");
	kakkoiiHD_ = Audio::LoadSound("kakkoii.wav");

	// 平面モデル
	//planeModel_ = std::make_unique<Model>();
	//planeModel_->Initialize(new ModelPlaneState());
	//planeModelTransform_ = {
	//	{1.0f, 1.0f, 1.0f},
	//	{0.0f, 0.0f, 0.0f},
	//	{0.0f, -1.0f, 0.0f},
	//};


	// スプライト
	/*sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize({ 0.0f, 0.0f }, { 640.0f, 360.0f });
	sprite_->SetTextureHandle(uvCheckerHD_);
	spriteTransform_ = {
		.scale = {1.0f, 1.0f, 1.0f},
		.rotate = {0.0f, 0.0f, 0.0f},
		.translate = {0.0f, 0.0f, 0.0f},
	};*/


	// Objモデル
	objModel_->CreateFromObj("axis");
	objModelTransform_ = {
		{1.0f, 1.0f, 1.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, -2.0f, 10.0f},
	};
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update() {

	AudioUpdate();

	planeModelTransform_.UpdateMatrix();
	objModelTransform_.UpdateMatrix();
	spriteTransform_.UpdateMatrix();
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw() {



}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) {

	view;
	//planeModel_->Draw(planeModelTransform_, view);
	objModel_->Draw(objModelTransform_, view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw() {

	//sprite_->Draw(spriteTransform_);
}


/// <summary>
/// Audioに関する処理まとめたやつ
/// </summary>
void EngineManual::AudioUpdate() {

	if (Input::PressKeys(DIK_B)) {

		if (Input::TriggerKey(DIK_1)) {
			Audio::PlayOnSound(mokugyoHD_, true, 1.0f);
		}

		if (Input::TriggerKey(DIK_2)) {
			Audio::PlayOnSound(mokugyoHD_, false, 1.0f);
		}

		if (Input::TriggerKey(DIK_3)) {
			Audio::PlayOnSound(kakkoiiHD_, false, 1.0f);
		}
	}
	if (Input::PressKeys(DIK_S)) {

		if (Input::TriggerKey(DIK_1)) {
			Audio::StopOnSound(mokugyoHD_);
		}

		if (Input::TriggerKey(DIK_2)) {
			Audio::StopOnSound(kakkoiiHD_);
		}
	}


#ifdef _DEBUG


	ImGui::Begin("Audio");

	ImGui::Text("mokugyo : B + 1 -> Loop");
	ImGui::Text("          B + 2 -> nonLoop");
	if (Audio::IsPlaying(mokugyoHD_)) {
		ImGui::Text("mokugyo_isPlaying : true");
	}
	else {
		ImGui::Text("mokugyo_isPlaying : false");
	}

	ImGui::Text("\nkakkoii : B + 3 -> nonLoop");
	if (Audio::IsPlaying(kakkoiiHD_)) {
		ImGui::Text("nkakkoii_isPlaying : true");
	}
	else {
		ImGui::Text("nkakkoii_isPlaying : false");
	}
	ImGui::End();

#endif // _DEBUG
}