//=============================================================================
//
// �����蔻�菈�� [Collision.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Collision.h"
#include "Player.h"

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

//=====================================================================================================
// �����蔻��
// AttackPos = �U�������S�ʒu, DefendPos = �h�䑤���S�ʒu, AttackRange = �U�������a, DefendPos = �h�䑤���a
//=====================================================================================================
bool HitSphere(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange)
{
	// �����蔻��̒��S�̋����𑪂�
	D3DXVECTOR3 unit = AttackPos - DefendPos;
	float dist = D3DXVec3Length(&unit);

	// �����蔻��͈̔͂𑫂����������o���i���Ȃ̂�XYZ�ǂ�Ƃ��Ă������j
	float hitrange = AttackRange + DefendRange;

	// �����蔻��̒��S�̋��������͈͂𑫂��������̕���������Γ�����
	if (dist <= hitrange)
	{
		return true;
	}
	// �O��
	else
	{

	}
	return false;
}

//=====================================================================================================
// �����蔻��
// AttackPos = �U�������S�ʒu, DefendPos = �h�䑤���S�ʒu, AttackRange = �U�������a, DefendPos = �h�䑤���a
//=====================================================================================================
bool HitSpheretoCircle(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange)
{
	// �����蔻��̒��S�̋����𑪂�
	float DistX = AttackPos.x - DefendPos.x;
	float DistZ = AttackPos.z - DefendPos.z;
	float dist = sqrtf(DistX * DistX + DistZ * DistZ);

	// �����蔻��͈̔͂𑫂����������o���i���Ȃ̂�XYZ�ǂ�Ƃ��Ă������j
	float hitrange = AttackRange + DefendRange;

	// �����蔻��̒��S�̋��������͈͂𑫂��������̕���������Γ�����
	if (dist <= hitrange)
	{
		return true;
	}
	// �O��
	else
	{

	}

	return false;
}


//=====================================================================================================
// �v���C���[�̍U���ƃG�l�~�[�Ƃ̓����蔻��
// �����FPlayer�\���́@Enemy�\����
//=====================================================================================================
bool HitCheckPToE(CHARA *Player, ENEMY *Enemy)
{
	switch (Player->Animation->CurrentAnimID)
	{
	case Jab:
		if (HitSpheretoCircle(Player->Collision[LeftHand].pos, Enemy->pos,
			Player->Collision[LeftHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Straight:
		if (HitSpheretoCircle(Player->Collision[RightHand].pos, Enemy->pos,
			Player->Collision[RightHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Upper:
		if (HitSpheretoCircle(Player->Collision[LeftHand].pos, Enemy->pos,
			Player->Collision[LeftHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Kick:
		if (HitSpheretoCircle(Player->Collision[RightFoot].pos, Enemy->pos,
			Player->Collision[RightFoot].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Attackitem:
		break;
	case Throwitem:
		break;
	default:
		break;
	}

	return false;
}