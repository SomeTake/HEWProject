//=============================================================================
//
// メイン処理 [main.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "Player.h"
#include "Opening.h"
#include "Title.h"
#include "Game.h"
#include "Ending.h"
#include "Debugproc.h"
#include "Onna.h"
#include "Effect.h"
#include "Blackhole.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"					// ウインドウのクラス名
#define WINDOW_NAME		"GRANGE_AND_ROMANCE"		// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif
int	g_nStage = STAGE_GAME;						// ステージ番号
bool SetWindowCenter(HWND hWnd);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;					// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;			// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
static LPD3DXFONT	g_pD3DXFont = NULL;				// フォントへのポインタ
int					g_nCountFPS;					// FPSカウンタ
#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));

	// 警告
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	DWORD dwExecLastTime;							// 最終実行時間
	DWORD dwFPSLastTime;							// 現在フレーム
	DWORD dwCurrentTime;							// 現在時刻
	DWORD dwFrameCount;								// フレームカウント

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							// 構造体のサイズ
		CS_CLASSDC,									// ウインドウスタイル：CS_HREDRAW / CS_VREDRAW
		WndProc,									// ウインドウプロシージャのアドレス
		0,											// 予備メモリ
		0,											// ウインドウオブジェクト作成時に確保されるメモリサイズ
		hInstance,									// インスタンスハンドル
		NULL,										// アプリのショートカットなどで使用（アイコンの設定）
		LoadCursor(NULL, IDC_ARROW),				// ウインドウのクライアント上のマウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),					// ウインドウのクライアント領域の背景色
		NULL,										// メニュー名
		CLASS_NAME,									// ウインドウクラスの名前
		NULL										// ウインドウのアイコン
	};
	HWND hWnd;										// ウインドウハンドル
	MSG msg;										// ウインドウプロシージャに渡すメッセージ

													// ウィンドウクラスの登録
	if (RegisterClassEx(&wcex) == 0)
	{
		return false;
	}

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,																					// クラス名
		WINDOW_NAME,																				// ウインドウ名
		WS_OVERLAPPEDWINDOW,																		// ウインドウスタイル
		CW_USEDEFAULT,																				// ウインドウの左上座標（X）
		CW_USEDEFAULT,																				// ウインドウの左上座標（Y）
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,											// ウインドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),		// ウインドウ縦幅
		NULL,																						// オーナーウインドウのハンドル
		NULL,																						// メニューハンドル
		hInstance,																					// アプリケーションインスタンスのハンドル
		NULL);																						// ウインドウ作成データ

																									// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);


	// --------------------------------------  メッセージループ---------------------------------------------
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)						//アプリケーションの終了要求
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// ゲーム処理
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	// -----------------------------------------------------------------------------------------------------

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 変数宣言
	static HANDLE Thread_Handle;

	switch (uMsg)
	{
		// 破棄
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		// 非システムキーメッセージ
	case WM_KEYDOWN:
		switch (wParam)
		{
			// ESCキーが押された場合
		case VK_ESCAPE:
			DestroyWindow(hWnd);	// ウインドウを破棄する
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// ウインドウの表示位置を画面中央に設定
	SetWindowCenter(hWnd);

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う

	if (bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// デバッグ
	InitDebugProc();

#endif

	// 入力処理の初期化
	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();
	InitOpening();
	InitTitle();
	InitGame();
	InitEnding();
	InitEffect(true);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if (g_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}

	// デバッグ
	UninitDebugProc();

#endif
	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// 入力処理の終了処理
	UninitInput();

	// オープニングの終了処理
	UninitOpening();

	// タイトルの終了処理
	UninitTitle();

	// ゲームの終了処理
	UninitGame();

	// エンディングの終了処理
	UninitEnding();

	//エフェクトの終了処理
	UninitEffect();

}


//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
#ifdef _DEBUG
	UpdateDebugProc();

#endif

	UpdateInput();
	UpdateCamera();

	// 画面遷移
	switch (g_nStage)
	{
	case STAGE_OPENING:

		// オープニング更新
		UpdateOpening();

		break;

	case STAGE_TITLE:

		// タイトル更新
		UpdateTitle();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetStage(STAGE_GAME);
		}

		break;

	case STAGE_GAME:

		// ゲーム更新
		UpdateGame();

		// エフェクト更新
		UpdateEffect();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetStage(STAGE_ENDING);
		}

		break;

	case STAGE_ENDING:

		// エンディング更新
		UpdateEnding();

		break;
	}

}

//=============================================================================
// 描画処理 引数:カメラ番号
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SetCamera(0);

#ifdef _DEBUG
		DrawDebugProc();
#endif

		// 画面遷移
		switch (g_nStage)
		{
		case STAGE_OPENING:

			// オープニング描画
			DrawOpening();

			break;

		case STAGE_TITLE:

			// タイトル描画
			DrawTitle();

			break;

		case STAGE_GAME:

			// ゲーム描画
			DrawGame();

			//エフェクト描画
			DrawEffect();

			break;

		case STAGE_ENDING:

			// エンディング描画
			DrawEnding();

			break;
		}

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// 再初期化（ゲームループで使用）
//=============================================================================
void ReInit(void)
{
	InitPlayer(1);
	InitOnna(1);
	InitBlackhole(1);
}

//=============================================================================
// 画面遷移
//=============================================================================
void SetStage(int stage)
{
	if (stage < 0 || stage >= STAGE_MAX) return;

	g_nStage = stage;
}

//=============================================================================
// 現在のゲーム画面を取得
//=============================================================================
int GetStage(void)
{
	return g_nStage;
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void DrawFPS(void)
{
	PrintDebugProc("FPS:%d\n", g_nCountFPS);
}
#endif

//=====================================================================================================
// ウインドウの表示位置を画面中央に
//=====================================================================================================
bool SetWindowCenter(HWND hWnd)
{
	// 変数宣言
	RECT WindowRegion;		//	ウィンドウ領域
	RECT DesktopRegion;	//	デスクトップ領域
	int WindowPositionX;	//	ウィンドウ位置 X
	int WindowPositionY;	//	ウィンドウ位置 Y
	int WindowSizeX;		//	ウィンドウサイズ X
	int WindowSizeY;		//	ウィンドウサイズ Y

							// 各サイズの取得
	GetMonitorRect(&DesktopRegion);				//	デスクトップのサイズを取得
	GetWindowRect(hWnd, &WindowRegion);	//	ウィンドウのサイズを取得

										// 各座標の割り出し
	WindowSizeX = (WindowRegion.right - WindowRegion.left);														//	ウインドウの横幅の割り出し
	WindowSizeY = (WindowRegion.bottom - WindowRegion.top);														//	ウインドウの縦幅の割り出し
	WindowPositionX = (((DesktopRegion.right - DesktopRegion.left) - WindowSizeX) / 2 + DesktopRegion.left);	//	横方向の中央座標軸の割り出し
	WindowPositionY = (((DesktopRegion.bottom - DesktopRegion.top) - WindowSizeY) / 2 + DesktopRegion.top);	//	縦方向の中央座標軸の割り出し

																											// ウィンドウを画面中央に移動
	return SetWindowPos	//	SetWindowPos関数：子ウィンドウ、ポップアップウィンドウ、またはトップレベルウィンドウのサイズ、位置、および Z オーダーを変更する
						//						これらのウィンドウは、その画面上での表示に従って順序が決められる、
						//						最前面にあるウィンドウは最も高いランクを与えられ、Zオーダーの先頭に置かれる
						(
							hWnd,											//	ウィンドウハンドル
							NULL,											//	配置順序のハンドル：先行するウィンドウのハンドルを指定
							WindowPositionX,								//	ウィンドウ左上隅の"X"座標を指定：横方向の位置 X
							WindowPositionY,								//	ウィンドウ左上隅の"Y"座標を指定：縦方向の位置 Y
							WindowSizeX,									//	ウィンドウの横幅を指定 X
							WindowSizeY,									//	ウィンドウの縦幅を指定 Y
							(SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER)	//	ウィンドウ位置のオプション：ウィンドウのサイズや、位置の変更に関するフラグを指定
						);

}
int CreateRandom(int Minimum, int Maximum)
{
	return Minimum + (int)(rand()*(Maximum - Minimum + 1.0f) / (1.0f + RAND_MAX));
}

float CreateRandomFloat(float Minimum, float Maximum)
{
	return Minimum + (int)(rand()*(Maximum - Minimum + 1.0f) / (1.0f + RAND_MAX));
}
