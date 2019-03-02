/*******************************************************************************
* タイトル:		ゲームヘッダー
* プログラム名:	Game.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_GAME		("data/TEXTURE/enter2.png")				// 読み込むテクスチャファイル名
#define	GAME_SIZE_X			(800)									// ゲームの幅
#define	GAME_SIZE_Y			(600)									// ゲームの高さ
#define GAME_MAX			(1)										// ゲームの最大数
#define	NUM_GAME			(2)										// ポリゴン数
#define TEXTURE_PATTERN_DIVIDE_X_GAME	(1)							// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_GAME	(1)							// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_GAME			(TEXTURE_PATTERN_DIVIDE_X_GAME*TEXTURE_PATTERN_DIVIDE_Y_GAME)	// アニメーションパターン数
#define TIME_ANIMATION_GAME				(4)							// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// ゲーム構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		scl;						// ポリゴンの拡大量
	D3DXVECTOR3		col;						// ポリゴンの色彩量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			Alpha;
	float			Radius;						// ゲームの半径
	float			BaseAngle;					// ゲームの角度
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D			VertexWkGame[NUM_VERTEX];			// 頂点情報格納ワーク

} GAME;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
HRESULT MakeVertexGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAME *GetGame(int no);

#endif
