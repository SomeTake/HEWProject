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
	playerWk.reverse = false;

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
		// 移動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Walk])))
		{
			return E_FAIL;
		}

		// 右移動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Rightwalk])))
		{
			return E_FAIL;
		}

		// 左移動
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Leftwalk])))
		{
			return E_FAIL;
		}

		// ジャブ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Jab])))
		{
			return E_FAIL;
		}

		// ストレート
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Straight])))
		{
			return E_FAIL;
		}

		// アッパー
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Upper])))
		{
			return E_FAIL;
		}

		// キック
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Kick])))
		{
			return E_FAIL;
		}

		// アイテムを拾う
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Pickup])))
		{
			return E_FAIL;
		}

		// 攻撃（アイテム所持）
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Attackitem])))
		{
			return E_FAIL;
		}

		// アイテムを投げる
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Throwitem])))
		{
			return E_FAIL;
		}

		// 被ダメージ
		if (FAILED(SetupCallbackKeyframes(playerWk.Animation, CharaStateAnim[Reaction])))
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

	// 向き制御
	if (playerWk.reverse == false)
	{
		playerWk.rot.y = D3DX_PI * VALUE_HALF;
	}
	else if(playerWk.reverse == true)
	{
		playerWk.rot.y = D3DX_PI * -VALUE_HALF;
	}

	// キャラクターのアニメーション変更
	ControlPlayer();

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
//操作＆アニメーション変更
//=============================================================================
void ControlPlayer(void)
{
	// 攻撃中などの状態では向き変更ができない
	if (playerWk.Animation->CurrentAnimID != Jab && playerWk.Animation->CurrentAnimID != Straight
		&& playerWk.Animation->CurrentAnimID != Upper && playerWk.Animation->CurrentAnimID != Kick
		&& playerWk.Animation->CurrentAnimID != Attackitem && playerWk.Animation->CurrentAnimID != Throwitem
		&& playerWk.Animation->CurrentAnimID != Pickup)
	{
		// 向きの変更
		if (playerWk.reverse == false)
		{
			if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(0, BUTTON_LEFT) || IsButtonPressed(0, STICK_LEFT))
			{
				playerWk.reverse = true;
			}
		}
		else if (playerWk.reverse == true)
		{
			if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(0, BUTTON_RIGHT) || IsButtonPressed(0, STICK_RIGHT))
			{
				playerWk.reverse = false;
			}
		}
	}

	// アニメーションの変更
	switch (playerWk.Animation->CurrentAnimID)
	{
	case Idle:
		// ジャブ PS4□
		if(GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾う PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
		}
		// 前進
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT) 
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Walk, Data[Walk].Spd);
		}
		// 右ステップ
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// 左ステップ
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Walk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{

		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Rightwalk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Leftwalk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Jab:
		// 攻撃ヒット時追加入力でストレート攻撃が出る
		// ストレート PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Straight, Data[Straight].Spd);
		}
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Straight:
		// 攻撃ヒット時追加入力でアッパー攻撃が出る
		// アッパー PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Upper, Data[Upper].Spd);
		}

		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Upper:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Kick:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
			playerWk.HitFrag = false;
		}
		break;
	case Pickup:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			playerWk.UseItem = true;
			playerWk.HitFrag = false;
		}
		break;
	case Idleitem:
		// アイテム攻撃 PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(0, BUTTON_A))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Attackitem, Data[Attackitem].Spd);
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_B))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(0, BUTTON_C))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Throwitem, Data[Throwitem].Spd);
		}
		// 前進
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Walk, Data[Walk].Spd);
		}
		// 右ステップ
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// 左ステップ
		else if (GetKeyboardPress(playerWk.reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(0, playerWk.reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Attackitem:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			playerWk.HitFrag = false;
		}
		break;
	case Throwitem:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			playerWk.UseItem = false;
			playerWk.HitFrag = false;
		}
		break;
	case Reaction:
		// アニメーション終了で待機に戻る
		if (playerWk.Animation->MotionEnd == true)
		{
			if (playerWk.UseItem == true)
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk.Animation->ChangeAnimation(playerWk.Animation, Idle, Data[Idle].Spd);
			}
			playerWk.HitFrag = false;
		}
		break;
	default:
		break;
	}
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
	case Walk:
		playerWk.move.x -= sinf(playerWk.rot.y) * VALUE_FRONTWALK;
		playerWk.move.z -= cosf(playerWk.rot.y) * VALUE_FRONTWALK;
		break;
		// 手前移動中の座標処理
	case Rightwalk:
		playerWk.move.x -= sinf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk.move.z -= cosf(playerWk.rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
		// 奥移動中の座標処理
	case Leftwalk:
		playerWk.move.x -= sinf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk.move.z -= cosf(playerWk.rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
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