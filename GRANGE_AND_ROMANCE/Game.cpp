/*******************************************************************************
* タイトル:		ゲームプログラム
* プログラム名:	Game.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Gauge.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	InitPlayer(0);
	InitEnemy(0);

	InitGauge(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// モデルの終了処理
	UninitPlayer();
	UninitEnemy();

	UninitGauge();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	UpdatePlayer();
	UpdateEnemy();

	UpdateGauge();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// プレイヤー描画
	DrawPlayer();
	DrawEnemy();

	DrawGauge();

}

