#pragma once
#include <Windows.h>
#include <cstdint>



class WindowsClass {

public:

	void Initialize();



public:

	//int32_tを使うためにincludeを追加　#include <cstdint>


	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720

};