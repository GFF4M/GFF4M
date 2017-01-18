#include "stdafx.h"
#include "StatusAilment.h"
#include "Scene.h"

StatusAilment::StatusAilment()
{
	for (int i = 0; i < SA_DATNUM; i++)
	{
		m_timer[i] = 0.0f;
	}
	m_random.Init((unsigned int)time(NULL));
}

void StatusAilment::Execute(AttackStat stat, MagicNo magic)
{
	switch (stat)
	{
	case AS_ME:
		if (magic == FIRE)
		{
			m_timer[SA_FROZEN] = 0.0f;
		}
		if (magic == AQUA)
		{
			m_timer[SA_IGNITION] = 0.0f;
		}
		break;
	case AS_OTHER:
		for each(StatusAilmentData dat in m_SA_Dat)
		{
			if (dat.s_magicNo == magic)
			{
				if (m_timer[dat.s_engName] <= 0.0f)
				{
					int random = m_random.GetRandInt() % 100;

					if (random <= dat.s_per)
					{
						m_timer[dat.s_engName] = dat.s_time;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void StatusAilment::Update()
{
	for (int i = 0; i < SA_DATNUM; i++)
	{
		if (m_timer[i] > 0.0f)
		{
			m_timer[i] -= DELTA_TIME;
		}
	}
}

StatusAilment::~StatusAilment()
{
}
