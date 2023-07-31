#include "ImGuiManager.h"


void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dXcommon) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(
		dXcommon->GetDevice(), 
		dXcommon->GetSwapChainDesc().BufferCount,
		dXcommon->GetrtvDesc().Format,
		dXcommon->GetsrvDescriptorHeap(),
		dXcommon->GetsrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		dXcommon->GetsrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
}


void ImGuiManager::BeginFrame() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}


void ImGuiManager::EndFrame() {
	ImGui::Render();
}