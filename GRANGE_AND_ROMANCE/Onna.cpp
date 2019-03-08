//=============================================================================
//
// 女.x処理 [Onna.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Onna.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ONNA enemyWk[ONNA_NUM];	// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitOnna(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < ONNA_NUM; en++)
	{
		// 位置・回転・スケールの初期設定
		enemyWk[en].HP = ONNA_HP_MAX;
		enemyWk[en].HPzan = enemyWk[en].HP;
		enemyWk[en].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyWk[en].rot = D3DXVECTOR3(0.0f, ONNA_DIRECTION, 0.0f);
		enemyWk[en].scl = D3DXVECTOR3(ONNA_SCALE, ONNA_SCALE, ONNA_SCALE);

		enemyWk[en].D3DTexture = NULL;
		enemyWk[en].D3DXMesh = NULL;
		enemyWk[en].D3DXBuffMat = NULL;
		enemyWk[en].NumMat = 0;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(ONNA_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&enemyWk[en].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&enemyWk[en].NumMat,						// D3DXMATERIAL構造体の数
				&enemyWk[en].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&enemyWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOnna(void)
{
	for (int en = 0; en < ONNA_NUM; en++)
	{
		if (enemyWk[en].D3DTexture != NULL)
		{	// テクスチャの開放
			enemyWk[en].D3DTexture->Release();
			enemyWk[en].D3DTexture = NULL;
		}

		if (enemyWk[en].D3DXMesh != NULL)
		{	// メッシュの開放
			enemyWk[en].D3DXMesh->Release();
			enemyWk[en].D3DXMesh = NULL;
		}

		if (enemyWk[en].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			enemyWk[en].D3DXBuffMat->Release();
			enemyWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOnna(void)
{

	enemyWk[0].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	enemyWk[1].pos = D3DXVECTOR3(30.0f, 0.0f, 10.0f);
	enemyWk[2].pos = D3DXVECTOR3(50.0f, 0.0f, 10.0f);
	enemyWk[3].pos = D3DXVECTOR3(70.0f, 0.0f, 10.0f);
	enemyWk[4].pos = D3DXVECTOR3(90.0f, 0.0f, 10.0f);
	enemyWk[5].pos = D3DXVECTOR3(-10.0f, 0.0f, 30.0f);
	enemyWk[6].pos = D3DXVECTOR3(-30.0f, 0.0f, 50.0f);
	enemyWk[7].pos = D3DXVECTOR3(-50.0f, 0.0f, 70.0f);
	enemyWk[8].pos = D3DXVECTOR3(-70.0f, 0.0f, 90.0f);
	enemyWk[9].pos = D3DXVECTOR3(-90.0f, 0.0f, 100.0f);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOnna(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < ONNA_NUM; en++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, enemyWk[en].scl.x, enemyWk[en].scl.y, enemyWk[en].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, enemyWk[en].rot.y, enemyWk[en].rot.x, enemyWk[en].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, enemyWk[en].pos.x, enemyWk[en].pos.y, enemyWk[en].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)enemyWk[en].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)enemyWk[en].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, enemyWk[en].D3DTexture);

			// 描画
			enemyWk[en].D3DXMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// エネミーの情報を取得する
// 引数：en エネミー番号
//=============================================================================
ONNA *GetOnna(int en)
{
	return &enemyWk[en];
}