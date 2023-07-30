#pragma once
#include "Matrix4x4.h"
#include "Transform.h"
#include "Function.h"


class Camera {

public:

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(int32_t ClientWidth_, int32_t ClientHeight_);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();


public:

	Matrix4x4 transformationMatrixData_;

private:

	int32_t ClientWidth_;
	int32_t ClientHeight_;


	Transform cameraTransform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-5.0f},
	};
	Transform transform{
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