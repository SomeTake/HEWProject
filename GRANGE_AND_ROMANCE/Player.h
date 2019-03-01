//=============================================================================
//
// �v���C���[���� [player.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHARA_XFILE			("data/MODEL/Girl.x")
#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// �����ʒu

#define VALUE_FRONTWALK	(1.50f)											// �O�����ړ���
#define	VALUE_SIDESTEP	(1.00f)											// �������ړ���
#define VALUE_HALF		(0.5f)											// ���炩�̒l�𔼕��ɂ��邽�߂Ɋ|����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
// �L�����N�^�[�̃f�[�^���Ǘ�����\����
typedef struct {
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	int					HP;					// �̗�
	int					SP;					// SP�Q�[�W
	int					HPzan;				// �c��̗�
	D3DXANIMATION		*Animation;			// �A�j���[�V����
	bool				reverse;			// �������]�t���O
	bool				HitFrag;			// �U���������������ǂ������肷��t���O
	bool				UseItem;			// �A�C�e�����������Ă��邩�ǂ������肷��t���O
}CHARA;

// �L�����N�^�[�̃A�j���[�V�����ԍ�
static const char* CharaStateAnim[] =
{
	"idle",				// �ҋ@
	"walk",				// �O����
	"rightwalk",		// ���ړ�
	"leftwalk",			// ���ړ�
	"jab",				// �p���`1
	"straight",			// �p���`2
	"upper",			// �p���`3
	"kick",				// �L�b�N
	"pickup",			// �A�C�e�����E��
	"idleitem",			// �ҋ@�i�A�C�e���������j
	"attackitem",		// �U���i�A�C�e���������j
	"throwitem",		// �A�C�e���𓊂���
	"reaction"			// ��_���[�W
};

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Walk,
	Rightwalk,
	Leftwalk,
	Jab,
	Straight,
	Upper,
	Kick,
	Pickup,
	Idleitem,
	Attackitem,
	Throwitem,
	Reaction,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

// �o�g���p�f�[�^�\����
typedef struct
{
	int Damage;					// ���̃��[�V�����ɂ���ė^����_���[�W��
	float Spd;					// �A�j���[�V�������Đ�����X�s�[�h
	float ShiftTime;			// �A�j���[�V�����̐؂�ւ�����
	int CollisionStartTime;		// �U�������蔻��̔������鎞��
	int CollisionFinishTime;	// �U�������蔻��̏I�����鎞��
}BATTLEDATA;

// �o�g���p�f�[�^�\���̔z��
static BATTLEDATA Data[AnimMax] = {
	{ 0, 1.0f, 0.1f, 0, 0 },		// Idle
{ 0, 1.0f, 0.1f, 0, 0 },		// Walk
{ 0, 1.0f, 0.1f, 0, 0 },		// Rightwalk
{ 0, 1.0f, 0.1f, 0, 0 },		// Leftwalk
{ 0, 1.0f, 0.1f, 0, 0 },		// Jab
{ 0, 1.0f, 0.1f, 0, 0 },		// Straight
{ 0, 1.0f, 0.1f, 0, 0 },		// Upper
{ 0, 1.0f, 0.1f, 0, 0 },		// Kick
{ 0, 1.0f, 0.1f, 0, 0 },		// Pickup
{ 0, 1.0f, 0.1f, 0, 0 },		// Idleitem
{ 0, 1.0f, 0.1f, 0, 0 },		// Attackitem
{ 0, 1.0f, 0.1f, 0, 0 },		// Throwitem
{ 0, 1.0f, 0.1f, 0, 0 },		// Reaction
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
CHARA *GetPlayer(void);
void ControlPlayer(void);		// ����
void MovePlayer(void);			// ���W�ړ�

#endif
