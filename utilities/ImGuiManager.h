#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class ImGuiManager {

public:

	void Initialize(WinApp* winApp, DirectXCommon* dXcommon);

	void BeginFrame(DirectXCommon* dXcommon);
	void EndFrame(DirectXCommon* dXcommon);
};