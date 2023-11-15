#pragma once

#include "IScene.h"
#include "GameManager.h"


class DebugScene : public IScene {

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DebugScene() {};

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DebugScene() {};

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(GameManager* state) override;

	/// <summary>
	/// �w�i�X�v���C�g�̕`�揈��
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// �RD�I�u�W�F�N�g�̕`�揈��
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// �O�i�X�v���C�g�̕`�揈��
	/// </summary>
	void FrontSpriteDraw() override;

private:


};