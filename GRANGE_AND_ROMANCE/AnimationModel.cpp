//=============================================================================
//
// �A�j���[�V�������� [AnimationModel.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================

#include "AnimationModel.h"

#if 0

AnimationModel::AnimationModel(void)
{
}


AnimationModel::~AnimationModel(void)
{
}

void AnimationModel::InitController(D3DXAnimation* mesh)
{
	m_pAnimMesh = mesh;
	m_pAnimController = mesh->CloneAnimCtrl();

	// �������̓��I�m��
	AnimationSet = (HLANIMATION_DESC*)malloc(sizeof(HLANIMATION_DESC) * GetAnimationNum());
	for (int i = 0; i < GetAnimationNum(); i++)
	{
		AnimationSet[i].pAnimSet = GetAnimationSet(i);
		AnimationSet[i].SetName = AnimationSet[i].pAnimSet->GetName();
		AnimationSet[i].PlaySpeed = (float)AnimationSet[i].pAnimSet->GetPeriod() / 4800;
	}
	return;
}

void AnimationModel::Render()
{
	m_pAnimMesh->Render(&m_Matrix);
}

bool AnimationModel::PlayAnimation(LPCTSTR name, bool isLoop)
{
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimationSet);
	return true;
}

void AnimationModel::Update(void)
{
	m_pAnimController->AdvanceTime(m_fSpeed, NULL);
}

void AnimationModel::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

float AnimationModel::GetSpeed(void)
{
	return AnimationSet[CurAnimID].PlaySpeed;
}

// ���[�v���Ԃ�ݒ�
bool AnimationModel::SetLoopTime(UINT animID, FLOAT time)
{
	// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
	if (animID > (UINT)GetAnimationNum())
	{
		return false;
	}

	// �g���b�N�X�s�[�h���ߒl���Z�o
	float DefTime = (float)AnimationSet[animID].pAnimSet->GetPeriod();
	AnimationSet[animID].fLoopTime = time;
	AnimationSet[animID].fTrackSpeed = DefTime / time;

	return true;
}

// ����J�n�ɂ����鎞�Ԃ�ݒ�
bool AnimationModel::SetShiftTime(UINT animID, FLOAT interval)
{
	// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
	if (animID > (UINT)GetAnimationNum())
	{
		return false;
	}

	// �V�t�g���Ԃ�o�^
	AnimationSet[animID].fShiftTime = interval;

	return true;
}

// �A�j���[�V������؂�ւ�
bool AnimationModel::ChangeAnimation(UINT animID)
{
	// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
	if (animID > (UINT)GetAnimationNum())
	{
		return false;
	}

	// �قȂ�A�j���[�V�����ł��邩���`�F�b�N
	if (CurAnimID == animID)
	{
		return false;
	}


	// ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
	D3DXTRACK_DESC TD;   // �g���b�N�̔\��
	m_pAnimController->GetTrackDesc(0, &TD);

	// ���̃A�j���[�V�������g���b�N1�Ɉڍs��
	// �g���b�N�̐ݒ�l���ڍs
	m_pAnimController->SetTrackAnimationSet(1, AnimationSet[CurAnimID].pAnimSet);
	m_pAnimController->SetTrackDesc(1, &TD);

	// �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
	m_pAnimController->SetTrackAnimationSet(0, AnimationSet[animID].pAnimSet);

	// �g���b�N0�̃X�s�[�h�̐ݒ�
	m_pAnimController->SetTrackSpeed(0, 1.0f);

	// �g���b�N0�̈ʒu�͍ŏ�����ɐݒ�
	m_pAnimController->SetTrackPosition(0, 0.0f);

	// �g���b�N�̍���������
	m_pAnimController->SetTrackEnable(0, true);
	m_pAnimController->SetTrackEnable(1, true);

	// �E�F�C�g���Ԃ�������
	AnimationSet[animID].fCurWeightTime = 0.0f;

	m_pAnimController->ResetTime();

	// ���݂̃A�j���[�V�����ԍ���؂�ւ�
	PreAnimID = CurAnimID;
	CurAnimID = animID;

	return true;
}

// �A�j���[�V�������X�V
bool AnimationModel::AdvanceTime(FLOAT time)
{
	// ���������ۂ��𔻒�
	AnimationSet[CurAnimID].fCurWeightTime += time;
	if (AnimationSet[CurAnimID].fCurWeightTime <= AnimationSet[CurAnimID].fShiftTime)
	{
		// �������B�E�F�C�g���Z�o
		FLOAT Weight = AnimationSet[CurAnimID].fCurWeightTime / AnimationSet[CurAnimID].fShiftTime;
		// �E�F�C�g��o�^
		m_pAnimController->SetTrackWeight(0, Weight);       // ���݂̃A�j���[�V����
		m_pAnimController->SetTrackWeight(1, 1 - Weight);   // �O�̃A�j���[�V����
	}
	else
	{
		// �����I�����B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l��
		m_pAnimController->SetTrackWeight(0, 1.0f);       // ���݂̃A�j���[�V����
		m_pAnimController->SetTrackEnable(1, false);      // �O�̃A�j���[�V�����𖳌��ɂ���
	}

	// ���Ԃ��X�V
	m_pAnimController->AdvanceTime(time, NULL);

	return true;
}

void AnimationModel::SetMatrix(const LPD3DXMATRIX matrix)
{
	m_Matrix = *matrix;
}

int AnimationModel::GetAnimationNum() const
{
	return m_pAnimController->GetMaxNumAnimationSets();
}

LPD3DXANIMATIONSET AnimationModel::GetAnimationSet(int index) const
{
	if (index >= 0 && index < GetAnimationNum())
	{
		LPD3DXANIMATIONSET pAnimSet = NULL;
		m_pAnimController->GetAnimationSet(index, &pAnimSet);
		return pAnimSet;
	}

	return NULL;
}

#endif
