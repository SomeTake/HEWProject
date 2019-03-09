//=============================================================================
//
// �o�[�x������ [Babel.cpp]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#include "Struct.h"
#include "Babel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ITEM babelWk[BABEL_NUM];	// �A�C�e���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBabel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < BABEL_NUM; in++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		babelWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		babelWk[in].rot = D3DXVECTOR3(0.0f, BABEL_DIRECTION, 0.0f);
		babelWk[in].scl = D3DXVECTOR3(BABEL_SCALE, BABEL_SCALE, BABEL_SCALE);

		babelWk[in].D3DTexture = NULL;
		babelWk[in].D3DXMesh = NULL;
		babelWk[in].D3DXBuffMat = NULL;
		babelWk[in].NumMat = 0;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(BABEL_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&babelWk[in].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&babelWk[in].NumMat,						// D3DXMATERIAL�\���̂̐�
				&babelWk[in].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&babelWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBabel(void)
{
	for (int in = 0; in < BABEL_NUM; in++)
	{
		if (babelWk[in].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			babelWk[in].D3DTexture->Release();
			babelWk[in].D3DTexture = NULL;
		}

		if (babelWk[in].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			babelWk[in].D3DXMesh->Release();
			babelWk[in].D3DXMesh = NULL;
		}

		if (babelWk[in].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			babelWk[in].D3DXBuffMat->Release();
			babelWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBabel(void)
{


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBabel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < BABEL_NUM; in++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, babelWk[in].scl.x, babelWk[in].scl.y, babelWk[in].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, babelWk[in].rot.y, babelWk[in].rot.x, babelWk[in].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, babelWk[in].pos.x, babelWk[in].pos.y, babelWk[in].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)babelWk[in].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)babelWk[in].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, babelWk[in].D3DTexture);

			// �`��
			babelWk[in].D3DXMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// �A�C�e���̏����擾����
// �����Fin �o�[�x���ԍ�
//=============================================================================
ITEM *GetBabel(int in)
{
	return &babelWk[in];
}