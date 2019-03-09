/*******************************************************************************
* �^�C�g��:	�Q�[�W�w�b�_�[
* �v���O������:	Gauge.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _GAUGE_H_
#define _GAUGE_H_

// �}�N����`
#define	NUM_GAUGE			(2)									// �|���S����
#define TEXTURE_GAUGE		("data/TEXTURE/PLAYERHP.png")		// �T���v���p�摜
#define GAUGE_SIZE_X			(200)								// �e�N�X�`���T�C�Y
#define GAUGE_SIZE_Y			(30)								// ����
#define GAUGE_MAX			(1)									// gauge�̐�

#define	NUM_GAUGE2			(2)									// �|���S����
#define TEXTURE_GAUGE2		("data/TEXTURE/aka.png")			// �T���v���p�摜
#define GAUGE2_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAUGE2_SIZE_Y		(40)								// ����
#define GAUGE2_MAX			(1)									// gauge2�̐�

#define	NUM_GAUGE3			(2)									// �|���S����
#define TEXTURE_GAUGE3		("data/TEXTURE/ENEMY HP.png")		// �T���v���p�摜
#define GAUGE3_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAUGE3_SIZE_Y		(30)								// ����
#define GAUGE3_MAX			(1)									// gauge3�̐�

#define	NUM_GAUGE4			(2)									// �|���S����
#define TEXTURE_GAUGE4		("data/TEXTURE/blue.png")			// �T���v���p�摜
#define GAUGE4_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAUGE4_SIZE_Y		(40)								// ����
#define GAUGE4_MAX			(1)									// gauge4�̐�

#define	NUM_GAUGE5			(2)									// �|���S����
#define TEXTURE_GAUGE5		("data/TEXTURE/aka2.png")			// �T���v���p�摜
#define GAUGE5_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAUGE5_SIZE_Y		(40)								// ����
#define GAUGE5_MAX			(1)									// gauge5�̐�

#define	NUM_GAUGE6			(2)									// �|���S����
#define TEXTURE_GAUGE6		("data/TEXTURE/blue2.png")			// �T���v���p�摜
#define GAUGE6_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAUGE6_SIZE_Y		(40)								// ����
#define GAUGE6_MAX			(1)									// gauge6�̐�

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// gauge�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture;			// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];			// ���_���i�[���[�N
	float			Radius;						// gauge�̔��a
	float			BaseAngle;					// gauge�̊p�x
} GAUGE;

typedef struct	// gauge2�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture2;			// �e�N�X�`�����
	VERTEX_2D		vertexWk2[NUM_VERTEX];		// ���_���i�[���[�N
	float			Radius;						// gauge2�̔��a
	float			BaseAngle;					// gauge2�̊p�x
} GAUGE2;

typedef struct	// gauge3�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture3;			// �e�N�X�`�����
	VERTEX_2D		vertexWk3[NUM_VERTEX];			// ���_���i�[���[�N
	float			Radius;						// gauge�̔��a
	float			BaseAngle;					// gauge�̊p�x
} GAUGE3;

typedef struct	// gauge4�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture4;			// �e�N�X�`�����
	VERTEX_2D		vertexWk4[NUM_VERTEX];		// ���_���i�[���[�N
	float			Radius;						// gauge2�̔��a
	float			BaseAngle;					// gauge2�̊p�x
} GAUGE4;

typedef struct	// gauge5�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture5;			// �e�N�X�`�����
	VERTEX_2D		vertexWk5[NUM_VERTEX];		// ���_���i�[���[�N
	float			Radius;						// gauge5�̔��a
	float			BaseAngle;					// gauge5�̊p�x
} GAUGE5;

typedef struct	// gauge6�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture6;			// �e�N�X�`�����
	VERTEX_2D		vertexWk6[NUM_VERTEX];		// ���_���i�[���[�N
	float			Radius;						// gauge6�̔��a
	float			BaseAngle;					// gag6�̊p�x
} GAUGE6;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGauge(int type);
HRESULT MakeVertexGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void SetVertexGauge(void);
void SetTextuerGauge(void);
GAUGE *GetGauge(int no);
GAUGE2 *GetGauge2(int no);
GAUGE3 *GetGauge3(int no);
GAUGE4 *GetGauge4(int no);
GAUGE5 *GetGauge5(int no);
GAUGE6 *GetGauge6(int no);

#endif
