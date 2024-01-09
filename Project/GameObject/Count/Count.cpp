#include "Count.h"

Count::~Count()
{
}

void Count::Initialize()
{

	adress = { 
		"0", "1", "2", "3", "4", "5", 
		"6", "7", "8", "9", "10", "11", 
		"12", "13", "14", "15" };

	mojiModel_ = make_unique<Model>();
	mojiModel_->CreateFromObj("Moji");
	mojiTransform_.Initialize();
	mojiTransform_.scale = { 60.0f, 60.0f, 60.0f };
	mojiTransform_.rotate = { 0.0f, 0.0f, 0.0f };
	mojiTransform_.translate = { 00.0f, 50.0f, 400.0f };


	for (int i = 0; i < 16; i++) {
		suujiModel_[i] = make_unique<Model>();
		suujiModel_[i]->CreateFromObj(adress[i]);
	}
	suujiTransform_.Initialize();
	suujiTransform_.scale = { 60.0f, 60.0f, 60.0f };
	suujiTransform_.rotate = { 0.0f, 0.0f, 0.0f };
	suujiTransform_.translate = { -20.0f, 46.0f, 400.0f };
	nowSuuji_ = 15;
}

void Count::Update()
{
	mojiTransform_.UpdateMatrix();
	suujiTransform_.UpdateMatrix();

#ifdef _DEBUG
	
	ImGui::Begin("Suuji");
	ImGui::DragInt("nowSuuji", reinterpret_cast<int*>(&nowSuuji_), 1, 0, 15);
	ImGui::DragFloat3("SuujiScale", &suujiTransform_.scale.x, 0.1f);
	ImGui::DragFloat3("SuujiRotate", &suujiTransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("SuujiTranslate", &suujiTransform_.translate.x, 0.1f);
	ImGui::End();

#endif // _DEBUG

}

void Count::Draw(ViewProjection view)
{
	mojiModel_->Draw(mojiTransform_, view);
	suujiModel_[nowSuuji_]->Draw(suujiTransform_, view);
}
