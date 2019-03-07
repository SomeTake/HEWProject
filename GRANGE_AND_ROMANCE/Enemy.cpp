//=============================================================================
//
// エネミー処理 [Enemy.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY EnemyWk[ENEMY_NUM];	// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・回転・スケールの初期設定
	g_posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclEnemy = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	g_pD3DTextureEnemy = NULL;
	g_pD3DXMeshEnemy = NULL;
	g_pD3DXBuffMatEnemy = NULL;
	g_nNumMatEnemy = 0;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(ENEMY_XFILE,				// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
		pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
		NULL,					// 隣接性データを含むバッファへのポインタ
		&g_pD3DXBuffMatEnemy,	// マテリアルデータを含むバッファへのポインタ
		NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
		&g_nNumMatEnemy,		// D3DXMATERIAL構造体の数
		&g_pD3DXMeshEnemy)))	// ID3DXMeshインターフェイスへのポインタのアドレス
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureEnemy);	// 読み込むメモリー
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}

	if (g_pD3DXMeshEnemy != NULL)
	{// メッシュの開放
		g_pD3DXMeshEnemy->Release();
		g_pD3DXMeshEnemy = NULL;
	}

	if (g_pD3DXBuffMatEnemy != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatEnemy->Release();
		g_pD3DXBuffMatEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_sclEnemy.x, g_sclEnemy.y, g_sclEnemy.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotEnemy.y, g_rotEnemy.x, g_rotEnemy.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_posEnemy.x, g_posEnemy.y, g_posEnemy.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemy->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEnemy);

		// 描画
		g_pD3DXMeshEnemy->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
