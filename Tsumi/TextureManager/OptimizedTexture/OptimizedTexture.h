#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Struct.h"



struct TexData {
	uint32_t index;
	ComPtr<ID3D12Resource> resource;
};


class OptimizedTexture {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	OptimizedTexture(std::string filePath, TexData texData);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OptimizedTexture();

	/// <summary>
	/// TexHandleの取得
	/// </summary>
	uint32_t GetTexHandle() { return texData_.index; }

	/// <summary>
	/// TexResourceのリセット
	/// </summary>
	void TexRelese() { texData_.resource.Reset(); }
	

private:

	std::string filePath_;

	TexData texData_;

};