//=============================================================================
//
// ��.x���� [Onna.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Onna.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ONNA enemyWk[ONNA_NUM];	// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitOnna(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < ONNA_NUM; en++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		enemyWk[en].HP = ONNA_HP_MAX;
		enemyWk[en].HPzan = enemyWk[en].HP;
		enemyWk[en].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyWk[en].rot = D3DXVECTOR3(0.0f, ONNA_DIRECTION, 0.0f);
		enemyWk[en].scl = D3DXVECTOR3(ONNA_SCALE, ONNA_SCALE, ONNA_SCALE);

		enemyWk[en].D3DTexture = NULL;
		enemyWk[en].D3DXMesh = NULL;
		enemyWk[en].D3DXBuffMat = NULL;
		enemyWk[en].NumMat = 0;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(ONNA_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&enemyWk[en].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&enemyWk[en].NumMat,						// D3DXMATERIAL�\���̂̐�
				&enemyWk[en].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&enemyWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitOnna(void)
{
	for (int en = 0; en < ONNA_NUM; en++)
	{
		if (enemyWk[en].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			enemyWk[en].D3DTexture->Release();
			enemyWk[en].D3DTexture = NULL;
		}

		if (enemyWk[en].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			enemyWk[en].D3DXMesh->Release();
			enemyWk[en].D3DXMesh = NULL;
		}

		if (enemyWk[en].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			enemyWk[en].D3DXBuffMat->Release();
			enemyWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOnna(void)
{

	enemyWk[0].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	enemyWk[1].pos = D3DXVECTOR3(30.0f, 0.0f, 10.0f);
	enemyWk[2].pos = D3DXVECTOR3(50.0f, 0.0f, 10.0f);
	enemyWk[3].pos = D3DXVECTOR3(70.0f, 0.0f, 10.0f);
	enemyWk[4].pos = D3DXVECTOR3(90.0f, 0.0f, 10.0f);
	enemyWk[5].pos = D3DXVECTOR3(-10.0f, 0.0f, 30.0f);
	enemyWk[6].pos = D3DXVECTOR3(-30.0f, 0.0f, 50.0f);
	enemyWk[7].pos = D3DXVECTOR3(-50.0f, 0.0f, 70.0f);
	enemyWk[8].pos = D3DXVECTOR3(-70.0f, 0.0f, 90.0f);
	enemyWk[9].pos = D3DXVECTOR3(-90.0f, 0.0f, 100.0f);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOnna(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < ONNA_NUM; en++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, enemyWk[en].scl.x, enemyWk[en].scl.y, enemyWk[en].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, enemyWk[en].rot.y, enemyWk[en].rot.x, enemyWk[en].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, enemyWk[en].pos.x, enemyWk[en].pos.y, enemyWk[en].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)enemyWk[en].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)enemyWk[en].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemyWk[en].D3DTexture);

			// �`��
			enemyWk[en].D3DXMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// �G�l�~�[�̏����擾����
// �����Fen �G�l�~�[�ԍ�
//=============================================================================
ONNA *GetOnna(int en)
{
	return &enemyWk[en];
}