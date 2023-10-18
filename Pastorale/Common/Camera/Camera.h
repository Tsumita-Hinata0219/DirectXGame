#pragma once
#include "WorldTransform.h"
#include "Function.h"
#include "WinApp.h"


class Camera {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


public:

	Matrix4x4 transformationMatrixData_;


	WorldTransform cameraTransform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-5.0f},
	};

private:

	int32_t ClientWidth_;
	int32_t ClientHeight_;


	WorldTransform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};



	Matrix4x4 worldMatrix_;
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;
	
};