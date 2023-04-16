#include <Windows.h>

#include <cstdint>

#include <string>
#include <format>


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



//string  -> wstring
std::wstring ConvertString(const std::string& str);


//wstring -> string
std::string ConvertString(const std::wstring& str);



/* ---出力ウィンドウに文字を出す--- */
void Log(const std::string& message) {
	OutputDebugStringA(message.c_str());
}



//Windowsアプリでエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");



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
	//int32_tを使うためにincludeを追加　#include <cstdint>

	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;


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

	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);



	MSG msg{};



	///// -----メインループ----- /////
	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		//Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			//ゲームの処理



		}
	}


	return 0;
}







/* -----プロトタイプ宣言----- */

//string  -> wstring
std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

//wstring -> string
std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}