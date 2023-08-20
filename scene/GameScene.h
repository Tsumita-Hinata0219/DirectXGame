#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "Camera.h"
#include "ImGuiManager.h"
#include "Transform.h"
#include "TextureManager.h"


class GameScene {

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const wchar_t* title, const int32_t Width, const int32_t Height);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


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

	// WinAppの生成
	WinApp* winApp_ = nullptr;
	// DirectXCommonの生成
	DirectXCommon* dXCommon_ = nullptr;
	// Modelの生成
	Model* model_ = nullptr;
	// Cameraの生成
	Camera* camera_ = nullptr;
	//　ImGuiの生成
	ImGuiManager* imguiManager_ = nullptr;
	// TextureManagerの生成
	TextureManager* textureManager_ = nullptr;

	// Triangle
	Triangle element_{};
	Transform triangleTransform_{};

};