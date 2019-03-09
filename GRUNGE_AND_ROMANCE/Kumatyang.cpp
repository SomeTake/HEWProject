//=============================================================================
//
// ���܂���񏈗� [Kumatyang.cpp]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#include "Struct.h"
#include "Kumatyang.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ITEM kumatyangWk[KUMATYANG_NUM];	// �A�C�e���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitKumatyang(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		kumatyangWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		kumatyangWk[in].rot = D3DXVECTOR3(0.0f, KUMATYANG_DIRECTION, 0.0f);
		kumatyangWk[in].scl = D3DXVECTOR3(KUMATYANG_SCALE, KUMATYANG_SCALE, KUMATYANG_SCALE);

		kumatyangWk[in].D3DTexture = NULL;
		kumatyangWk[in].D3DXMesh = NULL;
		kumatyangWk[in].D3DXBuffMat = NULL;
		kumatyangWk[in].NumMat = 0;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(KUMATYANG_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&kumatyangWk[in].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&kumatyangWk[in].NumMat,						// D3DXMATERIAL�\���̂̐�
				&kumatyangWk[in].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&kumatyangWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitKumatyang(void)
{
	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		if (kumatyangWk[in].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			kumatyangWk[in].D3DTexture->Release();
			kumatyangWk[in].D3DTexture = NULL;
		}

		if (kumatyangWk[in].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			kumatyangWk[in].D3DXMesh->Release();
			kumatyangWk[in].D3DXMesh = NULL;
		}

		if (kumatyangWk[in].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			kumatyangWk[in].D3DXBuffMat->Release();
			kumatyangWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateKumatyang(void)
{


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawKumatyang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, kumatyangWk[in].scl.x, kumatyangWk[in].scl.y, kumatyangWk[in].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, kumatyangWk[in].rot.y, kumatyangWk[in].rot.x, kumatyangWk[in].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, kumatyangWk[in].pos.x, kumatyangWk[in].pos.y, kumatyangWk[in].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)kumatyangWk[in].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)kumatyangWk[in].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, kumatyangWk[in].D3DTexture);

			// �`��
			kumatyangWk[in].D3DXMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// �A�C�e���̏����擾����
// �����Fin ���܂����ԍ�
//=============================================================================
ITEM *GetKumatyang(int in)
{
	return &kumatyangWk[in];
}