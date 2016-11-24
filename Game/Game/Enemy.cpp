#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy()
{
	m_position = {1.0f,0.0f,0.0f};
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.6f,0.6f,0.6f };

}


Enemy::~Enemy()
{
}

void Enemy::Start()
{

	m_skinModelData.LoadModelData("Assets/modelData/Player.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&g_defaultLight);//�f�t�H���g���C�g��ݒ�B
	m_characterController.Init(0.5f, 1.0f, m_position);

}

void Enemy::Update()
{
	Move();
	m_skinModel.Update(m_position, m_rotation,m_scale);//���[���h�s��̍X�V�B
}

void Enemy::Move()
{
	CVector3 move = m_characterController.GetMoveSpeed();
	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	m_characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s�B
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();
}

void Enemy::Render(CRenderContext& renderContext)
{

	m_skinModel.Draw(renderContext,g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}

void Enemy::Delete()
{
	DeleteGO(this);
}
