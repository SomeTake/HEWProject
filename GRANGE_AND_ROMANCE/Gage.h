/*******************************************************************************
* タイトル:	ゲージヘッダー
* プログラム名:	Gage.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _GAGE_H_
#define _GAGE_H_

// マクロ定義
#define	NUM_GAGE			(2)									// ポリゴン数
#define TEXTURE_GAGE		("data/TEXTURE/PLAYERHP.png")		// サンプル用画像
#define GAGE_SIZE_X			(200)								// テクスチャサイズ
#define GAGE_SIZE_Y			(30)								// 同上
#define GAGE_MAX			(1)									// gageの数

#define	NUM_GAGE2			(2)									// ポリゴン数
#define TEXTURE_GAGE2		("data/TEXTURE/aka.png")			// サンプル用画像
#define GAGE2_SIZE_X		(200)								// テクスチャサイズ
#define GAGE2_SIZE_Y		(40)								// 同上
#define GAGE2_MAX			(1)									// gage2の数

#define	NUM_GAGE3			(2)									// ポリゴン数
#define TEXTURE_GAGE3		("data/TEXTURE/ENEMY HP.png")		// サンプル用画像
#define GAGE3_SIZE_X		(200)								// テクスチャサイズ
#define GAGE3_SIZE_Y		(30)								// 同上
#define GAGE3_MAX			(1)									// gage3の数

#define	NUM_GAGE4			(2)									// ポリゴン数
#define TEXTURE_GAGE4		("data/TEXTURE/blue.png")			// サンプル用画像
#define GAGE4_SIZE_X		(200)								// テクスチャサイズ
#define GAGE4_SIZE_Y		(40)								// 同上
#define GAGE4_MAX			(1)									// gage4の数

#define	NUM_GAGE5			(2)									// ポリゴン数
#define TEXTURE_GAGE5		("data/TEXTURE/aka2.png")			// サンプル用画像
#define GAGE5_SIZE_X		(200)								// テクスチャサイズ
#define GAGE5_SIZE_Y		(40)								// 同上
#define GAGE5_MAX			(1)									// gage5の数

#define	NUM_GAGE6			(2)									// ポリゴン数
#define TEXTURE_GAGE6		("data/TEXTURE/blue2.png")			// サンプル用画像
#define GAGE6_SIZE_X		(200)								// テクスチャサイズ
#define GAGE6_SIZE_Y		(40)								// 同上
#define GAGE6_MAX			(1)									// gage6の数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// gage構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture;			// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_GAGE];			// 頂点情報格納ワーク
	float			Radius;						// gageの半径
	float			BaseAngle;					// gageの角度
} GAGE;

typedef struct	// gage2構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture2;			// テクスチャ情報
	VERTEX_2D		vertexWk2[NUM_GAGE2];		// 頂点情報格納ワーク
	float			Radius;						// gage2の半径
	float			BaseAngle;					// gage2の角度
} GAGE2;

typedef struct	// gage3構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture3;			// テクスチャ情報
	VERTEX_2D		vertexWk3[NUM_GAGE3];			// 頂点情報格納ワーク
	float			Radius;						// gageの半径
	float			BaseAngle;					// gageの角度
} GAGE3;

typedef struct	// gage4構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture4;			// テクスチャ情報
	VERTEX_2D		vertexWk4[NUM_GAGE4];		// 頂点情報格納ワーク
	float			Radius;						// gage2の半径
	float			BaseAngle;					// gage2の角度
} GAGE4;

typedef struct	// gage5構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture5;			// テクスチャ情報
	VERTEX_2D		vertexWk5[NUM_GAGE5];		// 頂点情報格納ワーク
	float			Radius;						// gage5の半径
	float			BaseAngle;					// gage5の角度
} GAGE5;

typedef struct	// gage6構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture6;			// テクスチャ情報
	VERTEX_2D		vertexWk6[NUM_GAGE6];		// 頂点情報格納ワーク
	float			Radius;						// gage6の半径
	float			BaseAngle;					// gag6の角度
} GAGE6;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGage(int type);
HRESULT MakeVertexGage(void);
void UninitGage(void);
void UpdateGage(void);
void DrawGage(void);
void SetVertexGage(void);
void SetTextuerGage(void);
GAGE *GetGage(int no);
GAGE2 *GetGage2(int no);
GAGE3 *GetGage3(int no);
GAGE4 *GetGage4(int no);
GAGE5 *GetGage5(int no);
GAGE6 *GetGage6(int no);

#endif
