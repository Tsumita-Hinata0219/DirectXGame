#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Pastorale.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "Sphere.h"



class Triangle {

public:

	Triangle();
	~Triangle();


	void Initialize(Pastorale* pastorale, DirectXCommon* dXCommon);

	void Update(Matrix4x4& ViewMatrix);

	void Draw3D();

	void Draw2D();

private:

	// Pastoraleの生成
	Pastorale* pastorale_ = nullptr;

	// Modelの生成
	Model* model_ = nullptr;
	// Spriteの生成
	Sprite* sprite_ = nullptr;
	// TextureManagerの生成
	TextureManager* textureManager_ = nullptr;
	// Sphereの生成
	Sphere* sphere_ = nullptr;


	TriangleElement element_{};
	WorldTransform transform_;


	WorldTransform spriteTransform_;
	SpriteData vertex_;

	
	WorldTransform sphereTransform_;
	SphereData sphereElemnt_;


};