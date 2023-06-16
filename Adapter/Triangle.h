#pragma once
#include "Function.h"


class Triangle {

public:

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(DirectXCommon* directX);


	/// <summary>
	/// �O�p�`�̕`��
	/// </summary>
	void Draw();


	/// <summary>
	/// �������
	/// </summary>
	void Relese();



	// ���_���\�[�X�p�̃q�[�v�ݒ�
	void CreateVertexResource();

	// ���_�o�b�t�@�r���[���쐬����
	void MakeVertexBufferView();


private:

	// DirectX
	DirectXCommon* directX_;


	// �Ȃɂ��ꁫ
	HRESULT hr_;


	// ���_���\�[�X�Ƀf�[�^����������
	Vector4* vertexData_ = nullptr;


	// ���_���\�[�X�p�̃q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};

	D3D12_RESOURCE_DESC vertexResourceDesc_{};

	ID3D12Resource* vertexResource_ = nullptr;


	// ���_���\�[�X�p�̃q�[�v�ݒ�
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
};