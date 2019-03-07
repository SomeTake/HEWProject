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
#include "Effect.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CHARA playerWk[PLAYER_NUM];

D3DXMATRIX WorldMtxPlayer;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		playerWk[pn].pos = FIRST_PLAYER_POS;
		playerWk[pn].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerWk[pn].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerWk[pn].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �X�e�[�^�X���̏����ݒ�
		playerWk[pn].HP = 200;
		playerWk[pn].HPzan = playerWk[pn].HP;
		playerWk[pn].SP = 0;
		playerWk[pn].reverse = false;
	}

	if (type == 0)
	{
		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			//�I�u�W�F�N�g�̏�����
			playerWk[pn].Animation = CreateAnimationObject();

			// xFile�̓ǂݍ���
			if (FAILED(Load_xFile(playerWk[pn].Animation, CHARA_XFILE, "Player")))
			{
				return E_FAIL;
			}

			// AnimationCallback���Z�b�g����
			// �ړ�
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Walk])))
			{
				return E_FAIL;
			}

			// �E�ړ�
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Rightwalk])))
			{
				return E_FAIL;
			}

			// ���ړ�
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Leftwalk])))
			{
				return E_FAIL;
			}

			// �W���u
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Jab])))
			{
				return E_FAIL;
			}

			// �X�g���[�g
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Straight])))
			{
				return E_FAIL;
			}

			// �A�b�p�[
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Upper])))
			{
				return E_FAIL;
			}

			// �L�b�N
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Kick])))
			{
				return E_FAIL;
			}

			// �A�C�e�����E��
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Pickup])))
			{
				return E_FAIL;
			}

			// �U���i�A�C�e�������j
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Attackitem])))
			{
				return E_FAIL;
			}

			// �A�C�e���𓊂���
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Throwitem])))
			{
				return E_FAIL;
			}

			// ��_���[�W
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Reaction])))
			{
				return E_FAIL;
			}
		}

		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			// AnimationSet������������
			for (int i = 0; i < playerWk[pn].Animation->AnimSetNum; i++)
			{
				if (FAILED(playerWk[pn].Animation->InitAnimation(playerWk[pn].Animation, CharaStateAnim[i], i)))
				{
					return E_FAIL;
				}
			}
			playerWk[pn].Animation->CurrentAnimID = Idle;
		}

		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			// �A�j���[�V�����Ԃ̕⊮��ݒ�
			for (int i = 0; i < AnimMax; i++)
			{
				playerWk[pn].Animation->SetShiftTime(playerWk[pn].Animation, i, Data[i].ShiftTime);
			}
		}
	}
	else
	{
		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// �A�j���[�V�����������[�X
		playerWk[pn].Animation->UninitAnimation(playerWk[pn].Animation);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// �A�j���[�V�������X�V
		playerWk[pn].Animation->UpdateAnimation(playerWk[pn].Animation, TIME_PER_FRAME);

		// ��������
		if (playerWk[pn].reverse == false)
		{
			playerWk[pn].rot.y = D3DX_PI * VALUE_HALF;
		}
		else if (playerWk[pn].reverse == true)
		{
			playerWk[pn].rot.y = D3DX_PI * -VALUE_HALF;
		}

		// �L�����N�^�[�̃A�j���[�V�����ύX
		ControlPlayer(pn);

		// ���W�ړ�
		MovePlayer(pn);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX ScaleMatrix, RotMatrix, TransMatrix, CapsuleMatrix, BallMatrix;

	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&WorldMtxPlayer);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&ScaleMatrix, playerWk[pn].scl.x, playerWk[pn].scl.y, playerWk[pn].scl.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&ScaleMatrix, playerWk[pn].rot.y, playerWk[pn].rot.x, playerWk[pn].rot.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&TransMatrix, playerWk[pn].pos.x, playerWk[pn].pos.y, playerWk[pn].pos.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &TransMatrix);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &WorldMtxPlayer);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �����_�����O
		playerWk[pn].Animation->DrawAnimation(playerWk[pn].Animation, &WorldMtxPlayer);

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// �v���C���[�̏����擾����
// �����Fpn �v���C���[�ԍ�
//=============================================================================
CHARA *GetPlayer(int pn)
{
	return &playerWk[pn];
}

//=============================================================================
//���쁕�A�j���[�V�����ύX
//=============================================================================
void ControlPlayer(int pn)
{
	// �U�����Ȃǂ̏�Ԃł͌����ύX���ł��Ȃ�
	if (playerWk[pn].Animation->CurrentAnimID != Jab && playerWk[pn].Animation->CurrentAnimID != Straight
		&& playerWk[pn].Animation->CurrentAnimID != Upper && playerWk[pn].Animation->CurrentAnimID != Kick
		&& playerWk[pn].Animation->CurrentAnimID != Attackitem && playerWk[pn].Animation->CurrentAnimID != Throwitem
		&& playerWk[pn].Animation->CurrentAnimID != Pickup)
	{
		// �����̕ύX
		if (playerWk[pn].reverse == false)
		{
			if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(pn, BUTTON_LEFT) || IsButtonPressed(pn, STICK_LEFT))
			{
				playerWk[pn].reverse = true;
			}
		}
		else if (playerWk[pn].reverse == true)
		{
			if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(pn, BUTTON_RIGHT) || IsButtonPressed(pn, STICK_RIGHT))
			{
				playerWk[pn].reverse = false;
			}
		}
	}

	// �A�j���[�V�����̕ύX
	switch (playerWk[pn].Animation->CurrentAnimID)
	{
	case Idle:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E�� PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
		}
		// �O�i
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Walk, Data[Walk].Spd);
		}
		// �E�X�e�b�v
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// ���X�e�b�v
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Walk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{

		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Rightwalk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Leftwalk:
		// �W���u PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e�����E��or������ PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
		}
		// �L�[�����[�X�őҋ@�ɖ߂�
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Jab:
		// �U���q�b�g���ǉ����͂ŃX�g���[�g�U�����o��
		// �X�g���[�g PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Straight, Data[Straight].Spd);
		}
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Straight:
		// �U���q�b�g���ǉ����͂ŃA�b�p�[�U�����o��
		// �A�b�p�[ PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Upper, Data[Upper].Spd);
		}

		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Upper:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Kick:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
			playerWk[pn].HitFrag = false;
		}
		break;
	case Pickup:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			playerWk[pn].UseItem = true;
			playerWk[pn].HitFrag = false;
		}
		break;
	case Idleitem:
		// �A�C�e���U�� PS4��
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
		}
		// �L�b�N PS4�~
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// �A�C�e���𓊂��� PS4��
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
		}
		// �O�i
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Walk, Data[Walk].Spd);
		}
		// �E�X�e�b�v
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// ���X�e�b�v
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Attackitem:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Throwitem:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].UseItem = false;
			playerWk[pn].HitFrag = false;
		}
		break;
	case Reaction:
		// �A�j���[�V�����I���őҋ@�ɖ߂�
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
			playerWk[pn].HitFrag = false;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//���W�ړ�
//=============================================================================
void MovePlayer(int pn)
{
	// �A�N�V�����ɍ��킹�����W�ړ�
	switch (playerWk[pn].Animation->CurrentAnimID)
	{
		// �O�ړ����̍��W����
	case Walk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y) * VALUE_FRONTWALK;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y) * VALUE_FRONTWALK;
		break;
		// ��O�ړ����̍��W����
	case Rightwalk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
		// ���ړ����̍��W����
	case Leftwalk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
	default:
		break;
	}

	// �ʒu�ړ�
	playerWk[pn].pos.x += playerWk[pn].move.x;
	playerWk[pn].pos.y += playerWk[pn].move.y;
	playerWk[pn].pos.z += playerWk[pn].move.z;

	EFFECT *Effect = GetEffect(0);

	Effect->Ppos.x = playerWk[pn].pos.x;
	Effect->Ppos.y = playerWk[pn].pos.y;
	Effect->Ppos.z = playerWk[pn].pos.z;

	// (���a*�p�x)�{����W�Ńv���C���[�̍��W���v�Z����

	// �ړ��ʂ����Z�b�g����
	playerWk[pn].move.x = 0.0f;
	playerWk[pn].move.y = 0.0f;
	playerWk[pn].move.z = 0.0f;
}