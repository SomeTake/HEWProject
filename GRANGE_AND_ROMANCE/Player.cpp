//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "D3DXAnimation.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CHARA playerWk;

D3DXMATRIX WorldMtxPlayer;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・回転・スケールの初期設定
	playerWk.pos = FIRST_PLAYER_POS;
	playerWk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	playerWk.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	playerWk.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// ステータス等の初期設定
	playerWk.HP = 0;
	playerWk.HPzan = playerWk.HP;
	playerWk.SP = 0;

	if (type == 0)
	{
		//オブジェクトの初期化
		playerWk.Animation = CreateAnimationObject();

		// xFileの読み込み
		if (FAILED(Load_xFile(playerWk.Animation, CHARA_XFILE, "Player")))
		{
			return E_FAIL;
		}

		// AnimationCallbackをセットする
		// 前歩き
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Frontwalk])))
		{
			return E_FAIL;
		}
		// 後ろ歩き
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Backwalk])))
		{
			return E_FAIL;
		}
		// 横移動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Rightstep])))
		{
			return E_FAIL;
		}
		// 横移動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Leftstep])))
		{
			return E_FAIL;
		}
		// ダメージ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Damage])))
		{
			return E_FAIL;
		}
		// ダウン
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Down])))
		{
			return E_FAIL;
		}
		// ダウンポーズ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Downpose])))
		{
			return E_FAIL;
		}
		// 起き上がり
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Getup])))
		{
			return E_FAIL;
		}
		// パンチ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Punchi])))
		{
			return E_FAIL;
		}
		// キック
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Kick])))
		{
			return E_FAIL;
		}
		// 波動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Hadou])))
		{
			return E_FAIL;
		}
		// 昇竜
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Shoryu])))
		{
			return E_FAIL;
		}
		// SP技
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[SPattack])))
		{
			return E_FAIL;
		}
		// 投げ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Throw])))
		{
			return E_FAIL;
		}
		// 投げスカり
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Miss])))
		{
			return E_FAIL;
		}


		// AnimationSetを初期化する
		for (int i = 0; i < playerWk.Animation->AnimSetNum; i++)
		{
			if (FAILED(playerWk.Animation->InitAnimation(playerWk.Animation, CharaStateAnim[i], i)))
			{
				return E_FAIL;
			}
		}
		playerWk.Animation->CurrentAnimID = Idle;

		// アニメーション間の補完を設定
		for (int i = 0; i < AnimMax; i++)
		{
			playerWk.Animation->SetShiftTime(playerWk.Animation, i, Data[i].ShiftTime);
		}

	}
	else
	{
		playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// アニメーションをリリース
	playerWk.Animation->UninitAnimation(playerWk.Animation);
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
		// アニメーションを更新
		playerWk.Animation->UpdateAnimation(playerWk.Animation, TIME_PER_FRAME);

		// 座標移動
		MovePlayer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX ScaleMatrix, RotMatrix, TransMatrix, CapsuleMatrix, BallMatrix;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMtxPlayer);

	// スケールを反映
	D3DXMatrixScaling(&ScaleMatrix, playerWk.scl.x, playerWk.scl.y, playerWk.scl.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&ScaleMatrix, playerWk.rot.y, playerWk.rot.x, playerWk.rot.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

	// 移動を反映
	D3DXMatrixTranslation(&TransMatrix, playerWk.pos.x, playerWk.pos.y, playerWk.pos.z);
	D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &TransMatrix);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtxPlayer);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// レンダリング
	playerWk.Animation->DrawAnimation(playerWk.Animation, &WorldMtxPlayer);
	
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
//プレイヤーの情報を取得する
//=============================================================================
CHARA *GetPlayer(void)
{
	return &playerWk;
}

//=============================================================================
//座標移動
//=============================================================================
void MovePlayer(void)
{
	// アクションに合わせた座標移動
	switch (playerWk.Animation->CurrentAnimID)
	{
		// 前移動中の座標処理
	case Frontwalk:
		playerWk.move.x -= sinf(playerWk.rot.y) * VALUE_FRONTWALK;
		playerWk.move.z -= cosf(playerWk.rot.y) * VALUE_FRONTWALK;
		break;
		// 後移動中の座標処理
	case Backwalk:
			playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI) * VALUE_BACKWALK;
			playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI) * VALUE_BACKWALK;
		break;
		// 手前移動中の座標処理
	case Rightstep:
		playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		break;
		// 奥移動中の座標処理
	case Leftstep:
		playerWk.move.x -= sinf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		playerWk.move.z -= cosf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_ROTATE;
		break;
	default:
		break;
	}

	// 位置移動
	playerWk.pos.x += playerWk.move.x;
	playerWk.pos.y += playerWk.move.y;
	playerWk.pos.z += playerWk.move.z;

	// (半径*角度)＋基準座標でプレイヤーの座標を計算する

	// 移動量をリセットする
	playerWk.move.x = 0.0f;
	playerWk.move.y = 0.0f;
	playerWk.move.z = 0.0f;	
}