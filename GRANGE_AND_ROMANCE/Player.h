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
#define CHARA_XFILE			("data/MODEL/Boy.x")
#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// �����ʒu

#define	VALUE_MOVE		(1.00f)											// �ړ���
#define VALUE_FRONTWALK	(1.50f)											// �O�����ړ���
#define VALUE_BACKWALK	(1.00f)											// �������ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.80f)								// ��]��
#define VALUE_ENLARGEMENT	(0.1f)										// �g��E�k����
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)							// ��]���x
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
}CHARA;

// �L�����N�^�[�̃A�j���[�V�����ԍ�
static const char* CharaStateAnim[] =
{
	"idle",				// �ҋ@
	"frontwalk",		// �O����
	"backwalk",			// ������
	"rightstep",		// ���ړ�
	"leftstep",			// ���ړ�
	"guard",			// �K�[�h �߂����ዹ����
	"damage",			// �_���[�W�󂯂�
	"down",				// �_�E��
	"downpose",			// �_�E�����
	"getup",			// �N���オ��
	"punchi",			// �p���`
	"kick",				// �L�b�N
	"hadou",			// �g�����B�₽�甭�����x��
	"shoryu",			// �������B�o�b�N�t���b�v
	"SPattack",			// SP�Z�B�߂������]����
	"throw",			// �����B�͂�ŕG����ăA�b�p�[
	"win",				// �K�b�c�|�[�Y�i�������j
	"miss",				// �����X�J��
	"throwedpose"		// �������Ă���Œ��̃|�[�Y
};

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Frontwalk,
	Backwalk,
	Rightstep,
	Leftstep,
	Guard,
	Damage,
	Down,
	Downpose,
	Getup,
	Punchi,
	Kick,
	Hadou,
	Shoryu,
	SPattack,
	Throw,
	Win,
	Miss,
	ThrowedPose,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

// �o�g���p�f�[�^�\����
typedef struct
{
	int Damage;					// ���̃��[�V�����ɂ���ė^����_���[�W�ʁiSP�Q�[�W�A�X�R�A�Ȃǂ��j
	float Spd;					// �A�j���[�V�������Đ�����X�s�[�h
	float ShiftTime;			// �A�j���[�V�����̐؂�ւ�����
	int CollisionStartTime;		// �U�������蔻��̔������鎞��
	int CollisionFinishTime;	// �U�������蔻��̏I�����鎞��
}BATTLEDATA;

// �o�g���p�f�[�^�\���̔z��
static BATTLEDATA Data[AnimMax] = {
	{ 0, 1.5f, 0.1f, 0, 0 },		// Idle
{ 0, 2.0f, 0.1f, 0, 0 },		// Frontwalk
{ 0, 2.0f, 0.1f, 0, 0 },		// Backwalk
{ 0, 2.0f, 0.1f, 0, 0 },		// Rightstep
{ 0, 2.0f, 0.1f, 0, 0 },		// Leftstep
{ 0, 1.0f, 0.1f, 0, 0 },		// Guard
{ 0, 1.5f, 0.1f, 0, 0 },		// Damage
{ 0, 1.5f, 0.1f, 0, 0 },		// Down
{ 0, 1.0f, 0.1f, 0, 0 },		// Downpose
{ 0, 1.5f, 0.1f, 0, 0 },		// Getup
{ 40, 2.5f, 0.1f, 0, 0 },		// Punchi
{ 50, 2.5f, 0.1f, 0, 0 },		// Kick
{ 100, 3.0f, 0.1f, 0, 0 },		// Hadou
{ 120, 2.0f, 0.1f, 0, 0 },		// Shoryu
{ 400, 1.5f, 0.1f, 0, 0 },		// SPattack
{ 150, 1.0f, 0.1f, 0, 0 },		// Throw
{ 0, 2.0f, 0.1f, 0, 0 },		// Win
{ 0, 1.5f, 0.1f, 0, 0 },		// Miss
{ 0, 1.0f, 0.1f, 0, 0 },		// Throwpose
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
