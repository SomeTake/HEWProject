//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "D3DXAnimation.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CHARA playerWk;

D3DXMATRIX WorldMtxPlayer;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	playerWk.pos = FIRST_PLAYER_POS;
	playerWk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	playerWk.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	playerWk.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// �X�e�[�^�X���̏����ݒ�
	playerWk.HP = 0;
	playerWk.HPzan = playerWk.HP;
	playerWk.SP = 0;
	playerWk.reverse = false;

	if (type == 0)
	{
		//�I�u�W�F�N�g�̏�����
		playerWk.Animation = CreateAnimationObject();

		// xFile�̓ǂݍ���
		if (FAILED(Load_xFile(playerWk.Animation, CHARA_XFILE, "Player")))
		{
			return E_FAIL;
		}

		// AnimationCallback���Z�b�g����
		// �O����
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Frontwalk])))
		{
			return E_FAIL;
		}
		// ������
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Backwalk])))
		{
			return E_FAIL;
		}
		// ���ړ�
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Rightstep])))
		{
			return E_FAIL;
		}
		// ���ړ�
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Leftstep])))
		{
			return E_FAIL;
		}
		// �_���[�W
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Damage])))
		{
			return E_FAIL;
		}
		// �_�E��
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Down])))
		{
			return E_FAIL;
		}
		// �_�E���|�[�Y
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Downpose])))
		{
			return E_FAIL;
		}
		// �N���オ��
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Getup])))
		{
			return E_FAIL;
		}
		// �p���`
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Punchi])))
		{
			return E_FAIL;
		}
		// �L�b�N
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Kick])))
		{
			return E_FAIL;
		}
		// �g��
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Hadou])))
		{
			return E_FAIL;
		}
		// ����
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Shoryu])))
		{
			return E_FAIL;
		}
		// SP�Z
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[SPattack])))
		{
			return E_FAIL;
		}
		// ����
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Throw])))
		{
			return E_FAIL;
		}
		// �����X�J��
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Miss])))
		{
			return E_FAIL;
		}


		// AnimationSet������������
		for (int i = 0; i < playerWk.Animation->AnimSetNum; i++)
		{
			if (FAILED(playerWk.Animation->InitAnimation(playerWk.Animation, CharaStateAnim[i], i)))
			{
				return E_FAIL;
			}
		}
		playerWk.Animation->CurrentAnimID = Idle;

		// �A�j���[�V�����Ԃ̕⊮��ݒ�
		for (int i = 0; i < AnimMax; i++)
		{
			playerWk.Animation->SetShiftTime(playerWk.Animation, i, Data[i].ShiftTime);
		}

	}
	else
	{
		playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// �A�j���[�V�����������[�X
	playerWk.Animation->UninitAnimation(playerWk.Animation);
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	// �A�j���[�V�������X�V
	playerWk.Animation->UpdateAnimation(playerWk.Animation, TIME_PER_FRAME);

	// ��������
	if (playerWk.reverse == false)
	{
		playerWk.rot.y = D3DX_PI * VALUE_HALF;
	}
	else if(playerWk.reverse == true)
	{
		playerWk.rot.y = D3DX_PI * -VALUE_HALF;
	}

	// �L�����N�^�[�̃A�j���[�V�����ύX
	ControlPlayer();

	// ���W�ړ�
	MovePlayer();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX ScaleMatrix, RotMatrix, TransMatrix, CapsuleMatrix, BallMatrix;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtxPlayer);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&ScaleMatrix, playerWk.scl.x, playerWk.scl.y, playerWk.scl.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&ScaleMatrix, playerWk.rot.y, playerWk.rot.x, playerWk.rot.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, playerWk.pos.x, playerWk.pos.y, playerWk.pos.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtxPlayer);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �����_�����O
	playerWk.Animation->DrawAnimation(playerWk.Animation, &WorldMtxPlayer);
	
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
//�v���C���[�̏����擾����
//=============================================================================
CHARA *GetPlayer(void)
{
	return &playerWk;
}

//=============================================================================
//���쁕�A�j���[�V�����ύX
//=============================================================================
void ControlPlayer(void)
{
	// �����̕ύX
	if (playerWk.reverse == false)
	{
		if (GetKeyboardTrigger(DIK_LEFT)) playerWk.reverse = true;
	}
	else if (playerWk.reverse == true)
	{
		if (GetKeyboardTrigger(DIK_RIGHT)) playerWk.reverse = false;
	}

	// �A�j���[�V�����̕ύX
	switch (playerWk.Animation->CurrentAnimID)
	{
	case Idle:
		// �O�i
		if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Frontwalk, Data[Frontwalk].Spd);
		}
		// �E�X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Rightstep, Data[Rightstep].Spd);
		}
		// ���X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Leftstep, Data[Leftstep].Spd);
		}
		break;
	case Frontwalk:
		if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT))
		{

		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
		}
		break;
	case Rightstep:
		if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
		}
		break;
	case Leftstep:
		if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//���W�ړ�
//=============================================================================
void MovePlayer(void)
{
	// �A�N�V�����ɍ��킹�����W�ړ�
	switch (playerWk.Animation->CurrentAnimID)
	{
		// �O�ړ����̍��W����
	case Frontwalk:
		playerWk.move.x -= sinf(playerWk.rot.y) * VALUE_FRONTWALK;
		playerWk.move.z -= cosf(playerWk.rot.y) * VALUE_FRONTWALK;
		break;
		// ��ړ����̍��W����
	case Backwalk:
			playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI) * VALUE_BACKWALK;
			playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI) * VALUE_BACKWALK;
		break;
		// ��O�ړ����̍��W����
	case Rightstep:
		playerWk.move.x -= sinf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		playerWk.move.z -= cosf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		break;
		// ���ړ����̍��W����
	case Leftstep:
		playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		break;
	default:
		break;
	}

	// �ʒu�ړ�
	playerWk.pos.x += playerWk.move.x;
	playerWk.pos.y += playerWk.move.y;
	playerWk.pos.z += playerWk.move.z;

	// (���a*�p�x)�{����W�Ńv���C���[�̍��W���v�Z����

	// �ړ��ʂ����Z�b�g����
	playerWk.move.x = 0.0f;
	playerWk.move.y = 0.0f;
	playerWk.move.z = 0.0f;	
}