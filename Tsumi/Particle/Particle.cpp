#include "Particle.h"



// 初期化処理
void Particle::Initialize(IParticleState* state, uint32_t instanceNum) {

	// テクスチャの初期設定
	this->useTexture_ = 1;

	// インスタンス数
	instanceNum_ = instanceNum;

	// ステートパターンの初期化処理
	this->state_ = state;
	state_->Initialize(this);
}


// 描画処理
void Particle::Draw(ViewProjection view) {

	state_->Draw(this, particlePropes_, view);
}


// リストの登録
void Particle::PushBackParticles(ParticleProperties prope) {

	particlePropes_.push_back(prope);
}