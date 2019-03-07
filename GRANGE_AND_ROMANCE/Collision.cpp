//=============================================================================
//
// 当たり判定処理 [Collision.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Collision.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ポインタの初期化
	Collision->D3DTexture = NULL;
	Collision->Mesh = NULL;
	Collision->D3DXMatBuff = NULL;

	// 場所、大きさの設定
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
	Collision->rot = Collision->rot;
	Collision->scl = D3DXVECTOR3(Radius, Radius, Radius);

	if (type == 0)
	{
		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(BALL_XFILE,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Collision->D3DXMatBuff,
			NULL,
			&Collision->NumMat,
			&Collision->Mesh)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitCollision(COLLISION *Collision)
{
	// テクスチャの開放
	SAFE_RELEASE(Collision->D3DTexture);

	// メッシュの開放
	SAFE_RELEASE(Collision->Mesh);

	// マテリアルの開放
	SAFE_RELEASE(Collision->D3DXMatBuff);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix)
{
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCollision(COLLISION *Collision)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Collision->mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, Collision->scl.x, Collision->scl.y, Collision->scl.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Collision->rot.y, Collision->rot.x, Collision->rot.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Collision->pos.x, Collision->pos.y, Collision->pos.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Collision->mtxWorld);

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)Collision->D3DXMatBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)Collision->NumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, Collision->D3DTexture);

		// 描画
		Collision->Mesh->DrawSubset(nCntMat);
	}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}