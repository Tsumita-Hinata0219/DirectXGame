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


void ImGuiManager::BeginFrame(DirectXCommon* dXcommon) {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ID3D12DescriptorHeap* descriptorHeap[] = { dXcommon->GetsrvDescriptorHeap() };
	dXcommon->GetCommandList()->SetDescriptorHeaps(1, descriptorHeap);
}


void ImGuiManager::EndFrame(DirectXCommon* dXcommon) {
	ImGui::Render();

	//実際のCommandListのImGuiの描画コマンドを進む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dXcommon->GetCommandList());
}

