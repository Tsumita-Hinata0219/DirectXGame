#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class ImGuiManager {

public:

	void Initialize(DirectXCommon* dXcommon);

	void BeginFrame(DirectXCommon* dXcommon);
	void EndFrame(DirectXCommon* dXcommon);
};