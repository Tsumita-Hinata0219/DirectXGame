#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "Pastorale.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "Sphere.h"



class Triangle {

public:

	Triangle();
	~Triangle();


	void Initialize(Pastorale* pastorale);

	void Update();

	void Draw3D(Matrix4x4& ViewMatrix);

	void Draw2D();

private:

	// Pastoraleの生成
	Pastorale* pastorale_ = nullptr;

	// Modelの生成
	Model* model_ = nullptr;
	TriangleElement modelElement_{};
	WorldTransform modelTransform_;

	// Spriteの生成
	Sprite* sprite_ = nullptr;
	WorldTransform spriteTransform_;
	SpriteData vertex_;

	// Sphereの生成
	Sphere* sphere_ = nullptr;
	WorldTransform sphereTransform_;


	uint32_t texhandle1_;
	uint32_t texhandle2_;
	uint32_t texhandle3_;
	uint32_t texhandle4_;
	bool useTex_;
};