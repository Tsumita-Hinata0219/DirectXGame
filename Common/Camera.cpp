#include "Camera.h"



// 初期化処理
void Camera::Initialize(int32_t ClientWidth, int32_t ClientHeight) {

	ClientWidth_ = ClientWidth;
	ClientHeight_ = ClientHeight;

	worldMatrix_ = MakeAffineMatrix(
		transform.scale, transform.rotate, transform.translate);

	cameraMatrix_ = MakeAffineMatrix(
		cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);

	viewMatrix_ = Inverse(cameraMatrix_);

	projectionMatrix_ = 
		MakePerspectiveFovMatrix(0.45f, float(ClientWidth_) / float(ClientHeight_), 0.1f, 100.0f);

	worldViewProjectionMatrix_ = Multiply(worldMatrix_, Multiply(viewMatrix_, projectionMatrix_));

	transformationMatrixData_ = worldViewProjectionMatrix_;
}



// 更新処理
void Camera::Update() {

	worldMatrix_ = MakeAffineMatrix(
		transform.scale, transform.rotate, transform.translate);

	cameraMatrix_ = MakeAffineMatrix(
		cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);

	viewMatrix_ = Inverse(cameraMatrix_);

	projectionMatrix_ =
		MakePerspectiveFovMatrix(0.45f, float(ClientWidth_) / float(ClientHeight_), 0.1f, 100.0f);

	worldViewProjectionMatrix_ = Multiply(worldMatrix_, Multiply(viewMatrix_, projectionMatrix_));

	transformationMatrixData_ = worldViewProjectionMatrix_;

}