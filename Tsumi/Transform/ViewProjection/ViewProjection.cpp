#include "ViewProjection.h"



/// <summary>
/// 初期化処理
/// </summary>
void ViewProjection::Initialize(Vector3 initRotate, Vector3 initTranslate) {

	rotate = initRotate;
	translate = initTranslate;
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