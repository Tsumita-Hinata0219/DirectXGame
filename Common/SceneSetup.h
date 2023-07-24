#pragma once
#include "Function.h"
#include "WorldTransform.h"


class SceneSetup {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const int32_t Width, const int32_t Height, Transform cameraTransform);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ワールドビュー投影行列
	/// </summary>
	Matrix4x4 WorldViewProjectionMatrixFanc(Matrix4x4 matrixTransform);

	/// <summary>
	/// アクセッサ
	/// </summary>
	Matrix4x4 GetWorldViewProjectionMatrix() { return worldViewProjectionMatrix_; };



private:

	int32_t Width_;
	int32_t Height_;

	// カメラのTransform変数
	Transform cameraTransform_;

	Matrix4x4 worldMatrix_;
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;

};

