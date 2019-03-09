//=============================================================================
//
// エフェクトヘッダー [Effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// マクロ定義
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
// 構造体定義
//*****************************************************************************
// エフェクトコントローラー構造体
typedef struct
{
	EffekseerRendererDX9::Renderer		*Render;		// エフェクトレンダ
	Effekseer::Manager					*Manager;		// エフェクトマネージャー
	Effekseer::Effect					**Effect;		// エフェクトポインタ
	int									EffectNum;		// エフェクトの数
}EFFECTCONTROLLER;

// エフェクト構造体
typedef struct
{
	D3DXVECTOR3							pos;			// 座標
	int									ID;				// エフェクト番号
	int									EffectType;		// エフェクト種類
	bool								use;			// 使用フラグ
}EFFECT;

//*****************************************************************************
// プロトタイプ宣言
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
