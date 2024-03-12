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

	// Particle
	particle_ = make_unique<Particle>();
	particle_->Initialize(new ParticlePlane, NumInstance_);
	for (int i = 0; i < NumInstance_; i++) {

		particlePrope_[i].worldTransform.Initialize();
		particlePrope_[i].worldTransform.scale = {1.0f, 1.0f, 1.0f};
		particlePrope_[i].worldTransform.rotate = { 0.0f, 0.0f, 0.0f };
		particlePrope_[i].worldTransform.translate = {
			i * 0.1f,
			i * 0.1f ,
			i * 0.1f,
		};
		particlePrope_[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		particlePrope_[i].velocity = RandomGenerator::getRandom({ -1.0f, 1.0f }, { -1.0f, 1.0f }, { 0.0f, 0.0f });
		particlePrope_[i].uvTransform.scale = { 1.0f, 1.0f, 1.0f };
		particlePrope_[i].uvTransform.rotate = { 0.0f, 0.0f, 0.0f };
		particlePrope_[i].uvTransform.translate = { 0.0f, 0.0f, 0.0f };
		particlePrope_[i].isActive = true;

		particle_->PushBackParticles(particlePrope_[i]);
	}
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update() {

	AudioUpdate();

	for (int i = 0; i < NumInstance_; i++) {
		//particlePrope_[i].worldTransform.UpdateMatrix();
	}
	particle_->Update();

#ifdef _DEBUG

	ImGui::Begin("EngineManual");
	
	ImGui::End();

#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) {

	particle_->Draw(view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) {

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