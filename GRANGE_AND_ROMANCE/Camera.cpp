//=============================================================================
//
// �J�������� [camera.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Camera.h"
#include "Input.h"
#include "Player.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#define VIEW_DIST			(4)		// �Œ���̃L�����N�^�[�ƃJ�����̋���
#define VIEW_DIST_RATE		(0.3f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA cameraWk[MAX_SEPARATE];

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	cameraWk->at = D3DXVECTOR3(AT_X_CAM, AT_Y_CAM, AT_Z_CAM);
	cameraWk->pos = cameraWk->at + D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);

	cameraWk->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	cameraWk->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����_����J�����̈ʒu�܂ł̋����v��
	float vx, vz;
	vx = cameraWk->pos.x - cameraWk->at.x;
	vz = cameraWk->pos.z - cameraWk->at.z;
	cameraWk->distance = sqrtf(vx * vx + vz * vz);

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(int no)
{
	CAMERA *cameraWk = GetCamera(no);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&cameraWk->mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&cameraWk->mtxView,
		&cameraWk->pos,		// �J�����̎��_
		&cameraWk->at,		// �J�����̒����_
		&cameraWk->up);		// �J�����̏�����x�N�g��

							// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &cameraWk->mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&cameraWk->mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&cameraWk->mtxProjection,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

							// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &cameraWk->mtxProjection);

}

//=============================================================================
//�J�����̏����擾����
//=============================================================================
CAMERA *GetCamera(int cno)
{
	return &cameraWk[cno];
}
