#pragma once

#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "ImGuiManager.h"
#include "Particle.h"



/// <summary>
/// 寿命と死亡フラグをまとめた構造体
/// </summary>
struct MortalityInfo {
	int32_t kLifeTimer;
	int32_t Timer;
	bool IsAlive = false;
	bool IsDead = false;
};