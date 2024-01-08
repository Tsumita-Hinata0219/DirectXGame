#include "RailCamera.h"



/// <summary>
/// 初期化処理
/// </summary>
void RailCamera::Initizlia() {

	worldTrans_.Initialize();
	worldTrans_.rotate = { 0.0f, 0.0f, 0.0f };
	worldTrans_.translate = { 0.0f, 0.0f, -50.0f };
	viewProjection_.Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void RailCamera::Update() {

	viewProjection_.rotate = worldTrans_.rotate;
	viewProjection_.translate = worldTrans_.translate;
	viewProjection_.matView = Inverse(worldTrans_.matWorld);

	worldTrans_.UpdateMatrix();
	viewProjection_.UpdateMatrix();


#ifdef _DEBUG

	ImGui::Begin("RailCemara");
	ImGui::DragFloat3("CameraRotate", &worldTrans_.rotate.x, 0.005f);
	ImGui::DragFloat3("CameraTranslate", &worldTrans_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG

}
