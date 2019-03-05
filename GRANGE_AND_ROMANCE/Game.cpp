/*******************************************************************************
* タイトル:		ゲームプログラム
* プログラム名:	Game.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Game.h"
#include "Player.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
<<<<<<< HEAD
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAME *game = GameWk;										// ゲームのポインターを初期化

																// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
		TEXTURE_GAME,				// ファイルの名前
		&pD3DTextureGame);			// 読み込むメモリー

	game->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	game->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	game->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	game->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 座標データを初期化
	game->Alpha = 1.0f;
	game->use = false;
	game->Texture = pD3DTextureGame;								// テクスチャ情報
	D3DXVECTOR2 temp = D3DXVECTOR2(GAME_SIZE_X, GAME_SIZE_Y);
	game->Radius = D3DXVec2Length(&temp);							// ゲームの半径を初期化
	game->BaseAngle = atan2f(GAME_SIZE_Y, GAME_SIZE_X);				// ゲームの角度を初期化
	game->PatternAnim = 0;											// アニメパターン番号を初期化
	game->CountAnim = 0;											// アニメカウントを初期化
																	// 頂点情報の作成
	MakeVertexGame();
=======
	InitPlayer(0);
>>>>>>> master

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// モデルの終了処理
	UninitPlayer();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	UpdatePlayer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
<<<<<<< HEAD
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAME *game = GameWk;						// ゲームのポインターを初期化

	if (game->use == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);


		// テクスチャの設定
		pDevice->SetTexture(0, game->Texture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAME, game->VertexWkGame, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGame(void)
{
	GAME *game= GameWk;				// ゲームのポインターを初期化

	// 頂点座標の設定
	game->VertexWkGame[0].vtx = D3DXVECTOR3(game->pos.x, game->pos.y, 0.0f);
	game->VertexWkGame[1].vtx = D3DXVECTOR3(game->pos.x + GAME_SIZE_X, game->pos.y, 0.0f);
	game->VertexWkGame[2].vtx = D3DXVECTOR3(game->pos.x, game->pos.y + GAME_SIZE_Y, 0.0f);
	game->VertexWkGame[3].vtx = D3DXVECTOR3(game->pos.x + GAME_SIZE_X, game->pos.y + GAME_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	game->VertexWkGame[0].rhw =
	game->VertexWkGame[1].rhw =
	game->VertexWkGame[2].rhw =
	game->VertexWkGame[3].rhw = 1.0f;

	// 反射光の設定
	game->VertexWkGame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	game->VertexWkGame[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	game->VertexWkGame[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_GAME, 0.0f);
	game->VertexWkGame[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GAME);
	game->VertexWkGame[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_GAME, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GAME);

	return S_OK;
=======
	// プレイヤー描画
	DrawPlayer();
>>>>>>> master
}

