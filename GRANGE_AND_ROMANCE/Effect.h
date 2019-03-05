//=============================================================================
//
// ���f������ [effekt.h]
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
	FIRE,
	HitBlood,
	HitFire,
	HitFire_Phase2,
	HitLight,
	ExplodeFire,
	ExplodeFire_Phase2,
	FireWall,
	FireWall_Phase2,
	RushSmoke,
	FirePillar,
	PowerUp,
	BossDebut,
	BossDeath,
	MagicCircle,
};


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	EffekseerRendererDX9::Renderer		*Render;
	Effekseer::Manager					*Manager;
	Effekseer::Effect					**Effect;
	int									EffectNum;
}EFFECTCONTROLLER;

typedef struct
{
	D3DXVECTOR3				Pos;
	D3DXVECTOR3				Rot;
	D3DXVECTOR3				Scale;
	D3DXVECTOR3				PPos;
	int						ID;
	int						EffectType;
	bool					Use;
}EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(bool FirstInit);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 Pos, D3DXVECTOR3 PPos, int EffectType, int no);
void TurnPhaseEffect(void);
HRESULT SafeLoadEffect(Effekseer::Manager *Manager, Effekseer::Effect **Effect, const EFK_CHAR* SrcPath, const char* ErrorSrc);
EFFECT *GetEffect(int no);

#endif
