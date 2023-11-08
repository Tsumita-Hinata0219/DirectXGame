#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "NormalGraphicPipeline.h"
#include "CreateResource.h"
#include "IModelState.h"



/* ModelPlaneクラス */
class ModelSphereState : public IModelState {

public: // メンバ関数

	ModelSphereState() {};
	~ModelSphereState() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform, Matrix4x4& viewMatrix) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(uint32_t texture);


private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// 分割数
	int32_t subdivision_ = 16;
};