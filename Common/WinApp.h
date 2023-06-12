#pragma once
#include "Function.h"


class WinApp
{
public:

	/// <summary>
	/// インストラクタ
	/// </summary>
	WinApp();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~WinApp();


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
	/// アクセッサ
	/// </summary>
	HWND GetHwnd() const { return hwnd_; };


private: // メンバ変数

	int32_t ClientWidth_;
	int32_t ClientHeight_;
	const wchar_t* title_;

	MSG msg{};

	WNDCLASS wc_{};

	HWND hwnd_ = nullptr;

};
