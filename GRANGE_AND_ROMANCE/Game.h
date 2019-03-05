/*******************************************************************************
* �^�C�g��:		�Q�[���w�b�_�[
* �v���O������:	Game.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME		("data/TEXTURE/enter2.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	GAME_SIZE_X			(800)									// �Q�[���̕�
#define	GAME_SIZE_Y			(600)									// �Q�[���̍���
#define GAME_MAX			(1)										// �Q�[���̍ő吔
#define	NUM_GAME			(2)										// �|���S����
#define TEXTURE_PATTERN_DIVIDE_X_GAME	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_GAME	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_GAME			(TEXTURE_PATTERN_DIVIDE_X_GAME*TEXTURE_PATTERN_DIVIDE_Y_GAME)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_GAME				(4)							// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �Q�[���\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// �|���S���̊g���
	D3DXVECTOR3		col;						// �|���S���̐F�ʗ�
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			Alpha;
	float			Radius;						// �Q�[���̔��a
	float			BaseAngle;					// �Q�[���̊p�x
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D			VertexWkGame[NUM_VERTEX];			// ���_���i�[���[�N

} GAME;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
HRESULT MakeVertexGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAME *GetGame(int no);

#endif
