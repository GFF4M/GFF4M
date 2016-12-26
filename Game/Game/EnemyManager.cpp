#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
	m_isBattle = false;
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		m_enemy[i] = nullptr;
	}

	m_random.Init((unsigned int)time(NULL));
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Start()
{
}

void EnemyManager::Update()
{

}

void EnemyManager::Change(Scenes scene, bool isBattle)
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		if (m_enemy[i] != nullptr)
		{
			m_enemy[i]->Delete();
			m_enemy[i] = nullptr;
		}
	}
	m_isBattle = isBattle;

	int cnt = 0;
	for each(Enemies dat in m_enemiesdat)
	{
		if (dat.s_scene == scene)
		{
			cnt++;
		}
	}

	if (cnt == 0)
	{
		return;
	}

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		int rand = m_random.GetRandInt() % cnt;
		m_enemy[i] = NewGO<Enemy>(0);
		m_enemy[i]->Start(m_enemiesdat[rand].s_filename, m_enemiesdat[rand].s_name, m_enemiesdat[rand].s_hp, m_enemiesdat[rand].s_movelim, m_enemiesdat[rand].s_look_pos);
	}
}