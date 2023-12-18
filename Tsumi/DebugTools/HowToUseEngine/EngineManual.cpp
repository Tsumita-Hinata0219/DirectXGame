#include "EngineManual.h"



/// <summary>
/// デストラクタ
/// </summary>
EngineManual::~EngineManual() {

	Audio::SoundUnload();
}


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


	// スプライト
	spriteA_ = std::make_unique<Sprite>();
	spriteA_->Initialize({ 0.0f, 0.0f }, { 640.0f, 360.0f });
	spriteA_->SetTextureHandle(uvCheckerHD_);
	spriteATransform_.Initialize();
	uvTransformA_ = {
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};

	spriteB_ = std::make_unique<Sprite>();
	spriteB_->Initialize({ 0.0f, 0.0f }, { 1280.0f, 720.0f });
	spriteB_->SetTextureHandle(skyHD_);
	spriteBTransform_.Initialize();
	uvTransformB_ = {
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};


	// Planeモデル
	planeModel_ = make_unique<Model>();
	planeModel_->Initialize(new ModelPlaneState);
	planeModelTransform_.Initialize();
	planeModel_->SetTexHandle(uvCheckerHD_);
	planeModelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
	planeModel_->SetColor(planeModelColor_);


	// Objモデル
	objModel1_ = make_unique<Model>();
	objModel1_->CreateFromObj("axis", objModelTransform1_);
	objModelTransform1_.Initialize();

	objModel2_ = make_unique<Model>();
	objModel2_->CreateFromObj("plane", objModelTransform2_);
	objModelTransform2_.Initialize();

	objModel3_ = make_unique<Model>();
	objModel3_->CreateFromObj("axis", objModelTransform3_);
	objModelTransform3_.Initialize();

}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update() {

	AudioUpdate();

	spriteA_->SetUVTransform(uvTransformA_);
	spriteB_->SetUVTransform(uvTransformA_);

	planeModelTransform_.UpdateMatrix();
	objModelTransform1_.UpdateMatrix();
	objModelTransform2_.UpdateMatrix();
	objModelTransform3_.UpdateMatrix();
	spriteATransform_.UpdateMatrix();
	spriteBTransform_.UpdateMatrix();

	planeModel_->SetColor(planeModelColor_);


#ifdef _DEBUG

	ImGui::Begin("EngineManual");
	ImGui::Text("AxisObj");
	ImGui::DragFloat3("Axis.Scele", &objModelTransform1_.scale.x, 0.01f);
	ImGui::DragFloat3("Axis.Rotate", &objModelTransform2_.rotate.x, 0.01f);
	ImGui::DragFloat3("Axis.Transform", &objModelTransform1_.translate.x, 0.01f);
	ImGui::Text("SpriteA");
	ImGui::DragFloat3("spriteAScale", &spriteATransform_.scale.x, 0.1f);
	ImGui::DragFloat3("spriteARotate", &spriteATransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("spriteATranslate", &spriteATransform_.translate.x, 0.1f);
	ImGui::DragFloat2("uvScaleA", &uvTransformA_.scale.x, 0.01f);
	ImGui::DragFloat("uvRotateA", &uvTransformA_.rotate.z, 0.01f);
	ImGui::DragFloat2("uvTranslateA", &uvTransformA_.translate.x, 0.01f);
	ImGui::Text("SpriteB");
	ImGui::DragFloat3("spriteBScale", &spriteBTransform_.scale.x, 0.1f);
	ImGui::DragFloat3("spriteBRotate", &spriteBTransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("spriteBTranslate", &spriteBTransform_.translate.x, 0.1f);
	ImGui::DragFloat2("uvScaleB", &uvTransformB_.scale.x, 0.01f);
	ImGui::DragFloat("uvRotateB", &uvTransformB_.rotate.z, 0.01f);
	ImGui::DragFloat2("uvTranslateB", &uvTransformB_.translate.x, 0.01f);
	ImGui::Text("PlaneModel");
	ImGui::DragFloat3("PlaneModelScale", &planeModelTransform_.scale.x, 0.1f);
	ImGui::DragFloat3("PlaneModelRotate", &planeModelTransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("PlaneModelTranslate", &planeModelTransform_.translate.x, 0.1f);
	ImGui::DragFloat4("PlaneModelColor", &planeModelColor_.x, 0.01f);
	ImGui::ColorEdit4("PlaneModelColor", &planeModelColor_.x);
	ImGui::End();

#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) {

	//spriteB_->Draw(skyHD_, spriteBTransform_, view);

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) {

	planeModel_->Draw(planeModelTransform_, view);
	//objModel1_->Draw(objModelTransform1_, view);
	//objModel2_->Draw(objModelTransform2_, view);
	//objModel3_->Draw(objModelTransform3_, view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) {

	spriteA_->Draw(uvCheckerHD_, spriteATransform_, view);
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