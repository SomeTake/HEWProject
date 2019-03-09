/*******************************************************************************
* �^�C�g��:		�G���f�B���O�v���O����
* �v���O������:	Ending.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#include "Ending.h"
#include "Input.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureEnding = NULL;				// �e�N�X�`���ւ̃|�C���^
ENDING					EndingWk[ENDING_MAX];					// �G���f�B���O�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnding(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENDING *ending = EndingWk;								// �G���f�B���O�̃|�C���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENDING,					// �t�@�C���̖��O
		&pD3DTextureEnding);			// �ǂݍ��ރ������[

	ending->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	ending->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	ending->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	ending->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	ending->Alpha = 1.0f;
	ending->use = true;
	ending->Texture = pD3DTextureEnding;								// �e�N�X�`�����
	D3DXVECTOR2 temp = D3DXVECTOR2(ENDING_SIZE_X, ENDING_SIZE_Y);
	ending->Radius = D3DXVec2Length(&temp);							// �G���f�B���O�̔��a��������
	ending->BaseAngle = atan2f(ENDING_SIZE_Y, ENDING_SIZE_X);		// �G���f�B���O�̊p�x��������
	ending->PatternAnim = 0;										// �A�j���p�^�[���ԍ���������
	ending->CountAnim = 0;											// �A�j���J�E���g��������
																	// ���_���̍쐬
	MakeVertexEnding();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitEnding(void)
{
	if (pD3DTextureEnding != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureEnding->Release();
		pD3DTextureEnding = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnding(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_OPENING);
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnding(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENDING *ending = EndingWk;				// �G���f�B���O�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, ending->Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENDING, ending->VertexWkEnding, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnding(void)
{
	ENDING *ending = EndingWk;				// �G���f�B���O�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	ending->VertexWkEnding[0].vtx = D3DXVECTOR3(ending->pos.x, ending->pos.y, 0.0f);
	ending->VertexWkEnding[1].vtx = D3DXVECTOR3(ending->pos.x + ENDING_SIZE_X, ending->pos.y, 0.0f);
	ending->VertexWkEnding[2].vtx = D3DXVECTOR3(ending->pos.x, ending->pos.y + ENDING_SIZE_Y, 0.0f);
	ending->VertexWkEnding[3].vtx = D3DXVECTOR3(ending->pos.x + ENDING_SIZE_X, ending->pos.y + ENDING_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	ending->VertexWkEnding[0].rhw =
	ending->VertexWkEnding[1].rhw =
	ending->VertexWkEnding[2].rhw =
	ending->VertexWkEnding[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	ending->VertexWkEnding[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ending->VertexWkEnding[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	ending->VertexWkEnding[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ending->VertexWkEnding[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENDING, 0.0f);
	ending->VertexWkEnding[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENDING);
	ending->VertexWkEnding[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENDING, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENDING);

	return S_OK;
}

//=============================================================================
// �G���f�B���O�擾�֐�
//=============================================================================
ENDING *GetEnding(int no)
{
	return(&EndingWk[no]);
}
