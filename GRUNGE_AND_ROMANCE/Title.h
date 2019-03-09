/*******************************************************************************
* �^�C�g��:		�^�C�g���w�b�_�[
* �v���O������:	Title.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _TITLE_H_
#define _TITLE_H_

#include "Main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		("data/TEXTURE/enter2.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_SIZE_X		(800)									// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)									// �^�C�g���̍���
#define TITLE_MAX			(1)										// �^�C�g���̍ő吔
#define	NUM_TITLE			(2)										// �|���S����
#define TEXTURE_PATTERN_DIVIDE_X_TITLE	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_TITLE	(1)							// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_TITLE			(TEXTURE_PATTERN_DIVIDE_X_TITLE*TEXTURE_PATTERN_DIVIDE_Y_TITLE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_TITLE			(4)							// �A�j���[�V�����̐؂�ւ��J�E���g

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �^�C�g���\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// �|���S���̊g���
	D3DXVECTOR3		col;						// �|���S���̐F�ʗ�
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	float			Alpha;
	float			Radius;						// title�̔��a
	float			BaseAngle;					// title�̊p�x
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D			VertexWkTitle[NUM_VERTEX];			// ���_���i�[���[�N

} TITLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
HRESULT MakeVertexTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLE *GetTitle(int no);
#endif
