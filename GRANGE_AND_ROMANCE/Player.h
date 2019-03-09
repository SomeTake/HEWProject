//=============================================================================
//
// �v���C���[���� [player.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "Collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHARA_XFILE			("data/MODEL/Girl.x")
#define PLAYER_NUM		(2)									// �v���C���[�̐�

#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// �����ʒu
#define PLAYER_HP_MAX	(200)

#define VALUE_FRONTWALK	(1.50f)								// �O�����ړ���
#define	VALUE_SIDESTEP	(1.00f)								// �������ړ���
#define VALUE_HALF		(0.5f)								// ���炩�̒l�𔼕��ɂ��邽�߂Ɋ|����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

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
{ 0, 1.5f, 0.1f, 0, 0 },		// Walk
{ 0, 1.5f, 0.1f, 0, 0 },		// Rightwalk
{ 0, 1.5f, 0.1f, 0, 0 },		// Leftwalk
{ 10, 1.5f, 0.1f, 0, 0 },		// Jab
{ 10, 1.5f, 0.1f, 0, 0 },		// Straight
{ 10, 2.0f, 0.1f, 0, 0 },		// Upper
{ 10, 1.5f, 0.1f, 0, 0 },		// Kick
{ 0, 2.0f, 0.1f, 0, 0 },		// Pickup
{ 0, 1.0f, 0.1f, 0, 0 },		// Idleitem
{ 15, 1.5f, 0.1f, 0, 0 },		// Attackitem
{ 20, 1.5f, 0.1f, 0, 0 },		// Throwitem
{ 0, 1.5f, 0.1f, 0, 0 },		// Reaction
};

// �����蔻��𔭐�������ꏊ
static const char* CharaHitPos[] =
{
	"Hips",				// �K
	"Neck",				// ��
	"Head",				// ��
	"LeftShoulder",		// ����
	"RightShoulder",	// �E��
	"LeftHand",			// ����
	"RightHand",		// �E��
	"LeftFoot",			// ����
	"RightFoot",		// �E��
	"LeftForeArm",		// ���I
	"RightForeArm",		// �E�I
	"LeftLeg",			// ���G
	"RightLeg"			// �E�G
};

// �����蔻�蔭���ꏊ�ƘA���iCharaHitPos�j
enum CharaHitNum
{
	Hips,
	Neck,
	Head,
	LeftShoulder,
	RightShoulder,
	LeftHand,
	RightHand,
	LeftFoot,
	RightFoot,
	LeftForeArm,
	RightForeArm,
	LeftLeg,
	RightLeg,
};

// �����蔻��̔��a�i��̔����ꏊ�ƘA���j
static float HitRadius[] =
{
	10.0f,
	10.0f,
	10.0f,
	5.0f,
	5.0f,
	5.0f,
	5.0f,
	7.0f,
	7.0f,
	5.0f,
	5.0f,
	7.0f,
	7.0f
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
CHARA *GetPlayer(int pn);
void ControlPlayer(int pn);						// ����
void MovePlayer(int pn);						// ���W�ړ�
void HitAction(int pn, ENEMY *enemy);			// �U���q�b�g���̃A�N�V����

#endif
