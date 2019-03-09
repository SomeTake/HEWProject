//=============================================================================
//
// ��.x���� [Onna.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Struct.h"
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
ENEMY onnaWk[ONNA_NUM];	// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitOnna(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < ONNA_NUM; en++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		onnaWk[en].HP = ONNA_HP_MAX;
		onnaWk[en].HPzan = onnaWk[en].HP;
		onnaWk[en].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		onnaWk[en].rot = D3DXVECTOR3(0.0f, ONNA_DIRECTION, 0.0f);
		onnaWk[en].scl = D3DXVECTOR3(ONNA_SCALE, ONNA_SCALE, ONNA_SCALE);

		onnaWk[en].D3DTexture = NULL;
		onnaWk[en].D3DXMesh = NULL;
		onnaWk[en].D3DXBuffMat = NULL;
		onnaWk[en].NumMat = 0;
		onnaWk[en].use = true;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(ONNA_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&onnaWk[en].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&onnaWk[en].NumMat,						// D3DXMATERIAL�\���̂̐�
				&onnaWk[en].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&onnaWk[en].D3DTexture);	// �ǂݍ��ރ������[
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
		if (onnaWk[en].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			onnaWk[en].D3DTexture->Release();
			onnaWk[en].D3DTexture = NULL;
		}

		if (onnaWk[en].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			onnaWk[en].D3DXMesh->Release();
			onnaWk[en].D3DXMesh = NULL;
		}

		if (onnaWk[en].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			onnaWk[en].D3DXBuffMat->Release();
			onnaWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOnna(void)
{
	for (int en = 0; en < ONNA_NUM; en++)
	{
		// �g�p���Ă���ꍇ�̂ݍX�V
		if (onnaWk[en].use)
		{

			// HP0�ɂȂ��������
			if (onnaWk[en].HPzan == 0)
			{
				onnaWk[en].use = false;
			}
		}
	}
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
		if (onnaWk[en].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, onnaWk[en].scl.x, onnaWk[en].scl.y, onnaWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, onnaWk[en].rot.y, onnaWk[en].rot.x, onnaWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, onnaWk[en].pos.x, onnaWk[en].pos.y, onnaWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)onnaWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)onnaWk[en].NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, onnaWk[en].D3DTexture);

				// �`��
				onnaWk[en].D3DXMesh->DrawSubset(nCntMat);
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
ENEMY *GetOnna(int en)
{
	return &onnaWk[en];
}