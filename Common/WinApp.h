#pragma once
#include "Function.h"
#include "imgui.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


class WinApp
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const wchar_t* title, int32_t ClientWidth, int32_t ClientHeight);


	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	static LRESULT WindowProc(
		HWND hwnd, 
		UINT msg,
		WPARAM wparam, 
		LPARAM lparam);


	/// <summary>
	/// ゲームウィンドウの作成
	/// </summary>
	void CreateGameWindow();


	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>終了かどうか</returns>
	bool ProcessMessage();


	/// <summary>
	/// ウィンドウハンドルの取得
	/// </summary>
	/// <returns></returns>
	HWND GetHwnd() const { return hwnd_; };


private: // メンバ変数

	// タイトルバー
	const wchar_t* title_;

	// クライアントサイズ
	int32_t ClientWidth_;
	int32_t ClientHeight_;
	
	// メッセージ
	MSG msg{};

	// ウィンドウクラス
	WNDCLASS wc_{};

	// ウィンドウハンドル
	HWND hwnd_ = nullptr;

};
