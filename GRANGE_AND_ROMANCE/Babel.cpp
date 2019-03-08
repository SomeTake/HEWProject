//=============================================================================
//
// �o�[�x������ [Babel.cpp]
// Author : HAL���� GP11B341-01 80163 �ђˁ@�t�P
//
//=============================================================================
#include "Babel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureBabel;	// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshBabel;		// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffBabel;// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatBabel;		// �������̑���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ITEM itemWk[BABEL_NUM];	// �A�C�e���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBabel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BABEL_NUM; en++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		itemWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-90.0f, 90.0f), 0.0f, CreateRandomFloat(-90.0f, 10.0f));
		itemWk[en].rot = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
		itemWk[en].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

		itemWk[en].D3DTexture = NULL;
		itemWk[en].D3DXMesh = NULL;
		itemWk[en].D3DXBuffMat = NULL;
		itemWk[en].NumMat = 0;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(BABEL_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&itemWk[en].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&itemWk[en].NumMat,							// D3DXMATERIAL�\���̂̐�
				&itemWk[en].D3DXMesh)))						// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,								// �t�@�C���̖��O
				&itemWk[en].D3DTexture);						// �ǂݍ��ރ������[
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
	for (int en = 0; en < BABEL_NUM; en++)
	{

		if (g_pD3DTextureBabel != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureBabel->Release();
			g_pD3DTextureBabel = NULL;
		}

		if (g_pMeshBabel != NULL)
		{// ���b�V���̊J��
			g_pMeshBabel->Release();
			g_pMeshBabel = NULL;
		}

		if (g_pD3DXMatBuffBabel != NULL)
		{// �}�e���A���̊J��
			g_pD3DXMatBuffBabel->Release();
			g_pD3DXMatBuffBabel = NULL;
		}

	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBabel(void)
{
	//itemWk[0].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	//itemWk[1].pos = D3DXVECTOR3(30.0f, 0.0f, 10.0f);
	//itemWk[2].pos = D3DXVECTOR3(50.0f, 0.0f, 10.0f);
	//itemWk[3].pos = D3DXVECTOR3(70.0f, 0.0f, 10.0f);
	//itemWk[4].pos = D3DXVECTOR3(90.0f, 0.0f, 10.0f);
	//itemWk[5].pos = D3DXVECTOR3(-10.0f, 0.0f, 30.0f);
	//itemWk[6].pos = D3DXVECTOR3(-30.0f, 0.0f, 50.0f);
	//itemWk[7].pos = D3DXVECTOR3(-50.0f, 0.0f, 70.0f);
	//itemWk[8].pos = D3DXVECTOR3(-70.0f, 0.0f, 90.0f);
	//itemWk[9].pos = D3DXVECTOR3(-90.0f, 0.0f, 100.0f);

	//for (int en = 0; en < BABEL_NUM; en++)
	//{
	//	itemWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-90.0f, 90.0f), 0.0f, CreateRandomFloat(-90.0f, 10.0f));

	//}

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


	for (int en = 0; en < BABEL_NUM; en++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, itemWk[en].scl.x, itemWk[en].scl.y, itemWk[en].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, itemWk[en].rot.y, itemWk[en].rot.x, itemWk[en].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, itemWk[en].pos.x, itemWk[en].pos.y, itemWk[en].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)itemWk[en].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)itemWk[en].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, itemWk[en].D3DTexture);

			// �`��
			itemWk[en].D3DXMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// �A�C�e���̏����擾����
// �����Fen �A�C�e���ԍ�
//=============================================================================
ITEM *GetItem(int en)
{
	return &itemWk[en];
}