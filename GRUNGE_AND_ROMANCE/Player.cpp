//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Struct.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "D3DXAnimation.h"
#include "Effect.h"
#include "Onna.h"
#include "Blackhole.h"
#include "Debugproc.h"
#include "Game.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CHARA playerWk[PLAYER_NUM];

D3DXMATRIX WorldMtxPlayer;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// 位置・回転・スケールの初期設定
		playerWk[pn].pos = FIRST_PLAYER_POS;
		playerWk[pn].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerWk[pn].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerWk[pn].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ステータス等の初期設定
		playerWk[pn].HP = PLAYER_HP_MAX;
		playerWk[pn].HPzan = playerWk[pn].HP;
		playerWk[pn].reverse = false;
	}

	if (type == 0)
	{
		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			//オブジェクトの初期化
			playerWk[pn].Animation = CreateAnimationObject();

			// xFileの読み込み
			if (FAILED(Load_xFile(playerWk[pn].Animation, CHARA_XFILE, "Player")))
			{
				return E_FAIL;
			}

			// AnimationCallbackをセットする
			// 移動
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Walk])))
			{
				return E_FAIL;
			}

			// 右移動
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Rightwalk])))
			{
				return E_FAIL;
			}

			// 左移動
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Leftwalk])))
			{
				return E_FAIL;
			}

			// ジャブ
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Jab])))
			{
				return E_FAIL;
			}

			// ストレート
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Straight])))
			{
				return E_FAIL;
			}

			// アッパー
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Upper])))
			{
				return E_FAIL;
			}

			// キック
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Kick])))
			{
				return E_FAIL;
			}

			// アイテムを拾う
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Pickup])))
			{
				return E_FAIL;
			}

			// 攻撃（アイテム所持）
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Attackitem])))
			{
				return E_FAIL;
			}

			// アイテムを投げる
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Throwitem])))
			{
				return E_FAIL;
			}

			// 被ダメージ
			if (FAILED(SetupCallbackKeyframes(playerWk[pn].Animation, CharaStateAnim[Reaction])))
			{
				return E_FAIL;
			}
		}

		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			// AnimationSetを初期化する
			for (int i = 0; i < playerWk[pn].Animation->AnimSetNum; i++)
			{
				if (FAILED(playerWk[pn].Animation->InitAnimation(playerWk[pn].Animation, CharaStateAnim[i], i)))
				{
					return E_FAIL;
				}
			}
			playerWk[pn].Animation->CurrentAnimID = Idle;
		}

		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			// アニメーション間の補完を設定
			for (int i = 0; i < AnimMax; i++)
			{
				playerWk[pn].Animation->SetShiftTime(playerWk[pn].Animation, i, Data[i].ShiftTime);
			}
		}

		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			// 当たり判定の初期化
			for (int i = 0; i < HIT_CHECK_NUM; i++)
			{
				D3DXMATRIX Mtx = GetBoneMatrix(playerWk[pn].Animation, CharaHitPos[i]);
				InitCollision(0, &playerWk[pn].Collision[i], Mtx, HitRadius[i]);
			}
		}
	}
	else
	{
		for (int pn = 0; pn < PLAYER_NUM; pn++)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// 当たり判定をリリース
		for (int i = 0; i < HIT_CHECK_NUM; i++)
		{
			UninitCollision(&playerWk[pn].Collision[i]);
		}

		// アニメーションをリリース
		playerWk[pn].Animation->UninitAnimation(playerWk[pn].Animation);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	ENEMY *OnnaWk = GetOnna(0);
	ENEMY *BlackholeWk = GetBlackhole(0);

#ifdef _DEBUG
	PrintDebugProc("ヒットフラグ %s", playerWk[0].HitFrag ? "true" : "false");
#endif

	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// アニメーションを更新
		playerWk[pn].Animation->UpdateAnimation(playerWk[pn].Animation, TIME_PER_FRAME);

		// 向き制御
		if (playerWk[pn].reverse == false)
		{
			playerWk[pn].rot.y = D3DX_PI * VALUE_HALF;
		}
		else if (playerWk[pn].reverse == true)
		{
			playerWk[pn].rot.y = D3DX_PI * -VALUE_HALF;
		}

		// キャラクターのアニメーション変更
		ControlPlayer(pn);

		// 座標移動
		MovePlayer(pn);

		// 当たり判定座標の更新
		D3DXMATRIX Mtx;
		for (int i = 0; i < HIT_CHECK_NUM; i++)
		{
			Mtx = GetBoneMatrix(playerWk[pn].Animation, CharaHitPos[i]);
			UpdateCollision(&playerWk[pn].Collision[i], Mtx);
		}

		// 攻撃による当たり判定
		if (playerWk[pn].HitFrag == false)
		{
			// 女.xとの当たり判定
			for (int num = 0; num < ONNA_NUM; num++)
			{
				if (OnnaWk[num].use == true)
				{
					if (HitCheckPToE(&playerWk[pn], &OnnaWk[num]) == true)
					{
						// 当たったあとの動き
						playerWk[pn].HitFrag = true;
						HitAction(pn, &OnnaWk[num]);
					}
				}
			}

			// ブラックホールくんとの当たり判定
			for (int num = 0; num < BLACKHOLE_NUM; num++)
			{
				if (BlackholeWk[num].use == true)
				{
					if (HitCheckPToE(&playerWk[pn], &BlackholeWk[num]) == true)
					{
						// 当たったあとの動き
						playerWk[num].HitFrag = true;
						HitAction(pn, &BlackholeWk[num]);
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX ScaleMatrix, RotMatrix, TransMatrix, CapsuleMatrix, BallMatrix;

	for (int pn = 0; pn < PLAYER_NUM; pn++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&WorldMtxPlayer);

		// スケールを反映
		D3DXMatrixScaling(&ScaleMatrix, playerWk[pn].scl.x, playerWk[pn].scl.y, playerWk[pn].scl.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&ScaleMatrix, playerWk[pn].rot.y, playerWk[pn].rot.x, playerWk[pn].rot.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &ScaleMatrix);

		// 移動を反映
		D3DXMatrixTranslation(&TransMatrix, playerWk[pn].pos.x, playerWk[pn].pos.y, playerWk[pn].pos.z);
		D3DXMatrixMultiply(&WorldMtxPlayer, &WorldMtxPlayer, &TransMatrix);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &WorldMtxPlayer);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// レンダリング
		playerWk[pn].Animation->DrawAnimation(playerWk[pn].Animation, &WorldMtxPlayer);

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

#ifdef _DEBUG
		for (int i = 0; i < HIT_CHECK_NUM; i++)
		{
			// プレイヤーの当たり判定用ボールを描画する
			DrawCollision(&playerWk[pn].Collision[i]);
		}
#endif

	}
}

//=============================================================================
// プレイヤーの情報を取得する
// 引数：pn プレイヤー番号
//=============================================================================
CHARA *GetPlayer(int pn)
{
	return &playerWk[pn];
}

//=============================================================================
//操作＆アニメーション変更
//=============================================================================
void ControlPlayer(int pn)
{
	// 攻撃中などの状態では向き変更ができない
	if (playerWk[pn].Animation->CurrentAnimID != Jab && playerWk[pn].Animation->CurrentAnimID != Straight
		&& playerWk[pn].Animation->CurrentAnimID != Upper && playerWk[pn].Animation->CurrentAnimID != Kick
		&& playerWk[pn].Animation->CurrentAnimID != Attackitem && playerWk[pn].Animation->CurrentAnimID != Throwitem
		&& playerWk[pn].Animation->CurrentAnimID != Pickup)
	{
		// 向きの変更
		if (playerWk[pn].reverse == false)
		{
			if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(pn, BUTTON_LEFT) || IsButtonPressed(pn, STICK_LEFT))
			{
				playerWk[pn].reverse = true;
			}
		}
		else if (playerWk[pn].reverse == true)
		{
			if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(pn, BUTTON_RIGHT) || IsButtonPressed(pn, STICK_RIGHT))
			{
				playerWk[pn].reverse = false;
			}
		}
	}

	// アニメーションの変更
	switch (playerWk[pn].Animation->CurrentAnimID)
	{
	case Idle:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾う PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
		}
		// 前進
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Walk, Data[Walk].Spd);
		}
		// 右ステップ
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// 左ステップ
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Walk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{

		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Rightwalk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Leftwalk:
		// ジャブ PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Jab, Data[Jab].Spd);
			}
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを拾うor投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Pickup, Data[Pickup].Spd);
			}
		}
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
		}
		// キーリリースで待機に戻る
		else
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
		}
		break;
	case Jab:
		// 攻撃ヒット時追加入力でストレート攻撃が出る
		if (playerWk[pn].HitFrag)
		{
			// ストレート PS4□
			if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Straight, Data[Straight].Spd);
				playerWk[pn].HitFrag = false;
			}
		}
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Straight:
		// 攻撃ヒット時追加入力でアッパー攻撃が出る
		if (playerWk[pn].HitFrag)
		{
			// アッパー PS4□
			if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Upper, Data[Upper].Spd);
				playerWk[pn].HitFrag = false;
			}
		}
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Upper:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Kick:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
			playerWk[pn].HitFrag = false;
		}
		break;
	case Pickup:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			playerWk[pn].UseItem = true;
			playerWk[pn].HitFrag = false;
		}
		break;
	case Idleitem:
		// アイテム攻撃 PS4□
		if (GetKeyboardTrigger(DIK_J) || IsButtonTriggered(pn, BUTTON_A))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Attackitem, Data[Attackitem].Spd);
		}
		// キック PS4×
		else if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(pn, BUTTON_B))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Kick, Data[Kick].Spd);
		}
		// アイテムを投げる PS4○
		else if (GetKeyboardTrigger(DIK_N) || IsButtonTriggered(pn, BUTTON_C))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Throwitem, Data[Throwitem].Spd);
		}
		// 前進
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_RIGHT : DIK_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_RIGHT : BUTTON_LEFT)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_RIGHT : STICK_LEFT))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Walk, Data[Walk].Spd);
		}
		// 右ステップ
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_DOWN : DIK_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_DOWN : BUTTON_UP)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_DOWN : STICK_UP))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Rightwalk, Data[Rightwalk].Spd);
		}
		// 左ステップ
		else if (GetKeyboardPress(playerWk[pn].reverse == false ? DIK_UP : DIK_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? BUTTON_UP : BUTTON_DOWN)
			|| IsButtonPressed(pn, playerWk[pn].reverse == false ? STICK_UP : STICK_DOWN))
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Leftwalk, Data[Leftwalk].Spd);
		}
		break;
	case Attackitem:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			playerWk[pn].HitFrag = false;
		}
		break;
	case Throwitem:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			playerWk[pn].UseItem = false;
			playerWk[pn].HitFrag = false;
		}
		break;
	case Reaction:
		// アニメーション終了で待機に戻る
		if (playerWk[pn].Animation->MotionEnd == true)
		{
			if (playerWk[pn].UseItem == true)
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idleitem, Data[Idleitem].Spd);
			}
			else
			{
				playerWk[pn].Animation->ChangeAnimation(playerWk[pn].Animation, Idle, Data[Idle].Spd);
			}
			playerWk[pn].HitFrag = false;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//座標移動
//=============================================================================
void MovePlayer(int pn)
{
	// アクションに合わせた座標移動
	switch (playerWk[pn].Animation->CurrentAnimID)
	{
		// 前移動中の座標処理
	case Walk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y) * VALUE_FRONTWALK;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y) * VALUE_FRONTWALK;
		break;
		// 手前移動中の座標処理
	case Rightwalk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y + D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
		// 奥移動中の座標処理
	case Leftwalk:
		playerWk[pn].move.x -= sinf(playerWk[pn].rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		playerWk[pn].move.z -= cosf(playerWk[pn].rot.y - D3DX_PI * VALUE_HALF) * VALUE_SIDESTEP;
		break;
	default:
		break;
	}

	// 位置移動
	playerWk[pn].pos.x += playerWk[pn].move.x;
	playerWk[pn].pos.y += playerWk[pn].move.y;
	playerWk[pn].pos.z += playerWk[pn].move.z;

	// (半径*角度)＋基準座標でプレイヤーの座標を計算する

	// 移動量をリセットする
	playerWk[pn].move.x = 0.0f;
	playerWk[pn].move.y = 0.0f;
	playerWk[pn].move.z = 0.0f;
}

//=============================================================================
// 攻撃ヒット時のアクション
//=============================================================================
void HitAction(int pn, ENEMY *enemy)
{
	switch (playerWk[pn].Animation->CurrentAnimID)
	{
	case Jab:
		// ダメージ
		AddDamageEnemy(enemy, Data[Jab].Damage);
		// SE
		// エフェクト
		break;
	case Straight:
		// ダメージ
		AddDamageEnemy(enemy, Data[Straight].Damage);
		// SE
		// エフェクト
		break;
	case Upper:
		// ダメージ
		AddDamageEnemy(enemy, Data[Upper].Damage);
		// SE
		// エフェクト
		break;
	case Kick:
		// ダメージ
		AddDamageEnemy(enemy, Data[Kick].Damage);
		// SE
		// エフェクト
		break;
	case Pickup:
		break;
	case Attackitem:
		// ダメージ
		AddDamageEnemy(enemy, Data[Attackitem].Damage);
		// SE
		// エフェクト
		break;
	case Throwitem:
		// ダメージ
		AddDamageEnemy(enemy, Data[Throwitem].Damage);
		// SE
		// エフェクト
		break;
	default:
		break;
	}

}