#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"


class ImGuiManager
{
public:

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Update();

	void Draw();

	void BeginFrame();

	void EndFrame();

private:


};