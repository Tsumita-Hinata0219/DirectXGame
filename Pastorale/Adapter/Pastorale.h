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
	void Initialize();


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() {};


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() {};


	/// <summary>
	/// アクセッサ 取得
	/// </summary>
	Model* GetModel() { return model_; }



private:

	// Modelの生成
	Model* model_ = nullptr;
};

