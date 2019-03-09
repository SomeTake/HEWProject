//=============================================================================
//
// �G�t�F�N�g�w�b�_�[ [Effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum EffectType
{
	HitEffect,
	FireEffect,
	HealEffect1,
	HealEffect2,
	HewEffect,
	BushEffect
};


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �G�t�F�N�g�R���g���[���[�\����
typedef struct
{
	EffekseerRendererDX9::Renderer		*Render;		// �G�t�F�N�g�����_
	Effekseer::Manager					*Manager;		// �G�t�F�N�g�}�l�[�W���[
	Effekseer::Effect					**Effect;		// �G�t�F�N�g�|�C���^
	int									EffectNum;		// �G�t�F�N�g�̐�
}EFFECTCONTROLLER;

// �G�t�F�N�g�\����
typedef struct
{
	D3DXVECTOR3							pos;			// ���W
	int									ID;				// �G�t�F�N�g�ԍ�
	int									EffectType;		// �G�t�F�N�g���
	bool								use;			// �g�p�t���O
}EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(bool FirstInit);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 Pos, int EffectType);
HRESULT SafeLoadEffect(Effekseer::Manager *Manager, Effekseer::Effect **Effect, const EFK_CHAR* SrcPath, const char* ErrorSrc);
EFFECT *GetEffect(int no);
EFFECTCONTROLLER *GetEffectCtrl(void);

#endif
