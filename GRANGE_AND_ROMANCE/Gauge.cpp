/*******************************************************************************
* �^�C�g��:		�Q�[�W�v���O����
* �v���O������:	Gauge.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#include "Main.h"
#include "Input.h"
#include "Gauge.h"
#include "Player.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge2 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge3 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge4 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge5 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureGauge6 = NULL;		// �e�N�X�`���ւ̃|�C���^

GAUGE						gaugeWk[GAUGE_MAX];				// gauge�\����
GAUGE2						gaugeWk2[GAUGE2_MAX];			// gauge2�\����
GAUGE3						gaugeWk3[GAUGE3_MAX];			// gauge3�\����
GAUGE4						gaugeWk4[GAUGE4_MAX];			// gauge4�\����
GAUGE5						gaugeWk5[GAUGE5_MAX];			// gauge5�\����
GAUGE6						gaugeWk6[GAUGE6_MAX];			// gauge6�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAUGE *gauge = gaugeWk;							// gauge�̃|�C���^�[��������
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2�̃|�C���^�[��������
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4�̃|�C���^�[��������
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5�̃|�C���^�[��������
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE,						// �t�@�C���̖��O
			&g_pD3DTextureGauge);				// �ǂݍ��ރ������[
	}
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE2,						// �t�@�C���̖��O
			&g_pD3DTextureGauge2);				// �ǂݍ��ރ������[
	}
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE3,						// �t�@�C���̖��O
			&g_pD3DTextureGauge3);				// �ǂݍ��ރ������[
	}
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE4,						// �t�@�C���̖��O
			&g_pD3DTextureGauge4);				// �ǂݍ��ރ������[
	}
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE5,						// �t�@�C���̖��O
			&g_pD3DTextureGauge5);				// �ǂݍ��ރ������[
	}
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAUGE6,						// �t�@�C���̖��O
			&g_pD3DTextureGauge6);				// �ǂݍ��ރ������[
	}

	// gauge�̏���������
	for (int i = 0; i < GAUGE_MAX; i++, gauge++)
	{
		gauge->use = true;												// �g�p
		gauge->pos = D3DXVECTOR3(-400.0f, 30.0f, 0.0f);					// ���W�f�[�^��������
		gauge->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ��]�f�[�^��������

		gauge->g_pD3DTexture = g_pD3DTextureGauge;						// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}
	// gauge2�̏���������
	for (int i = 0; i < GAUGE2_MAX; i++, gauge2++)
	{
		gauge2->use = true;												// �g�p
		gauge2->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// ���W�f�[�^��������
		gauge2->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		gauge2->g_pD3DTexture2 = g_pD3DTextureGauge2;					// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}
	// gauge3�̏���������
	for (int i = 0; i < GAUGE3_MAX; i++, gauge3++)
	{
		gauge3->use = true;												// �g�p
		gauge3->pos = D3DXVECTOR3(1000.0f, 30.0f, 0.0f);				// ���W�f�[�^��������
		gauge3->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������

		gauge3->g_pD3DTexture3 = g_pD3DTextureGauge3;					// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}
	// gauge4�̏���������
	for (int i = 0; i < GAUGE4_MAX; i++, gauge4++)
	{
		gauge4->use = true;												// �g�p
		gauge4->pos = D3DXVECTOR3(1000.0f, 70.0f, 0.0f);				// ���W�f�[�^��������
		gauge4->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		gauge4->g_pD3DTexture4 = g_pD3DTextureGauge4;					// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}
	// gauge5�̏���������
	for (int i = 0; i < GAUGE5_MAX; i++, gauge5++)
	{
		gauge5->use = true;												// �g�p
		gauge5->pos = D3DXVECTOR3(-400.0f, 70.0f, 0.0f);				// ���W�f�[�^��������
		gauge5->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		gauge5->g_pD3DTexture5 = g_pD3DTextureGauge5;					// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}
	// gauge6�̏���������
	for (int i = 0; i < GAUGE6_MAX; i++, gauge6++)
	{
		gauge6->use = true;												// �g�p
		gauge6->pos = D3DXVECTOR3(1000.0f, 70.0f, 0.0f);				// ���W�f�[�^��������
		gauge6->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]�f�[�^��������
		gauge6->g_pD3DTexture6 = g_pD3DTextureGauge6;					// �e�N�X�`�����
		MakeVertexGauge();												// ���_���̍쐬
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitGauge(void)
{
	if (g_pD3DTextureGauge != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge->Release();
		g_pD3DTextureGauge = NULL;
	}
	if (g_pD3DTextureGauge2 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge2->Release();
		g_pD3DTextureGauge2 = NULL;
	}
	if (g_pD3DTextureGauge3 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge3->Release();
		g_pD3DTextureGauge3 = NULL;
	}
	if (g_pD3DTextureGauge4 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge4->Release();
		g_pD3DTextureGauge4 = NULL;
	}
	if (g_pD3DTextureGauge5 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge5->Release();
		g_pD3DTextureGauge5 = NULL;
	}
	if (g_pD3DTextureGauge6 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGauge6->Release();
		g_pD3DTextureGauge6 = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateGauge(void)
{
	GAUGE *gauge = gaugeWk;							// gauge�̃|�C���^�[��������
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2�̃|�C���^�[��������
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4�̃|�C���^�[��������
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5�̃|�C���^�[��������
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6�̃|�C���^�[��������

		gauge2->pos.x +=4.0f;
		gauge->pos.x += 4.0f;
		gauge5->pos.x += 4.0f;

		if (gauge2->pos.x >= 0.0f)
		{
			gauge2->pos.x = 0;
			gauge->pos.x = 0;
			gauge5->pos.x = 0;

		}
		gauge4->pos.x -= 4.0f;
		gauge3->pos.x -= 4.0f;
		gauge6->pos.x -= 4.0f;

		if (gauge4->pos.x <= 600.0f)
		{
			gauge4->pos.x = 600;
			gauge3->pos.x = 600;
			gauge6->pos.x = 600;

		}

		SetVertexGauge();
		SetTextuerGauge();


}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAUGE *gauge = gaugeWk;							// gauge�̃|�C���^�[��������
	GAUGE2 *gauge2 = gaugeWk2;						// gauge2�̃|�C���^�[��������
	GAUGE3 *gauge3 = gaugeWk3;						// gauge3�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;						// gauge4�̃|�C���^�[��������
	GAUGE5 *gauge5 = gaugeWk5;						// gauge5�̃|�C���^�[��������
	GAUGE6 *gauge6 = gaugeWk6;						// gauge6�̃|�C���^�[��������

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge5);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE5, gauge5->vertexWk5, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE, gauge->vertexWk, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge2);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE2, gauge2->vertexWk2, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge6);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE6, gauge6->vertexWk6, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge3);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE3, gauge3->vertexWk3, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGauge4);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAUGE4, gauge4->vertexWk4, sizeof(VERTEX_2D));


}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGauge(void)
{
	GAUGE *gauge = gaugeWk;					// gauge�̃|�C���^�[��������
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2�̃|�C���^�[��������
	GAUGE3 *gauge3 = gaugeWk3;				// gauge3�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4�̃|�C���^�[��������
	GAUGE5 *gauge5 = gaugeWk5;				// gauge5�̃|�C���^�[��������
	GAUGE6 *gauge6 = gaugeWk6;				// gauge6�̃|�C���^�[��������


		// ���_���W�̐ݒ�
		gauge->vertexWk[0].vtx = D3DXVECTOR3(gauge->pos.x, gauge->pos.y, 0.0f);
		gauge->vertexWk[1].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X, gauge->pos.y, 0.0f);
		gauge->vertexWk[2].vtx = D3DXVECTOR3(gauge->pos.x, gauge->pos.y + GAUGE_SIZE_Y, 0.0f);
		gauge->vertexWk[3].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X, gauge->pos.y + GAUGE_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge->vertexWk[0].rhw =
			gauge->vertexWk[1].rhw =
			gauge->vertexWk[2].rhw =
			gauge->vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//���_���W�̐ݒ�
		gauge2->vertexWk2[0].vtx = D3DXVECTOR3(gauge2->pos.x, gauge2->pos.y, 0.0f);
		gauge2->vertexWk2[1].vtx = D3DXVECTOR3(gauge2->pos.x + GAUGE2_SIZE_X, gauge2->pos.y, 0.0f);
		gauge2->vertexWk2[2].vtx = D3DXVECTOR3(gauge2->pos.x, gauge2->pos.y + GAUGE2_SIZE_Y, 0.0f);
		gauge2->vertexWk2[3].vtx = D3DXVECTOR3(gauge2->pos.x + GAUGE2_SIZE_X, gauge2->pos.y + GAUGE2_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge2->vertexWk2[0].rhw =
			gauge2->vertexWk2[1].rhw =
			gauge2->vertexWk2[2].rhw =
			gauge2->vertexWk2[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge2->vertexWk2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge2->vertexWk2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge2->vertexWk2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge2->vertexWk2[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//���_���W�̐ݒ�
		gauge5->vertexWk5[0].vtx = D3DXVECTOR3(gauge5->pos.x, gauge5->pos.y, 0.0f);
		gauge5->vertexWk5[1].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X, gauge5->pos.y, 0.0f);
		gauge5->vertexWk5[2].vtx = D3DXVECTOR3(gauge5->pos.x, gauge5->pos.y + GAUGE5_SIZE_Y, 0.0f);
		gauge5->vertexWk5[3].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X, gauge5->pos.y + GAUGE5_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge5->vertexWk5[0].rhw =
			gauge5->vertexWk5[1].rhw =
			gauge5->vertexWk5[2].rhw =
			gauge5->vertexWk5[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge5->vertexWk5[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge5->vertexWk5[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge5->vertexWk5[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge5->vertexWk5[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge5->vertexWk5[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge5->vertexWk5[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		// ���_���W�̐ݒ�
		gauge3->vertexWk3[0].vtx = D3DXVECTOR3(gauge3->pos.x, gauge3->pos.y, 0.0f);
		gauge3->vertexWk3[1].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X, gauge3->pos.y, 0.0f);
		gauge3->vertexWk3[2].vtx = D3DXVECTOR3(gauge3->pos.x, gauge3->pos.y + GAUGE3_SIZE_Y, 0.0f);
		gauge3->vertexWk3[3].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X, gauge3->pos.y + GAUGE3_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge3->vertexWk3[0].rhw =
			gauge3->vertexWk3[1].rhw =
			gauge3->vertexWk3[2].rhw =
			gauge3->vertexWk3[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge3->vertexWk3[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge3->vertexWk3[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge3->vertexWk3[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge3->vertexWk3[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge3->vertexWk3[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge3->vertexWk3[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//���_���W�̐ݒ�
		gauge4->vertexWk4[0].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[1].vtx = D3DXVECTOR3(gauge4->pos.x + GAUGE4_SIZE_X, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[2].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);
		gauge4->vertexWk4[3].vtx = D3DXVECTOR3(gauge4->pos.x + GAUGE4_SIZE_X, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge4->vertexWk4[0].rhw =
			gauge4->vertexWk4[1].rhw =
			gauge4->vertexWk4[2].rhw =
			gauge4->vertexWk4[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge4->vertexWk4[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge4->vertexWk4[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge4->vertexWk4[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge4->vertexWk4[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		//���_���W�̐ݒ�
		gauge6->vertexWk6[0].vtx = D3DXVECTOR3(gauge6->pos.x, gauge6->pos.y, 0.0f);
		gauge6->vertexWk6[1].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X, gauge6->pos.y, 0.0f);
		gauge6->vertexWk6[2].vtx = D3DXVECTOR3(gauge6->pos.x, gauge6->pos.y + GAUGE6_SIZE_Y, 0.0f);
		gauge6->vertexWk6[3].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X, gauge6->pos.y + GAUGE_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		gauge6->vertexWk6[0].rhw =
			gauge6->vertexWk6[1].rhw =
			gauge6->vertexWk6[2].rhw =
			gauge6->vertexWk6[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gauge6->vertexWk6[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		gauge6->vertexWk6[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		gauge6->vertexWk6[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge6->vertexWk6[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		gauge6->vertexWk6[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge6->vertexWk6[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexGauge(void)
{
	GAUGE *gauge = gaugeWk;					// gauge�̃|�C���^�[��������
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2�̃|�C���^�[��������
	GAUGE3 *gauge3 = gaugeWk3;				// gauge3�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4�̃|�C���^�[��������
	GAUGE5 *gauge5 = gaugeWk5;				// gauge5�̃|�C���^�[��������
	GAUGE6 *gauge6 = gaugeWk6;				// gauge6�̃|�C���^�[��������

	CHARA *chara = GetPlayer(0);

		// ���_���W�̐ݒ�
		gauge2->vertexWk2[0].vtx = D3DXVECTOR3(gauge2->pos.x-0.5f, gauge2->pos.y - 0.5f, 0.0f);
		gauge2->vertexWk2[1].vtx = D3DXVECTOR3(gauge2->pos.x + chara->HP - 0.5f, gauge2->pos.y - 0.5f, 0.0f);
		gauge2->vertexWk2[2].vtx = D3DXVECTOR3(gauge2->pos.x - 0.5f, gauge2->pos.y + GAUGE2_SIZE_Y - 0.5f, 0.0f);
		gauge2->vertexWk2[3].vtx = D3DXVECTOR3(gauge2->pos.x + chara->HP - 0.5f, gauge2->pos.y + GAUGE2_SIZE_Y - 0.5f, 0.0f);

		gauge->vertexWk[0].vtx = D3DXVECTOR3(gauge->pos.x-0.5f, gauge->pos.y-0.5f, 0.0f);
		gauge->vertexWk[1].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X-0.5f, gauge->pos.y-0.5f, 0.0f);
		gauge->vertexWk[2].vtx = D3DXVECTOR3(gauge->pos.x-0.5f, gauge->pos.y + GAUGE_SIZE_Y-0.5f, 0.0f);
		gauge->vertexWk[3].vtx = D3DXVECTOR3(gauge->pos.x + GAUGE_SIZE_X-0.5f, gauge->pos.y + GAUGE_SIZE_Y-0.5f, 0.0f);

		gauge5->vertexWk5[0].vtx = D3DXVECTOR3(gauge5->pos.x - 0.5f, gauge5->pos.y - 0.5f, 0.0f);
		gauge5->vertexWk5[1].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X - 0.5f, gauge5->pos.y - 0.5f, 0.0f);
		gauge5->vertexWk5[2].vtx = D3DXVECTOR3(gauge5->pos.x - 0.5f, gauge5->pos.y + GAUGE5_SIZE_Y - 0.5f, 0.0f);
		gauge5->vertexWk5[3].vtx = D3DXVECTOR3(gauge5->pos.x + GAUGE5_SIZE_X - 0.5f, gauge5->pos.y + GAUGE5_SIZE_Y - 0.5f, 0.0f);


		// ���_���W�̐ݒ�
		gauge4->vertexWk4[0].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[1].vtx = D3DXVECTOR3(gauge4->pos.x + chara->HP, gauge4->pos.y, 0.0f);
		gauge4->vertexWk4[2].vtx = D3DXVECTOR3(gauge4->pos.x, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);
		gauge4->vertexWk4[3].vtx = D3DXVECTOR3(gauge4->pos.x + chara->HP, gauge4->pos.y + GAUGE4_SIZE_Y, 0.0f);

		gauge3->vertexWk3[0].vtx = D3DXVECTOR3(gauge3->pos.x - 0.5f, gauge3->pos.y - 0.5f, 0.0f);
		gauge3->vertexWk3[1].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X - 0.5f, gauge3->pos.y - 0.5f, 0.0f);
		gauge3->vertexWk3[2].vtx = D3DXVECTOR3(gauge3->pos.x - 0.5f, gauge3->pos.y + GAUGE3_SIZE_Y - 0.5f, 0.0f);
		gauge3->vertexWk3[3].vtx = D3DXVECTOR3(gauge3->pos.x + GAUGE3_SIZE_X - 0.5f, gauge3->pos.y + GAUGE3_SIZE_Y - 0.5f, 0.0f);

		gauge6->vertexWk6[0].vtx = D3DXVECTOR3(gauge6->pos.x - 0.5f, gauge6->pos.y - 0.5f, 0.0f);
		gauge6->vertexWk6[1].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X - 0.5f, gauge6->pos.y - 0.5f, 0.0f);
		gauge6->vertexWk6[2].vtx = D3DXVECTOR3(gauge6->pos.x - 0.5f, gauge6->pos.y + GAUGE6_SIZE_Y - 0.5f, 0.0f);
		gauge6->vertexWk6[3].vtx = D3DXVECTOR3(gauge6->pos.x + GAUGE6_SIZE_X - 0.5f, gauge6->pos.y + GAUGE6_SIZE_Y - 0.5f, 0.0f);


}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextuerGauge(void)
{
	GAUGE2 *gauge2 = gaugeWk2;				// gauge2�̃|�C���^�[��������
	GAUGE4 *gauge4 = gaugeWk4;				// gauge4�̃|�C���^�[��������

	CHARA *chara = GetPlayer(0);

		// �e�N�X�`�����W�̐ݒ�
		gauge2->vertexWk2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge2->vertexWk2[1].tex = D3DXVECTOR2((float)chara->HP / chara->HPzan, 0.0f);
		gauge2->vertexWk2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge2->vertexWk2[3].tex = D3DXVECTOR2((float)chara->HP / chara->HPzan, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		gauge4->vertexWk4[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		gauge4->vertexWk4[1].tex = D3DXVECTOR2((float)chara->HP / chara->HPzan, 0.0f);
		gauge4->vertexWk4[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		gauge4->vertexWk4[3].tex = D3DXVECTOR2((float)chara->HP / chara->HPzan, 1.0f);

}
//=============================================================================
// gauge�擾�֐�
//=============================================================================
GAUGE *GetGauge(int no)
{
	return(&gaugeWk[no]);
}
GAUGE2 *GetGauge2(int no)
{
	return(&gaugeWk2[no]);
}
GAUGE3 *GetGauge3(int no)
{
	return(&gaugeWk3[no]);
}
GAUGE4 *GetGauge4(int no)
{
	return(&gaugeWk4[no]);
}
GAUGE5 *GetGauge5(int no)
{
	return(&gaugeWk5[no]);
}
GAUGE6 *GetGauge6(int no)
{
	return(&gaugeWk6[no]);
}

