//=============================================================================
//
// �\���̒�`���� [Struct.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "Main.h"
#include "D3DXAnimation.h"


#define	HIT_CHECK_NUM	(13)								// �����蔻��̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �����蔻��p
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

// �v���C���[�L�����N�^�[�p
typedef struct {
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	int					HP;					// �̗�
	int					HPzan;				// �c��̗�
	D3DXANIMATION		*Animation;			// �A�j���[�V����
	bool				reverse;			// �������]�t���O
	bool				HitFrag;			// �U���������������ǂ������肷��t���O
	bool				UseItem;			// �A�C�e�����������Ă��邩�ǂ������肷��t���O
	COLLISION			Collision[HIT_CHECK_NUM];			// �����蔻��p�\����
}CHARA;

// �G�l�~�[�L�����N�^�[�p
typedef struct {
	LPDIRECT3DTEXTURE9	D3DTexture;			// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			D3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		D3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD				NumMat;				// �}�e���A�����̐�
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	int					HP;					// �̗�
	int					HPzan;				// �c��̗�
	bool				use;				// �g�p���t���O
}ENEMY;

// �A�C�e���L�����N�^�[�p
typedef struct {
	LPDIRECT3DTEXTURE9	D3DTexture;			// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			D3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		D3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD				NumMat;				// �}�e���A�����̐�
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
}ITEM;

#endif
