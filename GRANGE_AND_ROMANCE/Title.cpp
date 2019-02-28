/*******************************************************************************
* �^�C�g��:		�^�C�g���v���O����
* �v���O������:	Title.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#include "Title.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureTitle = NULL;				// �e�N�X�`���ւ̃|�C���^
TITLE					TitleWk[TITLE_MAX];						// �^�C�g���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = TitleWk;								// �^�C�g���̃|�C���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE,				// �t�@�C���̖��O
		&pD3DTextureTitle);			// �ǂݍ��ރ������[

	title->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	title->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	title->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	title->Alpha = 1.0f;
	title->use = true;
	title->Texture = pD3DTextureTitle;								// �e�N�X�`�����
	D3DXVECTOR2 temp = D3DXVECTOR2(TITLE_SIZE_X, TITLE_SIZE_Y);
	title->Radius = D3DXVec2Length(&temp);							// �^�C�g���̔��a��������
	title->BaseAngle = atan2f(TITLE_SIZE_Y, TITLE_SIZE_X);			// �^�C�g���̊p�x��������
	title->PatternAnim = 0;											// �A�j���p�^�[���ԍ���������
	title->CountAnim = 0;											// �A�j���J�E���g��������
																	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if (pD3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureTitle->Release();
		pD3DTextureTitle = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = TitleWk;				// �^�C�g���̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, title->Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TITLE, title->VertexWkTitle, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	TITLE *title = TitleWk;				// �^�C�g���̃|�C���^�[��������

										// ���_���W�̐ݒ�
	title->VertexWkTitle[0].vtx = D3DXVECTOR3(title->pos.x, title->pos.y, 0.0f);
	title->VertexWkTitle[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_SIZE_X, title->pos.y, 0.0f);
	title->VertexWkTitle[2].vtx = D3DXVECTOR3(title->pos.x, title->pos.y + TITLE_SIZE_Y, 0.0f);
	title->VertexWkTitle[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_SIZE_X, title->pos.y + TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	title->VertexWkTitle[0].rhw =
	title->VertexWkTitle[1].rhw =
	title->VertexWkTitle[2].rhw =
	title->VertexWkTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	title->VertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->VertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	title->VertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->VertexWkTitle[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE, 0.0f);
	title->VertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE);
	title->VertexWkTitle[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE);

	return S_OK;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
TITLE *GetTitle(int no)
{
	return(&TitleWk[no]);
}
