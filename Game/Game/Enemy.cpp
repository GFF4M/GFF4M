#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy()
{
	m_position = {1.0f,0.0f,0.0f};
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.8f,0.8f,0.8f };

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
	m_skinModel.Update(m_position, m_rotation,m_scale);//ワールド行列の更新。
}

void Enemy::Move()
{
}

void Enemy::Render(CRenderContext& renderContext)
{

	m_skinModel.Draw(renderContext,g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}

void Enemy::Delete()
{
	DeleteGO(this);
}
