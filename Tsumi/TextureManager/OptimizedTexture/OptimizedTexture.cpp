#include "OptimizedTexture.h"



/// <summary>
/// コンストラクタ
/// </summary>
OptimizedTexture::OptimizedTexture(std::string filePath, TexData texData) {

	filePath_ = filePath;
	texData_ = texData;
}



/// <summary>
/// デストラクタ
/// </summary>
OptimizedTexture::~OptimizedTexture() {

	TexRelese();
}