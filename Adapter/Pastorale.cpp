#include "Pastorale.h"



/// <summary>
/// コンストラク
/// </summary>
Pastorale::Pastorale(){

	// 生成
	model_ = new Model();
	textureManager_ = new TextureManager();
}



/// <summary>
/// デストラクタ
/// </summary>
Pastorale::~Pastorale(){

	// 解放処理
	delete model_;
	delete textureManager_;
}



/// <summary>
/// 初期化処理
/// </summary>
void Pastorale::Initialize(DirectXCommon* dXCommon){

	dXCommon_ = dXCommon;

	// TextureManagerの初期化処理
	textureManager_->Initialize(dXCommon_);

	// Modelの初期化処理
	model_->Initialize(dXCommon_);
}



/// <summary>
/// 更新処理
/// </summary>
void Pastorale::Update(){}



/// <summary>
/// 描画処理
/// </summary>
void Pastorale::Draw(){}



/// <summary>
/// テクスチャファイルを読み込む
/// </summary>
void Pastorale::Loadtexture(const std::string& filePath){

	textureManager_->LoadTexture(filePath);
}

