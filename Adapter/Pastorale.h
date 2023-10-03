#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "TextureManager.h"


//Pastorale//パストラーレ
//PASTORALE ENGINE

class Pastorale {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	Pastorale();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Pastorale();


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(DirectXCommon* dXCommon);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


	/// <summary>
	/// テクスチャファイルを読み込む
	/// </summary>
	void Loadtexture(const std::string& filePath1, const std::string& filePath2);



	/// <summary>
	/// アクセッサ 取得
	/// </summary>
	Model* GetModel() { return model_; }
	TextureManager* GetATextureManager() { return textureManager_; }



private:

	// DirectXCommonの生成
	DirectXCommon* dXCommon_ = nullptr;
	// Modelの生成
	Model* model_ = nullptr;
	// TextureManagerの生成
	TextureManager* textureManager_ = nullptr;


};

