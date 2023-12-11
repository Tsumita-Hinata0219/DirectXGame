#include "WorldTransform.h"



// 初期化処理
void WorldTransform::Initialize() {

	matWorld = MakeIdentity4x4();

}

// 更新処理
void WorldTransform::UpdateMatrix() {

	// スケール、回転、並列移動を合成して行列を計算する
	matWorld = MakeAffineMatrix(scale, rotate, translate);

	// 親があれば親のワールド行列を掛ける
	if (parent) {
		matWorld = Multiply(matWorld, parent->matWorld);
	}

}

