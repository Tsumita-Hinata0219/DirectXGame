﻿#pragma once

#include <Windows.h>

#include <cstdint>
#include <string>
#include <format>
#include <cassert>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <wrl.h>

#include "Vector4.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")


// string->wstring
std::wstring ConverString(const std::string& str);

// wstring->string
std::string ConvertString(const std::wstring& str);

// wstring->string
void Log(const std::string& message);

