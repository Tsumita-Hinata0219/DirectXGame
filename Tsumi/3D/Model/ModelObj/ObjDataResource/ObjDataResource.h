#pragma once

#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include "Function.h"
#include "Struct.h"

#include <cassert>


// Objデータ
struct ObjData {
	uint32_t index;
	ComPtr<ID3D12Resource> resource;
	vector<VertexData> vertices; 
};


/* ObjDataResourceクラス */
class ObjDataResource {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjDataResource(std::string filePath, ObjData objData);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjDataResource();


#pragma region Get

	/// <summary>
	/// Objデータ
	/// </summary>
	ObjData GetObjData() { return objData_; }

	/// <summary>
	/// テクスチャハンドルの取得
	/// </summary>
	uint32_t GetObjHandle() { return objData_.index; }

#pragma endregion 


private:

	std::string filePath_;
	ObjData objData_{};

};