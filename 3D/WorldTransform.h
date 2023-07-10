#pragma once
#include "Function.h"


/// <summary>
/// ワールド変換データ
/// </summary>
struct WorldTransform {

	// ローカルスケール
	Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
	// X,Y,Z軸回りのローカル回転軸
	Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
	// ローカル座標
	Vector3 translation_ = { 0.0f, 0.0f, 0.0f };

	// ローカル -> ワールド変換行列
	Matrix4x4 worldMatrix_;



	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void AffineMatrix();

};
