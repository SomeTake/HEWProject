/*******************************************************************************
* �^�C�g��:		�Q�[���v���O����
* �v���O������:	Game.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#include "Game.h"
#include "Player.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
<<<<<<< HEAD
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAME *game = GameWk;										// �Q�[���̃|�C���^�[��������

																// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAME,				// �t�@�C���̖��O
		&pD3DTextureGame);			// �ǂݍ��ރ������[

	game->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	game->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	game->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	game->col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���W�f�[�^��������
	game->Alpha = 1.0f;
	game->use = false;
	game->Texture = pD3DTextureGame;								// �e�N�X�`�����
	D3DXVECTOR2 temp = D3DXVECTOR2(GAME_SIZE_X, GAME_SIZE_Y);
	game->Radius = D3DXVec2Length(&temp);							// �Q�[���̔��a��������
	game->BaseAngle = atan2f(GAME_SIZE_Y, GAME_SIZE_X);				// �Q�[���̊p�x��������
	game->PatternAnim = 0;											// �A�j���p�^�[���ԍ���������
	game->CountAnim = 0;											// �A�j���J�E���g��������
																	// ���_���̍쐬
	MakeVertexGame();
=======
	InitPlayer(0);
>>>>>>> master

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���f���̏I������
	UninitPlayer();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	UpdatePlayer();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
<<<<<<< HEAD
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAME *game = GameWk;						// �Q�[���̃|�C���^�[��������

	if (game->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);


		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, game->Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_GAME, game->VertexWkGame, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGame(void)
{
	GAME *game= GameWk;				// �Q�[���̃|�C���^�[��������

	// ���_���W�̐ݒ�
	game->VertexWkGame[0].vtx = D3DXVECTOR3(game->pos.x, game->pos.y, 0.0f);
	game->VertexWkGame[1].vtx = D3DXVECTOR3(game->pos.x + GAME_SIZE_X, game->pos.y, 0.0f);
	game->VertexWkGame[2].vtx = D3DXVECTOR3(game->pos.x, game->pos.y + GAME_SIZE_Y, 0.0f);
	game->VertexWkGame[3].vtx = D3DXVECTOR3(game->pos.x + GAME_SIZE_X, game->pos.y + GAME_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	game->VertexWkGame[0].rhw =
	game->VertexWkGame[1].rhw =
	game->VertexWkGame[2].rhw =
	game->VertexWkGame[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	game->VertexWkGame[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	game->VertexWkGame[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	game->VertexWkGame[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	game->VertexWkGame[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_GAME, 0.0f);
	game->VertexWkGame[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GAME);
	game->VertexWkGame[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_GAME, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_GAME);

	return S_OK;
=======
	// �v���C���[�`��
	DrawPlayer();
>>>>>>> master
}

