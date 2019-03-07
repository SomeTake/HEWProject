//=============================================================================
//
// �����蔻�菈�� [Collision.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BALL_XFILE		"data/MODEL/Ball.x"					// �ǂݍ��ރ��f����
#define	HIT_CHECK_NUM	(13)								// �����蔻��̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scl;		// �傫��
	LPDIRECT3DTEXTURE9	D3DTexture;		// �e�N�X�`���ǂݍ��ݏꏊ
	LPD3DXMESH			Mesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER		D3DXMatBuff;	// ���b�V���̃}�e���A�������i�[
	DWORD				NumMat;			// �������̑���
	D3DXMATRIX			mtxWorld;		// ���[���h�}�g���b�N�X

} COLLISION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius);	// �������ABALL�\���́A�s��A���a
void UninitCollision(COLLISION *Collision);
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix);
void DrawCollision(COLLISION *Collision);

#endif
