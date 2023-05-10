#include "WindowsClass.h"


void WindowsClass::Initialize() {



	//ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
		WPARAM wparam, LPARAM lparam) {

		//メッセージに応じてゲーム固有の処理を行う
		switch (msg) {
			//ウィンドウが破棄された
		case WM_DESTROY:
			//OSに対して、アプリの終了を伝える
			PostQuitMessage(0);
			return 0;
		}

		//標準のめっせーっじ処理を行う
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}



	/* ---ウィンドウクラスを登録する--- */
	WNDCLASS wc{};

	//ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;

	//ウィンドウクラス名(なんでも良い)
	wc.lpszClassName = L"CGWindowClass";

	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);

	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録する
	RegisterClass(&wc);




	/* ---ウィンドウサイズを決める--- */

	//クライアント領域 = ゲーム画面が映る領域
	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);



	//ウィンドウの生成
	HWND hwnd = CreateWindow(

		wc.lpszClassName,      //利用するクラス名
		L"CG2",				   //タイトルバーの文字(なんでも良い)
		WS_OVERLAPPEDWINDOW,   //欲見るウィンドウスタイル
		CW_USEDEFAULT,		   //表示X座標(Windowsに任せる)
		CW_USEDEFAULT,		   //表示X座標(WindowsOSに任せる)
		wrc.right - wrc.left,  //ウィンドウ横幅
		wrc.bottom - wrc.top,  //ウィンドウ縦幅
		nullptr,			   //親ウィンドウハンドル
		nullptr,			   //メニューハンドル
		wc.hInstance,		   //インスタンスハンドル
		nullptr);			   //オプション
	
}