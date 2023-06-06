#pragma once
#include "Function.h"


class WinApp
{
public:

	/// <summary>
	/// インストラクタ
	/// </summary>
	WinApp(const wchar_t* title, int32_t kClientWidth, int32_t kClientHeight);


	/// <summary>
	/// デストラクタ
	/// </summary>
	~WinApp();


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
		WPARAM wparam, LPARAM lparam);


	/// <summary>
	/// アクセッサ
	/// </summary>
	/// <returns></returns>
	int32_t GetkClientWidth() const { return kClientWidth_; };
	int32_t GetkClientHeight() const { return kClientHeight_; };
	HWND GetHwnd() const { return hwnd_; };


private:

	int32_t kClientWidth_;
	int32_t kClientHeight_;
	const wchar_t* title_;

	MSG msg{};

	WNDCLASS wc_{};
	HWND hwnd_;

};
