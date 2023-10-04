#include "SceneSetup.h"



// 初期化処理
void SceneSetup::Initialize(const int32_t Width, const int32_t Height, WorldTransform cameraTransform) {

	Width_ = Width;
	Height_ = Height;

	// Transform変数の初期化
	cameraTransform_ = {
		cameraTransform.scale_,
		cameraTransform.rotate_,
		cameraTransform.translation_,
	};

	// 透視変換行列
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(Width_) / float(Height_), 0.1f, 100.0f);
}



// 更新処理
void SceneSetup::Update() {

}



// ワールドビュー投影行列
Matrix4x4 SceneSetup::WorldViewProjectionMatrixFanc(Matrix4x4 matrixTransform) {

	cameraMatrix_ = MakeAffineMatrix(
		cameraTransform_.scale_, cameraTransform_.rotate_, cameraTransform_.translation_);

	viewMatrix_ = Inverse(cameraMatrix_);



	worldViewProjectionMatrix_ = Multiply(matrixTransform, Multiply(viewMatrix_, projectionMatrix_));

	return worldViewProjectionMatrix_;
}

