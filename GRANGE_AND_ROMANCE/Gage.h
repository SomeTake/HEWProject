/*******************************************************************************
* �^�C�g��:	�Q�[�W�w�b�_�[
* �v���O������:	Gage.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _GAGE_H_
#define _GAGE_H_

// �}�N����`
#define	NUM_GAGE			(2)									// �|���S����
#define TEXTURE_GAGE		("data/TEXTURE/PLAYERHP.png")		// �T���v���p�摜
#define GAGE_SIZE_X			(200)								// �e�N�X�`���T�C�Y
#define GAGE_SIZE_Y			(30)								// ����
#define GAGE_MAX			(1)									// gage�̐�

#define	NUM_GAGE2			(2)									// �|���S����
#define TEXTURE_GAGE2		("data/TEXTURE/aka.png")			// �T���v���p�摜
#define GAGE2_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAGE2_SIZE_Y		(40)								// ����
#define GAGE2_MAX			(1)									// gage2�̐�

#define	NUM_GAGE3			(2)									// �|���S����
#define TEXTURE_GAGE3		("data/TEXTURE/ENEMY HP.png")		// �T���v���p�摜
#define GAGE3_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAGE3_SIZE_Y		(30)								// ����
#define GAGE3_MAX			(1)									// gage3�̐�

#define	NUM_GAGE4			(2)									// �|���S����
#define TEXTURE_GAGE4		("data/TEXTURE/blue.png")			// �T���v���p�摜
#define GAGE4_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAGE4_SIZE_Y		(40)								// ����
#define GAGE4_MAX			(1)									// gage4�̐�

#define	NUM_GAGE5			(2)									// �|���S����
#define TEXTURE_GAGE5		("data/TEXTURE/aka2.png")			// �T���v���p�摜
#define GAGE5_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAGE5_SIZE_Y		(40)								// ����
#define GAGE5_MAX			(1)									// gage5�̐�

#define	NUM_GAGE6			(2)									// �|���S����
#define TEXTURE_GAGE6		("data/TEXTURE/blue2.png")			// �T���v���p�摜
#define GAGE6_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define GAGE6_SIZE_Y		(40)								// ����
#define GAGE6_MAX			(1)									// gage6�̐�

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// gage�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture;			// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_GAGE];			// ���_���i�[���[�N
	float			Radius;						// gage�̔��a
	float			BaseAngle;					// gage�̊p�x
} GAGE;

typedef struct	// gage2�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture2;			// �e�N�X�`�����
	VERTEX_2D		vertexWk2[NUM_GAGE2];		// ���_���i�[���[�N
	float			Radius;						// gage2�̔��a
	float			BaseAngle;					// gage2�̊p�x
} GAGE2;

typedef struct	// gage3�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture3;			// �e�N�X�`�����
	VERTEX_2D		vertexWk3[NUM_GAGE3];			// ���_���i�[���[�N
	float			Radius;						// gage�̔��a
	float			BaseAngle;					// gage�̊p�x
} GAGE3;

typedef struct	// gage4�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture4;			// �e�N�X�`�����
	VERTEX_2D		vertexWk4[NUM_GAGE4];		// ���_���i�[���[�N
	float			Radius;						// gage2�̔��a
	float			BaseAngle;					// gage2�̊p�x
} GAGE4;

typedef struct	// gage5�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture5;			// �e�N�X�`�����
	VERTEX_2D		vertexWk5[NUM_GAGE5];		// ���_���i�[���[�N
	float			Radius;						// gage5�̔��a
	float			BaseAngle;					// gage5�̊p�x
} GAGE5;

typedef struct	// gage6�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	LPDIRECT3DTEXTURE9	g_pD3DTexture6;			// �e�N�X�`�����
	VERTEX_2D		vertexWk6[NUM_GAGE6];		// ���_���i�[���[�N
	float			Radius;						// gage6�̔��a
	float			BaseAngle;					// gag6�̊p�x
} GAGE6;

//*****************************************************************************
// �v���g�^�C�v�錾
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
