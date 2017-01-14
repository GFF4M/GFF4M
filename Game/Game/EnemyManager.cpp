#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"

const Enemy::EneDat			m_enemiesdat[ENEMY_DAT] =
{
	{ STAGE_T_1,			"dog",		"ìG",	100,{ 3.0f,55.0f,0.0f },{ 0.0f,5.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
	{ STAGE_T_BATTLE,		"kinokomove",	"ìG",	100,{ 3.0f,70.0f,3.0f },{ 0.0f,2.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
	{ STAGE_1_1,			"dog",		"ìG",	100,{ 3.0f,55.0f,0.0f },{ 0.0f,5.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
	{ STAGE_1_BATTLE,		"Player",	"ìG",	100,{ 3.0f,70.0f,3.0f },{ 0.0f,2.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
};

EnemyManager::EnemyManager()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		m_enemy[i] = nullptr;

	}

	m_random.Init((unsigned int)time(NULL));

	m_enemy_num = 0;

	m_isBattle = false;
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Start()
{
}

void EnemyManager::Update()
{
	if (m_isBattle)
	{
		bool changeflg = true;
		for (int i = 0;i < ENEMY_NUM;i++)
		{
			if (m_enemy[i] != nullptr)
			{
				if (m_enemy[i]->GetHP() > 0)
				{
					changeflg = false;
				}
			}
		}

		if (changeflg)
		{
			Scenes scene = NOSCENES;
			switch (g_scene->GetScenes())
			{
			case STAGE_T_BATTLE:
				scene = STAGE_1_1;
				break;
			case STAGE_1_BATTLE:
				scene = STAGE_2_1;
				break;
			case STAGE_2_BATTLE:
				scene = STAGE_3_1;
				break;
			case STAGE_3_BATTLE:
				scene = STAGE_4_1;
				break;
			case STAGE_4_BATTLE:
				scene = STAGE_5_1;
				break;
			case STAGE_5_BATTLE:
				scene = GAME_CLEAR;
				break;
			default:
				break;
			}

			g_scene->Change(scene);
		}
	}
}

void EnemyManager::Change(Scenes scene)
{
	Delete();

	//êÌì¨ópÉtÉBÅ[ÉãÉhÇ÷ÇÃëJà⁄Ç©í≤Ç◊ÇÈ
	switch (scene)
	{
	case STAGE_T_BATTLE:
	case STAGE_1_BATTLE:
	case STAGE_2_BATTLE:
	case STAGE_3_BATTLE:
	case STAGE_4_BATTLE:
	case STAGE_5_BATTLE:
		m_isBattle = true;
		break;
	default:
		m_isBattle = false;
		break;
	}

	int enemy_num = 0;
	for each(Enemy::EneDat dat in m_enemiesdat)
	{
		if (dat.s_scene == scene)
		{
			enemy_num++;
		}
	}

	if (enemy_num == 0)
	{
		return;
	}

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		m_enemy[i] = NewGO<Enemy>(0);

		int rand = m_random.GetRandInt() % enemy_num;

		int datcnt = 0;
		for each(Enemy::EneDat dat in m_enemiesdat)
		{
			if (dat.s_scene == scene)
			{
				if (datcnt == rand)
				{
					CVector3 pos;
					pos = dat.s_pos;

					m_enemy[i]->Start(dat, m_isBattle);
					break;
				}
				datcnt++;
			}
		}
	}
	m_enemy_num = ENEMY_NUM;
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
	m_enemy_num = 0;
}

Enemy* EnemyManager::GetNearestEnemy(CVector3 pos, int no)
{
	int ret = 0;
	float dis = 10000.0f;

	int num[ENEMY_NUM];
	float dat[ENEMY_NUM];

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		num[i] = 0;

		CVector3 sub = pos;
		sub.Subtract(m_enemy[i]->GetPos());
		dat[i] = sub.Length();
	}

	for (int i = 1;i < ENEMY_NUM;i++)
	{
		for (int j = 0;j < i;j++)
		{
			if (dat[i] > dat[j])
			{
				num[i]++;
			}
			else
			{
				num[j]++;
			}
		}
	}

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		if (num[i] == no)
		{
			return m_enemy[i];
		}
	}

	return nullptr;
}

//dog.X
//doragon.X
//golem.X
//kaeruwalk.X
//woodAttack.X
//kinokomove.X
//kinokoAttack.X