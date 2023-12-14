#include "ObjDataResource.h"



// コンストラクタ
ObjDataResource::ObjDataResource(std::string filePath, ObjData objData) {

	filePath_ = filePath;
	objData_ = objData;
}



// デストラクタ
ObjDataResource::~ObjDataResource() {

	objData_.resource.Reset();
}
