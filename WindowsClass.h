#include <Windows.h>
#include <cstdint>
#include <string>


class WindowsClass
{
public:

	/// <summary>
	/// インストラクタ
	/// </summary>
	WindowsClass(const wchar_t* title, int32_t kClientWidth, int32_t kClientHeight);


	/// <summary>
	/// デストラクタ
	/// </summary>
	~WindowsClass();


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


private:

	int32_t kClientWidth_;
	int32_t kClientHeight_;
	const wchar_t* title_;

	WNDCLASS wc_{};
	HWND hwnd_;

};
