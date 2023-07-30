#pragma once

#include <Windows.h>

#include <cstdint>
#include <string>
#include <format>
#include <cassert>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <wrl.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")


// string->wstring
std::wstring ConverString(const std::string& str);

// wstring->string
std::string ConvertString(const std::wstring& str);

// wstring->string
void Log(const std::string& message);

// 
Matrix4x4 MakeIdentity4x4();



// Scale
Matrix4x4 MakeScaleMatrix(const Vector3 scale);


// Rotate(X,Y,Z)
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);


// Multiply
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);


// Rotate(all)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);


// Translate
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);


// AffineMatrix (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

