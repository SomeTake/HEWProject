/*******************************************************************************
* �^�C�g��:		�I�[�v�j���O�v���O����
* �v���O������:	Opening.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#include "Opening.h"
#include "Input.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureOpening = NULL;				// �e�N�X�`���ւ̃|�C���^
OPENING					OpeningWk[OPENING_MAX];					// �I�[�v�j���O�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitOpening(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	OPENING *opening = OpeningWk;								// �I�[�v�j���O�̃|�C���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
		TEXTURE_OPENING,				// �t�@�C���̖��O
		&pD3DTextureOpening);			// �ǂݍ��ރ������[

	opening->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	opening->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	opening->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	opening->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	opening->Alpha = 1.0f;
	opening->use = true;
	opening->Texture = pD3DTextureOpening;								// �e�N�X�`�����
	D3DXVECTOR2 temp = D3DXVECTOR2(OPENING_SIZE_X, OPENING_SIZE_Y);
	opening->Radius = D3DXVec2Length(&temp);							// �I�[�v�j���O�̔��a��������
	opening->BaseAngle = atan2f(OPENING_SIZE_Y, OPENING_SIZE_X);		// �I�[�v�j���O�̊p�x��������
	opening->PatternAnim = 0;											// �A�j���p�^�[���ԍ���������
	opening->CountAnim = 0;												// �A�j���J�E���g��������
																		// ���_���̍쐬
	MakeVertexOpening();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitOpening(void)
{
	if (pD3DTextureOpening != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureOpening->Release();
		pD3DTextureOpening = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateOpening(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_TITLE);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawOpening(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	OPENING *opening = OpeningWk;				// �I�[�v�j���O�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, opening->Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_OPENING, opening->VertexWkOpening, sizeof(VERTEX_2D));


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexOpening(void)
{
	OPENING *opening = OpeningWk;				// �I�[�v�j���O�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	opening->VertexWkOpening[0].vtx = D3DXVECTOR3(opening->pos.x, opening->pos.y, 0.0f);
	opening->VertexWkOpening[1].vtx = D3DXVECTOR3(opening->pos.x + OPENING_SIZE_X, opening->pos.y, 0.0f);
	opening->VertexWkOpening[2].vtx = D3DXVECTOR3(opening->pos.x, opening->pos.y + OPENING_SIZE_Y, 0.0f);
	opening->VertexWkOpening[3].vtx = D3DXVECTOR3(opening->pos.x + OPENING_SIZE_X, opening->pos.y + OPENING_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	opening->VertexWkOpening[0].rhw =
	opening->VertexWkOpening[1].rhw =
	opening->VertexWkOpening[2].rhw =
	opening->VertexWkOpening[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	opening->VertexWkOpening[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	opening->VertexWkOpening[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	opening->VertexWkOpening[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	opening->VertexWkOpening[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_OPENING, 0.0f);
	opening->VertexWkOpening[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_OPENING);
	opening->VertexWkOpening[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_OPENING, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_OPENING);

	return S_OK;
}

//=============================================================================
// �I�[�v�j���O�擾�֐�
//=============================================================================
OPENING *GetOpening(int no)
{
	return(&OpeningWk[no]);
}
