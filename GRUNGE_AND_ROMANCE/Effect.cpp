//=============================================================================
//
// ���f������ [Effekt.cpp]
// Author : 
//
//=============================================================================
#include "Main.h"
#include "Effect.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EffectMax (1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EFFECTCONTROLLER		EffectCtrl;
EFFECT					Effect[EffectMax];

static const EFK_CHAR* EffectFileName[] =
{
	(const EFK_CHAR*)L"data/EFFECT/blow.efk",
	(const EFK_CHAR*)L"data/EFFECT/FireCircle.efk",

};

D3DXVECTOR3 at, up, pos,ppos;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(bool FirstInit)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	int Effect_No = 0;

	for (Effect_No = 0; Effect_No < EffectMax; Effect_No++)
	{
		Effect[Effect_No].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		Effect[Effect_No].Ppos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		Effect[Effect_No].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		Effect[Effect_No].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);;
		Effect[Effect_No].ID = -1;
		Effect[Effect_No].EffectType = -1;
		Effect[Effect_No].use = true;
	}

	// ���߂ď�����
	if (FirstInit == true)
	{
		EffectCtrl.Manager = NULL;
		EffectCtrl.Render = NULL;
		EffectCtrl.Effect = NULL;
		EffectCtrl.EffectNum = sizeof(EffectFileName) / sizeof(const EFK_CHAR*);

		// �`��p�C���X�^���X�̐���
		EffectCtrl.Render = ::EffekseerRendererDX9::Renderer::Create(Device, 30000);

		// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
		EffectCtrl.Manager = ::Effekseer::Manager::Create(30000);

		// �`��p�C���X�^���X����`��@�\��ݒ�
		EffectCtrl.Manager->SetSpriteRenderer(EffectCtrl.Render->CreateSpriteRenderer());
		EffectCtrl.Manager->SetRibbonRenderer(EffectCtrl.Render->CreateRibbonRenderer());
		EffectCtrl.Manager->SetRingRenderer(EffectCtrl.Render->CreateRingRenderer());
		EffectCtrl.Manager->SetTrackRenderer(EffectCtrl.Render->CreateTrackRenderer());
		EffectCtrl.Manager->SetModelRenderer(EffectCtrl.Render->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		EffectCtrl.Manager->SetTextureLoader(EffectCtrl.Render->CreateTextureLoader());
		EffectCtrl.Manager->SetModelLoader(EffectCtrl.Render->CreateModelLoader());

		// ���������m��
		EffectCtrl.Effect = (Effekseer::Effect**)calloc(EffectCtrl.EffectNum, sizeof(Effekseer::Effect*));
		if (EffectCtrl.Effect == NULL)
		{
			MessageBox(0, "Alloc Effect Memory Failed�I", "Error", 0);
			return E_FAIL;
		}

		// �G�t�F�N�g�̓Ǎ�
		for (int i = 0; i < EffectCtrl.EffectNum; i++)
		{
			if (FAILED(SafeLoadEffect(EffectCtrl.Manager, &EffectCtrl.Effect[i], EffectFileName[i], "effect")))
			{
				return E_FAIL;
			}
		}
	}

	// �S�G�t�F�N�g��~
	EffectCtrl.Manager->StopAllEffects();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �G�t�F�N�g�̒�~
	EffectCtrl.Manager->StopAllEffects();

	//// �G�t�F�N�g�̔j��
	//SafeFree(EffektCtrl.Effekt);
	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE(*EffectCtrl.Effect);

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	EffectCtrl.Manager->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	EffectCtrl.Render->Destroy();

	return;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	static int Count = 0;
	int Effect_No = 0;
	int EffectID = 0;

	for (Effect_No = 0; Effect_No < EffectMax; Effect_No++)
	{
		if (Effect[Effect_No].use == true)
		{
			EffectID = Effect[Effect_No].ID;
			if (GetKeyboardTrigger(DIK_O))
			{
					int EffectID = EffectCtrl.Manager->Play(EffectCtrl.Effect[FIRE],
						Effect->Ppos.x, Effect->Ppos.y, Effect->Ppos.z);

					if (GetKeyboardRelease(DIK_O))
					{
						EffectCtrl.Manager->StopEffect(Effect[Effect_No].ID);
						Effect[Effect_No].use = false;
						continue;
					}
			}

			else if (GetKeyboardTrigger(DIK_P))
			{
				int EffectID = EffectCtrl.Manager->Play(EffectCtrl.Effect[WATER],
					Effect->Ppos.x, Effect->Ppos.y, Effect->Ppos.z);

				if (GetKeyboardRelease(DIK_P))
				{
					EffectCtrl.Manager->StopEffect(Effect[Effect_No].ID);
					Effect[Effect_No].use = false;
					continue;
				}
			}

		}
	}


	// �G�t�F�N�g�̍X�V�������s��
	EffectCtrl.Manager->Update();

	return;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	CAMERA *cameraWk = GetCamera(0);

	pos=cameraWk->pos;
	at = cameraWk->at;
	up = cameraWk->up;

	// ���e�s���ݒ�
	EffectCtrl.Render->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z));

	// �J�����s���ݒ�
	EffectCtrl.Render->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(pos.x, pos.y, pos.z), ::Effekseer::Vector3D(at.x, at.y, at.z + 50.0f), ::Effekseer::Vector3D(up.x, up.y, up.z)));

	// �G�t�F�N�g�̕`��J�n�������s���B
	EffectCtrl.Render->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	EffectCtrl.Manager->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	EffectCtrl.Render->EndRendering();

	return;
}

//=============================================================================
// �G�t�F�N�g��ݒu����
//=============================================================================
void SetEffect(D3DXVECTOR3 Pos, int EffectType)
{
	int Effect_No = 0;

	for (Effect_No = 0; Effect_No < EffectMax; Effect_No++)
	{
		if (Effect[Effect_No].use == false)
		{
			Effect[Effect_No].ID = EffectCtrl.Manager->Play(EffectCtrl.Effect[EffectType], Pos.x, Pos.y, Pos.z);
			Effect[Effect_No].pos = Pos;
			Effect[Effect_No].EffectType = EffectType;
			Effect[Effect_No].use = true;
			break;
		}
	}

	return;
}

//=============================================================================
// �G�t�F�N�g�R���g���[���[���擾����
//=============================================================================
EFFECTCONTROLLER *GetEffectCtrl(void)
{
	return &EffectCtrl;
}

//=============================================================================
// �G�t�F�N�g��ǂݍ���
//=============================================================================
HRESULT SafeLoadEffect(Effekseer::Manager *Manager, Effekseer::Effect **Effect, const EFK_CHAR* SrcPath, const char* ErrorSrc)
{
	char Message[256];
	// �G�t�F�N�g�t�@�C���̒��̃e�N�X�`���̐�
	int TextureNum = 0;

	// �G�t�F�N�g�t�@�C����ǂݍ���
	(*Effect) = Effekseer::Effect::Create(Manager, SrcPath);
	// ���s������
	if ((*Effect) == NULL)
	{
		sprintf_s(Message, "Load %s Effect Failed�I", ErrorSrc);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	// �G�t�F�N�g�t�@�C���̒��̃e�N�X�`���̐����擾����
	TextureNum = (*Effect)->GetColorImageCount();
	for (int i = 0; i < TextureNum; i++)
	{
		// �e�N�X�`���̃|�C���^���擾����
		Effekseer::TextureData *Texture = (*Effect)->GetColorImage(i);
		// �e�N�X�`����ǂݍ��ނ����s������
		if (Texture == NULL)
		{
			sprintf_s(Message, "Load %s Effect Texture Failed�I", ErrorSrc);
			MessageBox(0, Message, "Error", 0);
			return E_FAIL;
		}
	}

	return S_OK;
}

EFFECT*GetEffect(int no)
{
	return(&Effect[no]);
}


