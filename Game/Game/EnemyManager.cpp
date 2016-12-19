#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
	m_random.Init((unsigned int)time(NULL));
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Start(Scenes scene)
{
	int cnt = 0;
	for each(Enemies dat in m_enemiesdat)
	{
		if (dat.s_scene == scene)
		{
			cnt++;
		}
	}

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		int rand = m_random.GetRandInt() % cnt;
		m_enemy[i] = NewGO<Enemy>(0);
		m_enemy[i]->Start(m_enemiesdat[rand].s_filename, m_enemiesdat[rand].s_name, m_enemiesdat[rand].s_hp, m_enemiesdat[rand].s_movelim);
	}
}

void EnemyManager::Update()
{

}

void EnemyManager::Render(CRenderContext& renderContext)
{

}

void EnemyManager::Delete()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		m_enemy[i]->Delete();
	}
}
