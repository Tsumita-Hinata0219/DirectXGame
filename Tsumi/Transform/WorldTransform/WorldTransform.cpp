#include "WorldTransform.h"



// 初期化処理
void WorldTransform::Initialize() {

	CreateBuffer();
	matWorld = MakeIdentity4x4();
	UpdateMatrix();
}

// 更新処理
void WorldTransform::UpdateMatrix() {

	// スケール、回転、並列移動を合成して行列を計算する
	matWorld = MakeAffineMatrix(scale, rotate, translate);

	// 親があれば親のワールド行列を掛ける
	if (parent) {
		matWorld = Multiply(matWorld, parent->matWorld);
	}

	TransferMatrix();
}

// ワールド座標の取得
Vector3 WorldTransform::GetWorldPos() {

	Vector3 worldPos{};

	worldPos = {
		.x = matWorld.m[3][0],
		.y = matWorld.m[3][1],
		.z = matWorld.m[3][2],
	};

	return worldPos;
}

// 親子関係を結ぶ
void WorldTransform::SetParent(const WorldTransform* parentTransform) {
	parent = parentTransform;
}

// 定数バッファの生成
void WorldTransform::CreateBuffer() {

	CreateResource::CreateBufferResource(sizeof(TransformationMatrix), constBuffer);

	// constBuffer が nullptr の場合はエラーログを出力してアサーションでプログラムを停止させる
	if (!constBuffer) {
		assert(false && "Failed to create constBuffer.");
	}
}

// マッピングする
void WorldTransform::Map() {

	// constBuffer が nullptr の場合はエラーハンドリング
	if (!constBuffer) {
		// エラーログなどを出力するか、適切な対処を行う
		// この例ではエラーログを出力し、アサーションでプログラムを停止させる
		assert(false && "constBuff_ is nullptr. Make sure to create constBuffer before calling Map.");
		return;
	}

	HRESULT result = constBuffer->Map(0, nullptr, reinterpret_cast<void**>(&buffMap));
	assert(SUCCEEDED(result));
}

// マッピング終了
void WorldTransform::UnMap() {

	constBuffer->Unmap(0, nullptr);
}

// 行列の計算・転送
void WorldTransform::TransferMatrix() {

	Map();
	buffMap->WVP = matWorld;
	buffMap->World = matWorld;
	UnMap();
}