#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy()
{
	m_position = { 1.0f,0.0f,0.0f };
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.6f,0.6f,0.6f };
	m_movelimit = 0.0f;
	m_characterController.Init(0.5f, 1.0f, m_position);
}


Enemy::~Enemy()
{
}

void Enemy::Start()
{
	SkinModelDataResources().Load(m_skinModelData,"Assets/modelData/Player.X",NULL);
	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//�f�t�H���g���C�g��ݒ�B
}

void Enemy::Update()
{
	Move();
	m_skinModel.Update(m_position, m_rotation,m_scale);//���[���h�s��̍X�V�B
}

void Enemy::Move()
{

	CVector3 move = m_characterController.GetMoveSpeed();
	CRandom random;

	random.Init((unsigned)time(NULL));

	CVector3 moveXZ;
	moveXZ.x = (random.GetRandDouble() - 0.5f) * 2.5f;
	moveXZ.y = 0.0f;
	moveXZ.z = (random.GetRandDouble() - 0.5f) * 2.5f;

	if (m_movelimit < moveXZ.Length())
	{
		float len = moveXZ.Length();
		moveXZ.Div(len);
		moveXZ.Scale(m_movelimit);
	}
	move.x = moveXZ.x;
	move.z = moveXZ.z;

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
