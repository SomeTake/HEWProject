//=============================================================================
//
// �����蔻�菈�� [Collision.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Main.h"
#include "Struct.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BALL_XFILE		"data/MODEL/Ball.x"					// �ǂݍ��ރ��f����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius);	// �������ABALL�\���́A�s��A���a
void UninitCollision(COLLISION *Collision);
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix);
void DrawCollision(COLLISION *Collision);

bool HitSphere(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange);
bool HitCheckPToE(CHARA *Player, ENEMY *Enemy);		// �v���C���[�̍U���ƃG�l�~�[�̓����蔻��
bool HitSpheretoCircle(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange);


#endif
