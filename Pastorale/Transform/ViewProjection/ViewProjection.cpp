#include "ViewProjection.h"



/// <summary>
/// 初期化処理
/// </summary>
void ViewProjection::Initialize() {

	rotate = { 0.0f, 0.0f, 0.0f };
	translate = { 0.0f, 0.0f, 0.0f };
}



/// <summary>
/// 更新処理
/// </summary>
void ViewProjection::UpdateMatrix() {

	Matrix4x4 translateMat = MakeTranslateMatrix(translate);
	Matrix4x4 rotateMat = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	matView = Multiply(Inverse(translateMat), Inverse(rotateMat));
	matProjection = MakePerspectiveFovMatrix(fov, aspectRatio, nearZ, farZ);
}