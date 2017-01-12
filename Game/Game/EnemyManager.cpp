#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemy.h"

const Enemy::EneDat			m_enemiesdat[ENEMY_DAT] =
{
	{ STAGE_T_1,			"dog",		"“G",	100,{ 3.0f,55.0f,0.0f },{ 0.0f,1.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
	{ STAGE_T_BATTLE,		"Player",	"“G",	100,{ 3.0f,70.0f,3.0f },{ 0.0f,1.0f,0.0f }	,{ 1.0f,1.0f,1.0f } },
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

}

void EnemyManager::Change(Scenes scene)
{
	Delete();

	//í“¬—pƒtƒB[ƒ‹ƒh‚Ö‚Ì‘JˆÚ‚©’²‚×‚é
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