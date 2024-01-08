#pragma once

#include "GameObject.h"


/*　RailCameraクラス　*/
class RailCamera {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initizlia();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Get

	/// <summary>
	/// ViewProjectionの取得
	/// </summary>
	ViewProjection& GetViewProjection() { return viewProjection_; }

	/// <summary>
	/// WorldTransformの取得
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTrans_; }

#pragma endregion


private:


private:

	WorldTransform worldTrans_{};
	ViewProjection viewProjection_{};

};

