//=============================================================================
//
// �J�������� [camera.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)											// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(10.0f)											// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(150.0f)										// �J�����̏����ʒu(Z���W)

#define AT_X_CAM		(0.0f)											// �J�����̒����_(X���W)
#define AT_Y_CAM		(50.0f)											// �J�����̒����_(Y���W)
#define AT_Z_CAM		(0.0f)											// �J�����̒����_(Z���W)

#define	VALUE_MOVE_CAMERA	(2.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

#define	INTERVAL_CAMERA_R	(12.5f)										// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_P	(0.35f)										// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)										// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(100.0f)									// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)										// �ǐՎ��̒����_�̍���

#define CAMERA_SPD		(0.05f)											// �Â��J�����ʒu�ƐV�����J�����ʒu�ɍ�������ꍇ�ɃJ�����ʒu���X�V����X�s�[�h
																		// �Q�̃J�����ʒu�̃x�N�g����CAMERA_SPD�����t���[���V�����J�����ʒu���X�V�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

typedef struct {
	D3DXVECTOR3			pos;		// �J�����̎��_
	D3DXVECTOR3			at;			// �J�����̒����_
	D3DXVECTOR3			up;			// �J�����̏�����x�N�g��
	D3DXVECTOR3			rot;		// �J�����̉�]
	float				distance;	// �J�����̒����_�Ǝ��_�Ƃ̋���
	D3DXMATRIX			mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
}CAMERA;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UpdateCamera(void);
CAMERA *GetCamera(int cno);
void SetCamera(int no);
D3DXVECTOR3 GetCenterPos(void);		// P��E�̊Ԃ̈ʒu���擾����
float GetPEdistance(void);			// P��E�̋������擾����

#endif
