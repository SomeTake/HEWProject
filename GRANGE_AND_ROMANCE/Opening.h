/*******************************************************************************
* �^�C�g��:		�I�[�v�j���O�w�b�_�[
* �v���O������:	Opening.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _OPENING_H_
#define _OPENING_H_

#include "Main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_OPENING		("data/TEXTURE/enter2.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	OPENING_SIZE_X		(800)									// �I�[�v�j���O�̕�
#define	OPENING_SIZE_Y		(600)									// �I�[�v�j���O�̍���
#define OPENING_MAX			(1)										// �I�[�v�j���O�̍ő吔
#define	NUM_OPENING			(2)										// �|���S����
#define TEXTURE_PATTERN_DIVIDE_X_OPENING	(1)						// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_OPENING	(1)						// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_OPENING			(TEXTURE_PATTERN_DIVIDE_X_OPENING*TEXTURE_PATTERN_DIVIDE_Y_OPENING)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_OPENING				(4)						// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �I�[�v�j���O�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// �|���S���̊g���
	D3DXVECTOR3		col;						// �|���S���̐F�ʗ�
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			Alpha;
	float			Radius;						// �I�[�v�j���O�̔��a
	float			BaseAngle;					// �I�[�v�j���O�̊p�x
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D			VertexWkOpening[NUM_VERTEX];			// ���_���i�[���[�N

} OPENING;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitOpening(void);
HRESULT MakeVertexOpening(void);
void UninitOpening(void);
void UpdateOpening(void);
void DrawOpening(void);
OPENING *GetOpening(int no);

#endif
