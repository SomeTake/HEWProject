/*******************************************************************************
* タイトル:		ゲームプログラム
* プログラム名:	Game.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Game.h"
#include "Player.h"
#include "Onna.h"
#include "Gauge.h"
#include "meshfield.h"
#include "Blackhole.h"
#include "Babel.h"
#include "Kumatyang.h"
#include "YakiYaki.h"
#include "Meshwall.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
	// 壁の初期化
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	InitPlayer(0);
	InitOnna(0);
	InitGauge(0);
	InitBlackhole(0);
	InitBabel(0);
	InitKumatyang(0);
	InitYakiYaki(0);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitMeshField();
	UninitPlayer();
	UninitOnna();
	UninitGauge();
	UninitBlackhole();
	UninitBabel();
	UninitKumatyang();
	UninitYakiYaki();
	// 壁の終了処理
	UninitMeshWall();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	UpdateMeshField();
	UpdatePlayer();
	UpdateOnna();
	UpdateGauge();
	UpdateBlackhole();
	UpdateBabel();
	UpdateKumatyang();
	UpdateYakiYaki();
	UpdateMeshWall();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawMeshWall();
	DrawMeshField();
	DrawPlayer();
	DrawOnna();
	DrawGauge();
	DrawBlackhole();
	DrawBabel();
	DrawKumatyang();
	DrawYakiYaki();

}

