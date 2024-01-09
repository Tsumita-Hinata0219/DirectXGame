#pragma once

#include "GameObject.h"

class Count {

public:

	Count() {};
	~Count();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	void SetNowSuuji(uint32_t val) { nowSuuji_ = val; }

private:


private:

	unique_ptr<Model> mojiModel_ = nullptr;
	WorldTransform mojiTransform_{};

	unique_ptr<Model> suujiModel_[16];
	WorldTransform suujiTransform_{};
	uint32_t suujiTex_[16];

	uint32_t nowSuuji_ = 0;

	std::vector<std::string> adress{};
};

