#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "ImGuiManager.h"



class Triangle {

public:

	Triangle();
	~Triangle();


	void Initialize();

	void Update();

	void Draw3D(Matrix4x4& ViewMatrix);

	void Draw2D();

private:

	// TriangleModelの生成
	Model* modelPlane_ = nullptr;
	WorldTransform modelPlaneTransform_;

	// Spriteの生成
	Sprite* sprite_ = nullptr;
	WorldTransform spriteTransform_{};
	UVTransform uvTransform_{};

	// Sphereの生成
	Model* modelSphere_ = nullptr;
	WorldTransform modelSphereTransform_{};
	DirectionalLight light_{};


	uint32_t texhandle1_;
	uint32_t texhandle2_;
	uint32_t texhandle3_;
	uint32_t texhandle4_;
	bool useTex_;
};