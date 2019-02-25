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
#define CHARA_XFILE			("data/MODEL/Boy.x")
#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// 初期位置

#define	VALUE_MOVE		(1.00f)											// 移動量
#define VALUE_FRONTWALK	(1.50f)											// 前歩き移動量
#define VALUE_BACKWALK	(1.00f)											// 後ろ歩き移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.80f)								// 回転量
#define VALUE_ENLARGEMENT	(0.1f)										// 拡大・縮小量
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)							// 回転速度
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
}CHARA;

// キャラクターのアニメーション番号
static const char* CharaStateAnim[] =
{
	"idle",				// 待機
	"frontwalk",		// 前歩き
	"backwalk",			// 後ろ歩き
	"rightstep",		// 横移動
	"leftstep",			// 横移動
	"guard",			// ガード めっちゃ胸反る
	"damage",			// ダメージ受けた
	"down",				// ダウン
	"downpose",			// ダウン状態
	"getup",			// 起き上がり
	"punchi",			// パンチ
	"kick",				// キック
	"hadou",			// 波動拳。やたら発生が遅い
	"shoryu",			// 昇竜拳。バックフリップ
	"SPattack",			// SP技。めっちゃ回転する
	"throw",			// 投げ。掴んで膝入れてアッパー
	"win",				// ガッツポーズ（勝利時）
	"miss",				// 投げスカり
	"throwedpose"		// 投げられている最中のポーズ
};

// キャラクターのアニメーション番号と連動（CharaStateAnim）
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
	AnimMax,			// アニメーションの最大数
};

// バトル用データ構造体
typedef struct
{
	int Damage;					// そのモーションによって与えるダメージ量（SPゲージ、スコアなども）
	float Spd;					// アニメーションを再生するスピード
	float ShiftTime;			// アニメーションの切り替え時間
	int CollisionStartTime;		// 攻撃当たり判定の発生する時間
	int CollisionFinishTime;	// 攻撃当たり判定の終了する時間
}BATTLEDATA;

// バトル用データ構造体配列
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
