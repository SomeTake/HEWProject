/*******************************************************************************
* �^�C�g��:		�ǃw�b�_�[
* �v���O������:	meshwall.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/1/28
*******************************************************************************/
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "Main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MESH_WALL		(10)								// �ǂ̑���
#define	TEXTURE_FILENAME	"data/TEXTURE/graffiti_texture_01_by_aimi_stock_d1nms6n-fullview.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_WALL		(5.0f)							// �ړ����x
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)				// ��]���x
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
#endif
