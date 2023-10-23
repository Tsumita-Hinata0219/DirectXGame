#include "GraphicPipelineManager.h"


/// <summary>
/// PSOクラスのインスタンス取得
/// </summary>
GraphicPipelineManager* GraphicPipelineManager::GetInstance() {

	static GraphicPipelineManager instance;
	return &instance;
}



/// <summary>
/// 初期化処理
/// </summary>
void GraphicPipelineManager::Initialize() {

	NormalGraphicPipeline::SetNormalPso();
	SpriteGraphicPipeline::SetSpritePso();
	LightGraphicPipeline::SetLightPso();
}


