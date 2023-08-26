#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Pastorale.h"



class Triangle {

public:

	void Initialize(Pastorale* pastorale);

	void Update(Matrix4x4& ViewMatrix);

	void Draw();

private:

	// Pastoraleの生成
	Pastorale* pastorale_ = nullptr;

	// Modelの生成
	Model* model_ = nullptr;
	// TextureManagerの生成
	TextureManager* textureManager_ = nullptr;


	TriangleElement element_{};
	WorldTransform transform_;
};