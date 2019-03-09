/*******************************************************************************
* �^�C�g��:		�G���f�B���O�w�b�_�[
* �v���O������:	Ending.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _ENDING_H_
#define _ENDING_H_

#include "Main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ENDING		("data/TEXTURE/enter2.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ENDING_SIZE_X			(800)								// �G���f�B���O�̕�
#define	ENDING_SIZE_Y			(600)								// �G���f�B���O�̍���
#define ENDING_MAX			(1)										// �G���f�B���O�̍ő吔
#define	NUM_ENDING			(2)										// �|���S����
#define TEXTURE_PATTERN_DIVIDE_X_ENDING	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENDING	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENDING			(TEXTURE_PATTERN_DIVIDE_X_ENDING*TEXTURE_PATTERN_DIVIDE_Y_ENDING)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENDING			(4)							// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �G���f�B���O�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// �|���S���̊g���
	D3DXVECTOR3		col;						// �|���S���̐F�ʗ�
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			Alpha;
	float			Radius;						// �G���f�B���O�̔��a
	float			BaseAngle;					// �G���f�B���O�̊p�x
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D			VertexWkEnding[NUM_VERTEX];			// ���_���i�[���[�N

} ENDING;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnding(void);
HRESULT MakeVertexEnding(void);
void UninitEnding(void);
void UpdateEnding(void);
void DrawEnding(void);
ENDING *GetEnding(int no);

#endif
