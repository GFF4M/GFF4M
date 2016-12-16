#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = /*CVector3::Zero*/{ 0.0f,15.0f,0.0f };
	m_rotation = CQuaternion::Identity;
	m_animationStat = AnimationStand;
	m_characterController.Init(0.5f, 1.0f, m_position);//�L�����N�^�R���g���[���̏������B
}

Player::~Player()
{
}

void Player::Start()
{

	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/kanoDash2.X", &m_animation);

	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//�f�t�H���g���C�g��ݒ�B

	m_animation.SetAnimationLoopFlag(AnimationAttack,false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
}

void Player::Update()
{

	if (Pad(0).IsTrigger(enButtonA))
	{
		m_animation.PlayAnimation(AnimationAttack,0.3f);
	}

	Move();

	m_animation.Update(2.0 / 60.0f);

	//���[���h�s��̍X�V�B
	m_skinModel.Update(m_position,m_rotation, CVector3::One);

}

void Player::Move()
{
	//�L�����N�^�[�̈ړ����x������B
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 10.0f;
	move.z = -Pad(0).GetLStickYF() * 10.0f;

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//�����x�N�g��
	moveXZ.y = 0.0f;

	float    LenXZ = moveXZ.Length();

	if (LenXZ > 0.0f)
	{
		if (m_animationStat != AnimationWalk)
		{
			m_animationStat = AnimationWalk;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
		}

		//AxisZ��moveXZ�̂Ȃ��p�����߂�
		m_angle = moveXZ.AngleBetween(CVector3::AxisZ);

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}
	
		//�J�����ɂ��␳
		m_angle -= g_gameCamera->GetAngle();

		//��]���������Ɉړ�
		move.x = LenXZ * sin(CMath::DegToRad(m_angle));
		move.z = LenXZ * cos(CMath::DegToRad(m_angle));
	}
	else
	{
		if (m_animationStat != AnimationStand)
		{
			m_animationStat = AnimationStand;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
		}
	}

	//�p�x�̐��K��
	if (m_angle < -180.0f)
	{
		m_angle += 360.0f;
	}
	else if (180.0f < m_angle)
	{
		m_angle -= 360.0f;
	}

	//��i�W�����v
	if (KeyInput().GetPad(0).IsPress(enButtonX) && m_characterController.IsOnGround())
	{
		m_characterController.Jump();
		move.y = 8.0f;
	}

	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	m_characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s�B
	m_characterController.Execute();
	//���s���ʂ��󂯎��B
	m_position = m_characterController.GetPosition();

	m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
}

void Player::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Player::Delete()
{
	m_characterController.RemoveRigidBoby();
	DeleteGO(this);
}
