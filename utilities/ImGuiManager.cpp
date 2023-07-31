#include "ImGuiManager.h"


void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(
		dxCommon->GetDevice(),
		dxCommon->GetSwapChainDesc().BufferCount,
		dxCommon->GetRtvDesc().Format,
		dxCommon->GetSrvDescriptorHeap(),
		dxCommon->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		dxCommon->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
}


void ImGuiManager::Update() {

}


void ImGuiManager::Draw() {

}



void ImGuiManager::BeginFrame() {

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}




void ImGuiManager::EndFrame() {
	ImGui::Render();
}