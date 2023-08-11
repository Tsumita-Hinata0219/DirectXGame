#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class ImGuiManager {

public:

	void Initialize(WinApp* winApp, DirectXCommon* dXcommon);
	void Update();
	void Draw();

	void BeginFrame();
	void EndFrame();
};