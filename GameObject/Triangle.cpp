#include "Triangle.h"



/// <summary>
/// 初期化処理
/// </summary>
void Triangle::Initialize(Pastorale* pastorale){

	pastorale_ = pastorale;

	pastorale_->GetATextureManager()->LoadTexture("Resources/uvChecker.png");


	// 三角形の各要素を決める
	// Left Top Right Color
	element_ = {
		{ -0.5f, -0.5f, 0.0f, 1.0f},
		{0.0f, 0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
	};
	// SRT
	transform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
}



/// <summary>
/// 更新処理
/// </summary>
void Triangle::Update(Matrix4x4& ViewMatrix){

	pastorale_->GetModel()->Update(element_, transform_, ViewMatrix);
}



/// <summary>
/// 描画処理
/// </summary>
void Triangle::Draw() {

	pastorale_->GetModel()->Draw(pastorale_->GetATextureManager());
}


