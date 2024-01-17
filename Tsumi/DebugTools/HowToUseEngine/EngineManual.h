#pragma once

#include "GameObject.h"


/* EngineManualクラス */
class EngineManual {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EngineManual() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EngineManual();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw(ViewProjection view);

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw(ViewProjection view);

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw(ViewProjection view);


private: // メンバ関数

	/// <summary>
	/// Audioに関する処理まとめたやつ
	/// </summary>
	void AudioUpdate();

private: // メンバ変数

	// PlaneModel
	std::unique_ptr<Model> planeModel_ = nullptr;
	WorldTransform planeModelTransform_{};
	Vector4 planeModelColor_{};


	// ObjModel
	std::unique_ptr<Model> objModel1_ = nullptr;
	WorldTransform objModelTransform1_{};
	Vector4 objModel1Color_{};

	std::unique_ptr<Model> objModel2_ = nullptr;
	WorldTransform objModelTransform2_{};

	std::unique_ptr<Model> objModel3_ = nullptr;
	WorldTransform objModelTransform3_{};

	std::unique_ptr<Model> fenceObj_ = nullptr;
	WorldTransform fenceModelTransform_{};


	// Particle
	std::unique_ptr<Particle> particle_ = nullptr;
	static constexpr uint32_t NumInstance_ = 10;
	ParticleProperties particlePrope_[NumInstance_]{};

	// Sprite
	std::unique_ptr<Sprite> spriteA_ = nullptr;
	WorldTransform spriteATransform_{};
	UVTransform uvTransformA_{};

	std::unique_ptr<Sprite> spriteB_ = nullptr;
	WorldTransform spriteBTransform_{};
	UVTransform uvTransformB_{};


	// texHandle
	uint32_t uvCheckerHD_;
	uint32_t monsterBallHD_;
	uint32_t asanohaHD_;
	uint32_t skyHD_;


	// SoundHandle
	uint32_t mokugyoHD_;
	uint32_t kakkoiiHD_;

};
