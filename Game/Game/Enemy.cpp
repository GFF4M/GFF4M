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
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。
	m_characterController.Init(0.5f, 1.0f, m_position);

}

void Enemy::Update()
{
	Move();
	m_skinModel.Update(m_position, m_rotation,m_scale);//ワールド行列の更新。
}

void Enemy::Move()
{
	CVector3 move = m_characterController.GetMoveSpeed();
	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
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
