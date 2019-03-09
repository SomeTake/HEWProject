//=============================================================================
//
// �u���b�N�z�[�����񏈗� [Blackhole.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Struct.h"
#include "Blackhole.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMY blackholeWk[BLACKHOLE_NUM];	// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBlackhole(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		blackholeWk[en].HP = BLACKHOLE_HP_MAX;
		blackholeWk[en].HPzan = blackholeWk[en].HP;
		blackholeWk[en].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		blackholeWk[en].rot = D3DXVECTOR3(0.0f, BLACKHOLE_DIRECTION, 0.0f);
		blackholeWk[en].scl = D3DXVECTOR3(BLACKHOLE_SCALE, BLACKHOLE_SCALE, BLACKHOLE_SCALE);

		blackholeWk[en].D3DTexture = NULL;
		blackholeWk[en].D3DXMesh = NULL;
		blackholeWk[en].D3DXBuffMat = NULL;
		blackholeWk[en].NumMat = 0;
		blackholeWk[en].use = true;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(BLACKHOLE_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&blackholeWk[en].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&blackholeWk[en].NumMat,						// D3DXMATERIAL�\���̂̐�
				&blackholeWk[en].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&blackholeWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlackhole(void)
{
	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		if (blackholeWk[en].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			blackholeWk[en].D3DTexture->Release();
			blackholeWk[en].D3DTexture = NULL;
		}

		if (blackholeWk[en].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			blackholeWk[en].D3DXMesh->Release();
			blackholeWk[en].D3DXMesh = NULL;
		}

		if (blackholeWk[en].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			blackholeWk[en].D3DXBuffMat->Release();
			blackholeWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlackhole(void)
{
	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		// �g�p���Ă���ꍇ�̂ݍX�V
		if (blackholeWk[en].use)
		{

			// HP0�ɂȂ��������
			if (blackholeWk[en].HPzan == 0)
			{
				blackholeWk[en].use = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlackhole(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		if (blackholeWk[en].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, blackholeWk[en].scl.x, blackholeWk[en].scl.y, blackholeWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, blackholeWk[en].rot.y, blackholeWk[en].rot.x, blackholeWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, blackholeWk[en].pos.x, blackholeWk[en].pos.y, blackholeWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)blackholeWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)blackholeWk[en].NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, blackholeWk[en].D3DTexture);

				// �`��
				blackholeWk[en].D3DXMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// �G�l�~�[�̏����擾����
// �����Fen �G�l�~�[�ԍ�
//=============================================================================
ENEMY *GetBlackhole(int en)
{
	return &blackholeWk[en];
}