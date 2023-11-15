#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include <d3d12.h>
#include <wrl.h>
#include "WinApp.h"
#include "Function.h"


/* ビュープロジェクション変換データ */
struct ViewProjection {

	// X, Y, Z軸周りのローカル回転軸
	Vector3 rotate = { 0.0f, 0.0f, 0.0f };

	// ローカル座標
	Vector3 translate = { 0.0f, 0.0f, 0.0f };

	// ワールド -> ビュー変換行列
	Matrix4x4 matView{};

	// ビュー -> プロジェクション変換行列
	Matrix4x4 matProjection{};

	// 垂直方向視野角
	float fov = 0.45f;

	// ビューポートのアスペクト比
	float aspectRatio = float(WinApp::GetClientWidth()) / float(WinApp::GetCliendHeight());

	// 深度限界 (手前側)
	float nearZ = 0.1f;

	// 深度限界 (奥側)
	float farZ = 1000.0f;



	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void UpdateMatrix();

};