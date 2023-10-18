#include "Pastorale.h"



/// <summary>
/// コンストラク
/// </summary>
Pastorale::Pastorale() {

	// 生成
	model_ = new Model();
}



/// <summary>
/// デストラクタ
/// </summary>
Pastorale::~Pastorale() {

	// 解放処理
	delete model_;
}



/// <summary>
/// 初期化処理
/// </summary>
void Pastorale::Initialize() {

	// TextureManagerの初期化処理
	TextureManager::Initialize();

	// Modelの初期化処理
	model_->Initialize();
}

