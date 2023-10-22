﻿#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "Camera.h"
#include "ImGuiManager.h"
#include "WorldTransform.h"
#include "Pastorale.h"
#include "Triangle.h"
#include "Sprite.h"
#include "ShaderManager.h"


class GameScene {

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const wchar_t* title);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D();
	void Draw2D();


	/// <summary>
	/// メッセージの処理
	/// </summary>
	bool ProcessMessage();


	/// <summary>
	/// フレームの開始
	/// </summary>
	void BeginFrame();


	/// <summary>
	/// フレームの終了
	/// </summary>
	void EndFrame();


private:

	// Cameraの生成
	Camera* camera_ = nullptr;
	// Pastoraleの生成
	Pastorale* pastorale_ = nullptr;
	// Triangleの生成
	Triangle* triangle_ = nullptr;
	// Spriteの生成
	Sprite* sprite_ = nullptr;

	// Triangle
	TriangleElement element_{};
	WorldTransform triangleTransform_{};

};

