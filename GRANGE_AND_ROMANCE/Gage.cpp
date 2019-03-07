/*******************************************************************************
* タイトル:		ゲージプログラム
* プログラム名:	Gage.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Main.h"
#include "Input.h"
#include "Gage.h"
#include "Player.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGage = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGage2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGage3 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGage4 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGage5 = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureGage6 = NULL;		// テクスチャへのポインタ

GAGE						gageWk[GAGE_MAX];			// gage構造体
GAGE2						gageWk2[GAGE2_MAX];			// gage2構造体
GAGE3						gageWk3[GAGE3_MAX];			// gage3構造体
GAGE4						gageWk4[GAGE4_MAX];			// gage4構造体
GAGE5						gageWk5[GAGE5_MAX];			// gage5構造体
GAGE6						gageWk6[GAGE6_MAX];			// gage6構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGage(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE *gage = gageWk;						// gageのポインターを初期化
	GAGE2 *gage2 = gageWk2;						// gage2のポインターを初期化
	GAGE3 *gage3 = gageWk3;						// gage3のポインターを初期化
	GAGE4 *gage4 = gageWk4;						// gage4のポインターを初期化
	GAGE5 *gage5 = gageWk5;						// gage5のポインターを初期化
	GAGE6 *gage6 = gageWk6;						// gage6のポインターを初期化

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE,						// ファイルの名前
			&g_pD3DTextureGage);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE2,						// ファイルの名前
			&g_pD3DTextureGage2);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE3,						// ファイルの名前
			&g_pD3DTextureGage3);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE4,						// ファイルの名前
			&g_pD3DTextureGage4);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE5,						// ファイルの名前
			&g_pD3DTextureGage5);				// 読み込むメモリー
	}
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_GAGE6,						// ファイルの名前
			&g_pD3DTextureGage6);				// 読み込むメモリー
	}

	// gageの初期化処理
	for (int i = 0; i < GAGE_MAX; i++, gage++)
	{
		gage->use = true;												// 使用
		gage->pos = D3DXVECTOR3(-400.0f, 30.0f, 0.0f);					// 座標データを初期化
		gage->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化

		gage->g_pD3DTexture = g_pD3DTextureGage;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}
	// gage2の初期化処理
	for (int i = 0; i < GAGE2_MAX; i++, gage2++)
	{
		gage2->use = true;												// 使用
		gage2->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// 座標データを初期化
		gage2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転データを初期化
		gage2->g_pD3DTexture2 = g_pD3DTextureGage2;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}
	// gage3の初期化処理
	for (int i = 0; i < GAGE3_MAX; i++, gage3++)
	{
		gage3->use = true;												// 使用
		gage3->pos = D3DXVECTOR3(1000.0f, 30.0f, 0.0f);					// 座標データを初期化
		gage3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化

		gage3->g_pD3DTexture3 = g_pD3DTextureGage3;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}
	// gage4の初期化処理
	for (int i = 0; i < GAGE4_MAX; i++, gage4++)
	{
		gage4->use = true;												// 使用
		gage4->pos = D3DXVECTOR3(1000.0f, 70.0f, 0.0f);					// 座標データを初期化
		gage4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化
		gage4->g_pD3DTexture4 = g_pD3DTextureGage4;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}
	// gage5の初期化処理
	for (int i = 0; i < GAGE5_MAX; i++, gage5++)
	{
		gage5->use = true;												// 使用
		gage5->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);					// 座標データを初期化
		gage5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化
		gage5->g_pD3DTexture5 = g_pD3DTextureGage5;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}
	// gage6の初期化処理
	for (int i = 0; i < GAGE6_MAX; i++, gage6++)
	{
		gage6->use = true;												// 使用
		gage6->pos = D3DXVECTOR3(1000.0f, 70.0f, 0.0f);					// 座標データを初期化
		gage6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転データを初期化
		gage6->g_pD3DTexture6 = g_pD3DTextureGage6;						// テクスチャ情報
		MakeVertexGage();												// 頂点情報の作成
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGage(void)
{
	if (g_pD3DTextureGage != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage->Release();
		g_pD3DTextureGage = NULL;
	}
	if (g_pD3DTextureGage2 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage2->Release();
		g_pD3DTextureGage2 = NULL;
	}
	if (g_pD3DTextureGage3 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage3->Release();
		g_pD3DTextureGage3 = NULL;
	}
	if (g_pD3DTextureGage4 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage4->Release();
		g_pD3DTextureGage4 = NULL;
	}
	if (g_pD3DTextureGage5 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage5->Release();
		g_pD3DTextureGage5 = NULL;
	}
	if (g_pD3DTextureGage6 != NULL)
	{// テクスチャの開放
		g_pD3DTextureGage6->Release();
		g_pD3DTextureGage6 = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateGage(void)
{
	GAGE *gage = gageWk;						// gageのポインターを初期化
	GAGE2 *gage2 = gageWk2;						// gage2のポインターを初期化
	GAGE3 *gage3 = gageWk3;						// gage3のポインターを初期化
	GAGE4 *gage4 = gageWk4;						// gage4のポインターを初期化
	GAGE5 *gage5 = gageWk5;						// gage5のポインターを初期化
	GAGE6 *gage6 = gageWk6;						// gage6のポインターを初期化

		gage2->pos.x +=4.0f;
		gage->pos.x += 4.0f;
		gage5->pos.x += 4.0f;

		if (gage2->pos.x >= 0.0f)
		{
			gage2->pos.x = 0;
			gage->pos.x = 0;
			gage5->pos.x = 0;
		}

		gage4->pos.x -= 4.0f;
		gage3->pos.x -= 4.0f;
		gage6->pos.x -= 4.0f;

		if (gage4->pos.x <= 600.0f)
		{
			gage4->pos.x = 600;
			gage3->pos.x = 600;
			gage6->pos.x = 600;

		}

		SetVertexGage();
		SetTextuerGage();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawGage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE *gage = gageWk;						// gageのポインターを初期化
	GAGE2 *gage2 = gageWk2;						// gage2のポインターを初期化
	GAGE3 *gage3 = gageWk3;						// gage3のポインターを初期化
	GAGE4 *gage4 = gageWk4;						// gage4のポインターを初期化
	GAGE5 *gage5 = gageWk5;						// gage5のポインターを初期化
	GAGE6 *gage6 = gageWk6;						// gage6のポインターを初期化

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage5);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE5, gage5->vertexWk5, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE, gage->vertexWk, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage2);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE2, gage2->vertexWk2, sizeof(VERTEX_2D));



		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage6);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE6, gage6->vertexWk6, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage3);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE3, gage3->vertexWk3, sizeof(VERTEX_2D));


		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGage4);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAGE4, gage4->vertexWk4, sizeof(VERTEX_2D));

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGage(void)
{
	GAGE *gage = gageWk;				// gageのポインターを初期化
	GAGE2 *gage2 = gageWk2;				// gage2のポインターを初期化
	GAGE3 *gage3 = gageWk3;				// gage3のポインターを初期化
	GAGE4 *gage4 = gageWk4;				// gage4のポインターを初期化
	GAGE5 *gage5 = gageWk5;				// gage5のポインターを初期化
	GAGE6 *gage6 = gageWk6;				// gage6のポインターを初期化

		// 頂点座標の設定
		gage->vertexWk[0].vtx = D3DXVECTOR3(gage->pos.x, gage->pos.y, 0.0f);
		gage->vertexWk[1].vtx = D3DXVECTOR3(gage->pos.x + GAGE_SIZE_X, gage->pos.y, 0.0f);
		gage->vertexWk[2].vtx = D3DXVECTOR3(gage->pos.x, gage->pos.y + GAGE_SIZE_Y, 0.0f);
		gage->vertexWk[3].vtx = D3DXVECTOR3(gage->pos.x + GAGE_SIZE_X, gage->pos.y + GAGE_SIZE_Y, 0.0f);

		// rhwの設定
		gage->vertexWk[0].rhw =
		gage->vertexWk[1].rhw =
		gage->vertexWk[2].rhw =
		gage->vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		gage->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gage2->vertexWk2[0].vtx = D3DXVECTOR3(gage2->pos.x, gage2->pos.y, 0.0f);
		gage2->vertexWk2[1].vtx = D3DXVECTOR3(gage2->pos.x + GAGE2_SIZE_X, gage2->pos.y, 0.0f);
		gage2->vertexWk2[2].vtx = D3DXVECTOR3(gage2->pos.x, gage2->pos.y + GAGE2_SIZE_Y, 0.0f);
		gage2->vertexWk2[3].vtx = D3DXVECTOR3(gage2->pos.x + GAGE2_SIZE_X, gage2->pos.y + GAGE2_SIZE_Y, 0.0f);

		// rhwの設定
		gage2->vertexWk2[0].rhw =
		gage2->vertexWk2[1].rhw =
		gage2->vertexWk2[2].rhw =
		gage2->vertexWk2[3].rhw = 1.0f;

		// 反射光の設定
		gage2->vertexWk2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage2->vertexWk2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage2->vertexWk2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage2->vertexWk2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage2->vertexWk2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage2->vertexWk2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gage5->vertexWk5[0].vtx = D3DXVECTOR3(gage5->pos.x, gage5->pos.y, 0.0f);
		gage5->vertexWk5[1].vtx = D3DXVECTOR3(gage5->pos.x + GAGE5_SIZE_X, gage5->pos.y, 0.0f);
		gage5->vertexWk5[2].vtx = D3DXVECTOR3(gage5->pos.x, gage5->pos.y + GAGE5_SIZE_Y, 0.0f);
		gage5->vertexWk5[3].vtx = D3DXVECTOR3(gage5->pos.x + GAGE5_SIZE_X, gage5->pos.y + GAGE5_SIZE_Y, 0.0f);

		// rhwの設定
		gage5->vertexWk5[0].rhw =
		gage5->vertexWk5[1].rhw =
		gage5->vertexWk5[2].rhw =
		gage5->vertexWk5[3].rhw = 1.0f;

		// 反射光の設定
		gage5->vertexWk5[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage5->vertexWk5[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage5->vertexWk5[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage5->vertexWk5[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage5->vertexWk5[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage5->vertexWk5[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage5->vertexWk5[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage5->vertexWk5[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		// 頂点座標の設定
		gage3->vertexWk3[0].vtx = D3DXVECTOR3(gage3->pos.x, gage3->pos.y, 0.0f);
		gage3->vertexWk3[1].vtx = D3DXVECTOR3(gage3->pos.x + GAGE3_SIZE_X, gage3->pos.y, 0.0f);
		gage3->vertexWk3[2].vtx = D3DXVECTOR3(gage3->pos.x, gage3->pos.y + GAGE3_SIZE_Y, 0.0f);
		gage3->vertexWk3[3].vtx = D3DXVECTOR3(gage3->pos.x + GAGE3_SIZE_X, gage3->pos.y + GAGE3_SIZE_Y, 0.0f);

		// rhwの設定
		gage3->vertexWk3[0].rhw =
		gage3->vertexWk3[1].rhw =
		gage3->vertexWk3[2].rhw =
		gage3->vertexWk3[3].rhw = 1.0f;

		// 反射光の設定
		gage3->vertexWk3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage3->vertexWk3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage3->vertexWk3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage3->vertexWk3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage3->vertexWk3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage3->vertexWk3[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage3->vertexWk3[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage3->vertexWk3[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gage4->vertexWk4[0].vtx = D3DXVECTOR3(gage4->pos.x, gage4->pos.y, 0.0f);
		gage4->vertexWk4[1].vtx = D3DXVECTOR3(gage4->pos.x + GAGE4_SIZE_X, gage4->pos.y, 0.0f);
		gage4->vertexWk4[2].vtx = D3DXVECTOR3(gage4->pos.x, gage4->pos.y + GAGE4_SIZE_Y, 0.0f);
		gage4->vertexWk4[3].vtx = D3DXVECTOR3(gage4->pos.x + GAGE4_SIZE_X, gage4->pos.y + GAGE4_SIZE_Y, 0.0f);

		// rhwの設定
		gage4->vertexWk4[0].rhw =
		gage4->vertexWk4[1].rhw =
		gage4->vertexWk4[2].rhw =
		gage4->vertexWk4[3].rhw = 1.0f;

		// 反射光の設定
		gage4->vertexWk4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage4->vertexWk4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage4->vertexWk4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage4->vertexWk4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage4->vertexWk4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage4->vertexWk4[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//頂点座標の設定
		gage6->vertexWk6[0].vtx = D3DXVECTOR3(gage6->pos.x, gage6->pos.y, 0.0f);
		gage6->vertexWk6[1].vtx = D3DXVECTOR3(gage6->pos.x + GAGE6_SIZE_X, gage6->pos.y, 0.0f);
		gage6->vertexWk6[2].vtx = D3DXVECTOR3(gage6->pos.x, gage6->pos.y + GAGE6_SIZE_Y, 0.0f);
		gage6->vertexWk6[3].vtx = D3DXVECTOR3(gage6->pos.x + GAGE6_SIZE_X, gage6->pos.y + GAGE_SIZE_Y, 0.0f);

		// rhwの設定
		gage6->vertexWk6[0].rhw =
		gage6->vertexWk6[1].rhw =
		gage6->vertexWk6[2].rhw =
		gage6->vertexWk6[3].rhw = 1.0f;

		// 反射光の設定
		gage6->vertexWk6[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage6->vertexWk6[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage6->vertexWk6[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gage6->vertexWk6[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		gage6->vertexWk6[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gage6->vertexWk6[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gage6->vertexWk6[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gage6->vertexWk6[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGage(void)
{
	GAGE *gage = gageWk;				// gageのポインターを初期化
	GAGE2 *gage2 = gageWk2;				// gage2のポインターを初期化
	GAGE3 *gage3 = gageWk3;				// gage3のポインターを初期化
	GAGE4 *gage4 = gageWk4;				// gage4のポインターを初期化
	GAGE5 *gage5 = gageWk5;				// gage5のポインターを初期化
	GAGE6 *gage6 = gageWk6;				// gage6のポインターを初期化

	CHARA *charaWk = GetPlayer(0);

	// 頂点座標の設定
	gage2->vertexWk2[0].vtx = D3DXVECTOR3(gage2->pos.x-0.5f, gage2->pos.y - 0.5f, 0.0f);
	gage2->vertexWk2[1].vtx = D3DXVECTOR3(gage2->pos.x + charaWk->HP - 0.5f, gage2->pos.y - 0.5f, 0.0f);
	gage2->vertexWk2[2].vtx = D3DXVECTOR3(gage2->pos.x - 0.5f, gage2->pos.y + GAGE2_SIZE_Y - 0.5f, 0.0f);
	gage2->vertexWk2[3].vtx = D3DXVECTOR3(gage2->pos.x + charaWk->HP - 0.5f, gage2->pos.y + GAGE2_SIZE_Y - 0.5f, 0.0f);

	gage->vertexWk[0].vtx = D3DXVECTOR3(gage->pos.x-0.5f, gage->pos.y-0.5f, 0.0f);
	gage->vertexWk[1].vtx = D3DXVECTOR3(gage->pos.x + GAGE_SIZE_X-0.5f, gage->pos.y-0.5f, 0.0f);
	gage->vertexWk[2].vtx = D3DXVECTOR3(gage->pos.x-0.5f, gage->pos.y + GAGE_SIZE_Y-0.5f, 0.0f);
	gage->vertexWk[3].vtx = D3DXVECTOR3(gage->pos.x + GAGE_SIZE_X-0.5f, gage->pos.y + GAGE_SIZE_Y-0.5f, 0.0f);

	gage5->vertexWk5[0].vtx = D3DXVECTOR3(gage5->pos.x - 0.5f, gage5->pos.y - 0.5f, 0.0f);
	gage5->vertexWk5[1].vtx = D3DXVECTOR3(gage5->pos.x + GAGE5_SIZE_X - 0.5f, gage5->pos.y - 0.5f, 0.0f);
	gage5->vertexWk5[2].vtx = D3DXVECTOR3(gage5->pos.x - 0.5f, gage5->pos.y + GAGE5_SIZE_Y - 0.5f, 0.0f);
	gage5->vertexWk5[3].vtx = D3DXVECTOR3(gage5->pos.x + GAGE5_SIZE_X - 0.5f, gage5->pos.y + GAGE5_SIZE_Y - 0.5f, 0.0f);


	// 頂点座標の設定
	gage4->vertexWk4[0].vtx = D3DXVECTOR3(gage4->pos.x, gage4->pos.y, 0.0f);
	gage4->vertexWk4[1].vtx = D3DXVECTOR3(gage4->pos.x + charaWk->HP, gage4->pos.y, 0.0f);
	gage4->vertexWk4[2].vtx = D3DXVECTOR3(gage4->pos.x, gage4->pos.y + GAGE4_SIZE_Y, 0.0f);
	gage4->vertexWk4[3].vtx = D3DXVECTOR3(gage4->pos.x + charaWk->HP, gage4->pos.y + GAGE4_SIZE_Y, 0.0f);

	gage3->vertexWk3[0].vtx = D3DXVECTOR3(gage3->pos.x - 0.5f, gage3->pos.y - 0.5f, 0.0f);
	gage3->vertexWk3[1].vtx = D3DXVECTOR3(gage3->pos.x + GAGE3_SIZE_X - 0.5f, gage3->pos.y - 0.5f, 0.0f);
	gage3->vertexWk3[2].vtx = D3DXVECTOR3(gage3->pos.x - 0.5f, gage3->pos.y + GAGE3_SIZE_Y - 0.5f, 0.0f);
	gage3->vertexWk3[3].vtx = D3DXVECTOR3(gage3->pos.x + GAGE3_SIZE_X - 0.5f, gage3->pos.y + GAGE3_SIZE_Y - 0.5f, 0.0f);

	gage6->vertexWk6[0].vtx = D3DXVECTOR3(gage6->pos.x - 0.5f, gage6->pos.y - 0.5f, 0.0f);
	gage6->vertexWk6[1].vtx = D3DXVECTOR3(gage6->pos.x + GAGE6_SIZE_X - 0.5f, gage6->pos.y - 0.5f, 0.0f);
	gage6->vertexWk6[2].vtx = D3DXVECTOR3(gage6->pos.x - 0.5f, gage6->pos.y + GAGE6_SIZE_Y - 0.5f, 0.0f);
	gage6->vertexWk6[3].vtx = D3DXVECTOR3(gage6->pos.x + GAGE6_SIZE_X - 0.5f, gage6->pos.y + GAGE6_SIZE_Y - 0.5f, 0.0f);


}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextuerGage(void)
{
	GAGE2 *gage2 = gageWk2;				// gage2のポインターを初期化
	GAGE4 *gage4 = gageWk4;				// gage4のポインターを初期化

	CHARA *charaWk = GetPlayer(0);

	// テクスチャ座標の設定
	gage2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	gage2->vertexWk2[1].tex = D3DXVECTOR2((float)charaWk->HP / charaWk->HPzan, 0.0f);
	gage2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	gage2->vertexWk2[3].tex = D3DXVECTOR2((float)charaWk->HP / charaWk->HPzan, 1.0f);

	// テクスチャ座標の設定
	gage4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	gage4->vertexWk4[1].tex = D3DXVECTOR2((float)charaWk->HP / charaWk->HPzan, 0.0f);
	gage4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	gage4->vertexWk4[3].tex = D3DXVECTOR2((float)charaWk->HP / charaWk->HPzan, 1.0f);

}
//=============================================================================
// gage取得関数
//=============================================================================
GAGE *GetGage(int no)
{
	return(&gageWk[no]);
}
GAGE2 *GetGage2(int no)
{
	return(&gageWk2[no]);
}
GAGE3 *GetGage3(int no)
{
	return(&gageWk3[no]);
}
GAGE4 *GetGage4(int no)
{
	return(&gageWk4[no]);
}
GAGE5 *GetGage5(int no)
{
	return(&gageWk5[no]);
}
GAGE6 *GetGage6(int no)
{
	return(&gageWk6[no]);
}

