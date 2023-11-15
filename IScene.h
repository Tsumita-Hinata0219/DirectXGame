#pragma once

class GameManager;

/* IScene�N���X */
class IScene {

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	IScene() {};

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IScene() {};

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(GameManager* state) = 0;

	/// <summary>
	/// �w�i�X�v���C�g�̕`�揈��
	/// </summary>
	virtual void BackSpriteDraw() = 0;

	/// <summary>
	/// �RD�I�u�W�F�N�g�̕`�揈��
	/// </summary>
	virtual void ModelDraw() = 0;

	/// <summary>
	/// �O�i�X�v���C�g�̕`�揈��
	/// </summary>
	virtual void FrontSpriteDraw() = 0;


private:


};