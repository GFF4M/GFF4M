#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
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

void EnemyManager::Change(Scenes scene)
{
	Delete();

	bool isBattle;

	//戦闘用フィールドへの遷移か調べる
	switch (scene)
	{
	case STAGE_1_BATTLE:
	case STAGE_2_BATTLE:
	case STAGE_3_BATTLE:
	case STAGE_4_BATTLE:
	case STAGE_5_BATTLE:
	case STAGE_1_BOSS_BATTLE:
	case STAGE_2_BOSS_BATTLE:
	case STAGE_3_BOSS_BATTLE:
	case STAGE_4_BOSS_BATTLE:
	case STAGE_5_BOSS_BATTLE:
		isBattle = true;
		break;
	default:
		isBattle = false;
		break;
	}

	cnt = 0;
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
		m_enemy[i] = NewGO<Enemy>(0);

		int rand = m_random.GetRandInt() % cnt + 1;

		int datcnt = 0;
		for each(Enemies dat in m_enemiesdat)
		{
			if (dat.s_scene == scene)
			{
				datcnt++;
				if (datcnt == cnt)
				{
					m_enemy[i]->Start(dat.s_filename, dat.s_name, dat.s_hp, dat.s_movelim, dat.s_look_pos, isBattle);
					break;
				}
			}
		}
	}
}

void EnemyManager::Delete()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		if (m_enemy[i] != nullptr)
		{
			m_enemy[i]->Delete();
			m_enemy[i] = nullptr;
		}
	}
}