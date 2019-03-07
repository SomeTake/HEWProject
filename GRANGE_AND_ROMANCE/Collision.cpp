//=============================================================================
//
// �����蔻�菈�� [Collision.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Collision.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �|�C���^�̏�����
	Collision->D3DTexture = NULL;
	Collision->Mesh = NULL;
	Collision->D3DXMatBuff = NULL;

	// �ꏊ�A�傫���̐ݒ�
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
	Collision->rot = Collision->rot;
	Collision->scl = D3DXVECTOR3(Radius, Radius, Radius);

	if (type == 0)
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(BALL_XFILE,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Collision->D3DXMatBuff,
			NULL,
			&Collision->NumMat,
			&Collision->Mesh)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitCollision(COLLISION *Collision)
{
	// �e�N�X�`���̊J��
	SAFE_RELEASE(Collision->D3DTexture);

	// ���b�V���̊J��
	SAFE_RELEASE(Collision->Mesh);

	// �}�e���A���̊J��
	SAFE_RELEASE(Collision->D3DXMatBuff);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix)
{
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCollision(COLLISION *Collision)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Collision->mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, Collision->scl.x, Collision->scl.y, Collision->scl.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Collision->rot.y, Collision->rot.x, Collision->rot.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Collision->pos.x, Collision->pos.y, Collision->pos.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Collision->mtxWorld);

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)Collision->D3DXMatBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)Collision->NumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Collision->D3DTexture);

		// �`��
		Collision->Mesh->DrawSubset(nCntMat);
	}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}