#pragma once
#include "Function.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "NormalGraphicPipeline.h"
#include "CreateResource.h"
#include "IModelState.h"
#include "DescriptorManager.h"



/* ModelPlaneクラス */
class ModelPlaneState : public IModelState {

public: // メンバ関数

	ModelPlaneState() {};
	~ModelPlaneState() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform, ViewProjection view) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(uint32_t texture, WorldTransform worldTransform, ViewProjection view);


private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// サイズ
	float size_;
};