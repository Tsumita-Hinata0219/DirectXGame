#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <wrl.h>
using Microsoft::WRL::ComPtr;
using namespace std;

#include <vector>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <iostream>
#include <cstdint>
#include <WorldTransform.h>



// 頂点データ
struct VertexData {
	Vector4 position;
	Vector2 texCoord;
	Vector3 normal;
};


// スプライト構造体
struct SpriteData {
	Vector4 topLeft;
	Vector4 bottomLeft;
	Vector4 topRight;
	Vector4 bottomRight;
};


// uvTransform
struct UVTransform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};



// 球
struct SphereData {
	Vector3 center;
	float radius;
};


// マテリアル
struct Material {
	Vector4 color;
	int32_t enableLightting;
};
struct MaterialSprite {
	Vector4 color;
	Matrix4x4 uvTransform;
};
struct MaterialParticle {
	Vector4 color;
	Matrix4x4 uvTransform;
};


// マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
};


// モデルデータ
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};


// 平行光源
struct DirectionalLight {
	Vector4 color;     // ライトの色
	Vector3 direction; // ライトの向き
	float intensity;   // 輝度
};


// CompileShader
struct CompileShaders {
	IDxcBlobEncoding* Source;
	DxcBuffer SourceBuffer{};
	IDxcResult* Result;
	IDxcBlobUtf8* Error;
	IDxcBlob* Blob;
};


// Objデータ
struct ObjData {
	uint32_t index;
	uint32_t textureHD;
	ComPtr<ID3D12Resource> resource;
	vector<VertexData> vertices;
	MaterialData material;
};
