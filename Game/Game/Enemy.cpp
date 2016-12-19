#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy()
{
	m_position = { 0.0f,100.0f,10.0f };
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.6f,0.6f,0.6f };
	m_radius = 0.5f;
	m_dead = false;

	m_filename = NULL;
	m_name = NULL;
	m_hp = 0;
	m_maxhp = 0;
	m_movelim = 0.0f;

	m_characterController.Init(m_radius, 1.0f, m_position);

	m_random.Init((unsigned int)time(NULL));
}


Enemy::~Enemy()
{
}

void Enemy::Start(char* filename, char* enemyname, int maxhp, float radius)
{
	m_filename = filename;
	m_name = enemyname;
	m_hp = maxhp;
	m_maxhp = maxhp;
	m_radius = radius;

	m_characterController.SetRadius(m_radius);

	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", m_filename);

	SkinModelDataResources().Load(m_skinModelData, filePath, NULL);
	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。
}

void Enemy::Update()
{
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}

	Move();
	m_skinModel.Update(m_position, m_rotation,m_scale);//ワールド行列の更新。
}

void Enemy::Move()
{
	if (m_random.GetRandDouble() > 0.5f)
	{
		return;
	}

	CVector3 move = m_characterController.GetMoveSpeed();

	CVector3 moveXZ;
	moveXZ.x = (m_random.GetRandDouble() - 0.5f) * 2.5f;
	moveXZ.y = 0.0f;
	moveXZ.z = (m_random.GetRandDouble() - 0.5f) * 2.5f;

	if (m_movelim < moveXZ.Length())
	{
		float len = moveXZ.Length();
		moveXZ.Div(len);
		moveXZ.Scale(m_movelim);
	}
	move.x = moveXZ.x;
	move.z = moveXZ.z;

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
	m_dead = true;
}
