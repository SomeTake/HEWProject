//=============================================================================
//
// バーベル処理 [Babel.cpp]
// Author : HAL東京 GP11B341-01 80163 飯塚　春輝
//
//=============================================================================
#include "Babel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureBabel;	// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshBabel;		// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffBabel;// メッシュのマテリアル情報を格納
DWORD				g_aNumMatBabel;		// 属性情報の総数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ITEM itemWk[BABEL_NUM];	// アイテム構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBabel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BABEL_NUM; en++)
	{
		// 位置・回転・スケールの初期設定
		itemWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-90.0f, 90.0f), 0.0f, CreateRandomFloat(-90.0f, 10.0f));
		itemWk[en].rot = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
		itemWk[en].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

		itemWk[en].D3DTexture = NULL;
		itemWk[en].D3DXMesh = NULL;
		itemWk[en].D3DXBuffMat = NULL;
		itemWk[en].NumMat = 0;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(BABEL_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&itemWk[en].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&itemWk[en].NumMat,							// D3DXMATERIAL構造体の数
				&itemWk[en].D3DXMesh)))						// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,								// ファイルの名前
				&itemWk[en].D3DTexture);						// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBabel(void)
{
	for (int en = 0; en < BABEL_NUM; en++)
	{

		if (g_pD3DTextureBabel != NULL)
		{// テクスチャの開放
			g_pD3DTextureBabel->Release();
			g_pD3DTextureBabel = NULL;
		}

		if (g_pMeshBabel != NULL)
		{// メッシュの開放
			g_pMeshBabel->Release();
			g_pMeshBabel = NULL;
		}

		if (g_pD3DXMatBuffBabel != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffBabel->Release();
			g_pD3DXMatBuffBabel = NULL;
		}

	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBabel(void)
{
	//itemWk[0].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	//itemWk[1].pos = D3DXVECTOR3(30.0f, 0.0f, 10.0f);
	//itemWk[2].pos = D3DXVECTOR3(50.0f, 0.0f, 10.0f);
	//itemWk[3].pos = D3DXVECTOR3(70.0f, 0.0f, 10.0f);
	//itemWk[4].pos = D3DXVECTOR3(90.0f, 0.0f, 10.0f);
	//itemWk[5].pos = D3DXVECTOR3(-10.0f, 0.0f, 30.0f);
	//itemWk[6].pos = D3DXVECTOR3(-30.0f, 0.0f, 50.0f);
	//itemWk[7].pos = D3DXVECTOR3(-50.0f, 0.0f, 70.0f);
	//itemWk[8].pos = D3DXVECTOR3(-70.0f, 0.0f, 90.0f);
	//itemWk[9].pos = D3DXVECTOR3(-90.0f, 0.0f, 100.0f);

	//for (int en = 0; en < BABEL_NUM; en++)
	//{
	//	itemWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-90.0f, 90.0f), 0.0f, CreateRandomFloat(-90.0f, 10.0f));

	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBabel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < BABEL_NUM; en++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, itemWk[en].scl.x, itemWk[en].scl.y, itemWk[en].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, itemWk[en].rot.y, itemWk[en].rot.x, itemWk[en].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, itemWk[en].pos.x, itemWk[en].pos.y, itemWk[en].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)itemWk[en].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)itemWk[en].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, itemWk[en].D3DTexture);

			// 描画
			itemWk[en].D3DXMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// アイテムの情報を取得する
// 引数：en アイテム番号
//=============================================================================
ITEM *GetItem(int en)
{
	return &itemWk[en];
}