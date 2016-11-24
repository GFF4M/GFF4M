#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
}


Player::~Player()
{
}


void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Player.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&g_defaultLight);	//�f�t�H���g���C�g��ݒ�B
											
	m_characterController.Init(0.5f, 1.0f, m_position);//�L�����N�^�R���g���[���̏������B
}

void Player::Update()
{
	Move();
	//���[���h�s��̍X�V�B
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}

void Player::Move()
{
	//�L�����N�^�[�̈ړ����x������B
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//��]������
	CVector3 moveXZ = move;						//�����x�N�g��
	moveXZ.y = 0.0f;

	//AxisZ��moveXZ�̂Ȃ��p�����߂�
	if (moveXZ.Length() > 0.0f)
	{
		m_angle = moveXZ.Dot(CVector3::AxisZ);
		m_angle /= (moveXZ.Length() + 0.00001f);
		m_angle = acosf(m_angle);
		m_angle = m_angle * 180.0 / CMath::PI;

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}
	
		//�J�����ɂ��␳
		m_angle -= g_gameCamera->GetAngle();

		move.x = moveXZ.Length() * sin(CMath::DegToRad(m_angle));
		move.z = moveXZ.Length() * cos(CMath::DegToRad(m_angle));
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
	DeleteGO(this);
}
