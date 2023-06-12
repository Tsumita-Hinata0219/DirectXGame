#include "WinApp.h"


/// <summary>
/// ウィンドウプロシージャ
/// </summary>
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg,
	WPARAM wparam, LPARAM lparam) {

	// メッセージが来てたら最優先で処理させる
	switch (msg)
	{
	// ウィンドウが破棄された
	case WM_DESTROY:

		// OSに対して、アプリ終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準メッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



/// <summary>
/// コンストラクタ
/// </summary>
WinApp::WinApp() {}



/// <summary>
/// デストラクタ
/// </summary>
WinApp::~WinApp() {}



/// <summary>
/// 初期化
/// </summary>
void WinApp::Initialize(const wchar_t* title, int32_t ClientWidth, int32_t ClientHeight) {

	this->title_ = title;
	this->ClientWidth_ = ClientWidth;
	this->ClientHeight_ = ClientHeight;


	/* --- ウィンドウクラスを登録する --- */

	// ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	// ウィンドウクラス名(なんでも良い)
	wc_.lpszClassName = L"%s", title_;
	// インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	// カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// ウィンドウクラスを登録する
	RegisterClass(&wc_);



	/* --- ウィンドウサイズを決める --- */

	// クライアント領域のサイズ
	RECT wrc = { 0, 0, ClientWidth_, ClientHeight_ };

	// クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);



	/* --- ウィンドウを生成して表示 --- */

	//ウィンドウの生成
	hwnd_ = CreateWindow(

		wc_.lpszClassName,     //利用するクラス名
		title_,				   //タイトルバーの文字(なんでも良い)
		WS_OVERLAPPEDWINDOW,   //欲見るウィンドウスタイル
		CW_USEDEFAULT,		   //表示X座標(Windowsに任せる)
		CW_USEDEFAULT,		   //表示X座標(WindowsOSに任せる)
		wrc.right - wrc.left,  //ウィンドウ横幅
		wrc.bottom - wrc.top,  //ウィンドウ縦幅
		nullptr,			   //親ウィンドウハンドル
		nullptr,			   //メニューハンドル
		wc_.hInstance,		   //インスタンスハンドル
		nullptr);			   //オプション


	//ウィンドウを表示する
	ShowWindow(hwnd_, SW_SHOW);
}



