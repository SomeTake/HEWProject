//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHARA_XFILE			("data/MODEL/Girl.x")
#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// 初期位置

#define VALUE_FRONTWALK	(1.50f)											// 前歩き移動量
#define	VALUE_SIDESTEP	(1.00f)											// 横歩き移動量
#define VALUE_HALF		(0.5f)											// 何らかの値を半分にするために掛ける

//*****************************************************************************
// グローバル変数
//*****************************************************************************
// キャラクターのデータを管理する構造体
typedef struct {
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	int					HP;					// 体力
	int					SP;					// SPゲージ
	int					HPzan;				// 残り体力
	D3DXANIMATION		*Animation;			// アニメーション
	bool				reverse;			// 向き反転フラグ
	bool				HitFrag;			// 攻撃が当たったかどうか判定するフラグ
	bool				UseItem;			// アイテムを所持しているかどうか判定するフラグ
}CHARA;

// キャラクターのアニメーション番号
static const char* CharaStateAnim[] =
{
	"idle",				// 待機
	"walk",				// 前歩き
	"rightwalk",		// 横移動
	"leftwalk",			// 横移動
	"jab",				// パンチ1
	"straight",			// パンチ2
	"upper",			// パンチ3
	"kick",				// キック
	"pickup",			// アイテムを拾う
	"idleitem",			// 待機（アイテム所持時）
	"attackitem",		// 攻撃（アイテム所持時）
	"throwitem",		// アイテムを投げる
	"reaction"			// 被ダメージ
};

// キャラクターのアニメーション番号と連動（CharaStateAnim）
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
	AnimMax,			// アニメーションの最大数
};

// バトル用データ構造体
typedef struct
{
	int Damage;					// そのモーションによって与えるダメージ量
	float Spd;					// アニメーションを再生するスピード
	float ShiftTime;			// アニメーションの切り替え時間
	int CollisionStartTime;		// 攻撃当たり判定の発生する時間
	int CollisionFinishTime;	// 攻撃当たり判定の終了する時間
}BATTLEDATA;

// バトル用データ構造体配列
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
CHARA *GetPlayer(void);
void ControlPlayer(void);		// 操作
void MovePlayer(void);			// 座標移動

#endif
