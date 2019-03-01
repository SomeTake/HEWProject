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
		// �ړ�
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Walk])))
		{
			return E_FAIL;
		}

		// �E�ړ�
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Rightwalk])))
		{
			return E_FAIL;
		}

		// ���ړ�
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Leftwalk])))
		{
			return E_FAIL;
		}

		// �W���u
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Jab])))
		{
			return E_FAIL;
		}

		// �X�g���[�g
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Straight])))
		{
			return E_FAIL;
		}

		// �A�b�p�[
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Upper])))
		{
			return E_FAIL;
		}

		// �L�b�N
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Kick])))
		{
			return E_FAIL;
		}

		// �A�C�e�����E��
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Pickup])))
		{
			return E_FAIL;
		}

		// �U���i�A�C�e�������j
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Attackitem])))
		{
			return E_FAIL;
		}

		// �A�C�e���𓊂���
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Throwitem])))
		{
			return E_FAIL;
		}

		// ��_���[�W
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Reaction])))
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
	// �U�����Ȃǂ̏�Ԃł͌����ύX���ł��Ȃ�
	if (playerWk.Animation->CurrentAnimID != Jab && playerWk.Animation->CurrentAnimID != Straight
		&& playerWk.Animation->CurrentAnimID != Upper && playerWk.Animation->CurrentAnimID != Kick
		&& playerWk.Animation->CurrentAnimID != Attackitem && playerWk.Animation->CurrentAnimID != Throwitem
		&& playerWk.Animation->CurrentAnimID != Pickup)
	{
		// �����̕ύX
		if (playerWk.reverse == false)
		{
			if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(0, BUTTON_LEFT) || IsButtonPressed(0, STICK_LEFT))
			{
				playerWk.reverse = true;
			}
		}
		else if (playerWk.reverse == true)
		{
			if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(0, BUTTON_RIGHT) || IsButtonPressed(0, STICK_RIGHT))
			{
				playerWk.reverse = false;
			}
		}
	}

	// �A�j���[�V�����̕ύX
	switch (playerWk.Animation->CurrentAnimID)
	{
	case Idle:
		// �W���u PS4��
		if(GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E�� PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
		}
		// �O�i
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT) 
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Walk, Data[Walk].Spd);
		}
		// �E�X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// ���X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Walk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{

		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Rightwalk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Leftwalk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Jab:
		// �U���q�b�g���ǉ����͂ŃX�g���[�g�U�����o��
		// �X�g���[�g PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Straight, Data[Straight].Spd);
		}
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Straight:
		// �U���q�b�g���ǉ����͂ŃA�b�p�[�U�����o��
		// �A�b�p�[ PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Upper, Data[Upper].Spd);
		}

		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Upper:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Kick:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
			playerWk.HitFrag = false;
		}
		break;
	case Pickup:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			playerWk.UseItem = true;
			playerWk.HitFrag = false;
		}
		break;
	case Idleitem:
		// �A�C�e���U�� PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e���𓊂��� PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
		}
		// �O�i
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Walk, Data[Walk].Spd);
		}
		// �E�X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// ���X�e�b�v
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Attackitem:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Throwitem:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.UseItem = false;
			playerWk.HitFrag = false;
		}
		break;
	case Reaction:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk.Animation->MotionEnd == true)
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
			playerWk.HitFrag = false;
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
	case Walk:
		playerWk.move.x -= sinf(playerWk.rot.y) * VALUE_FRONTWALK;
		playerWk.move.z -= cosf(playerWk.rot.y) * VALUE_FRONTWALK;
		break;
		// ��O�ړ����̍��W����
	case Rightwalk:
		playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
		// ���ړ����̍��W����
	case Leftwalk:
		playerWk.move.x -= sinf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk.move.z -= cosf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
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