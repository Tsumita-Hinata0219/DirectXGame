#include "WorldTransform.h"



// 更新処理
void Transform::AffineMatrix() {

	// スケール、回転、並列移動を合成して行列を計算する
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translation_);

}

