#include "stdafx.h"
#include "Map.h"
#include "MapDat.h"

Map::Map()
{
	m_dead = false;
	m_mapchip[0] = nullptr;
}

Map::~Map()
{
}

void Map::Start()
{
}

void Map::Change(Scenes scene)
{
	Delete();

	int num = 0;

	switch (scene)
	{
	case NOSCENES:
		break;
	case START:
		break;
	case SAVE_DATA:
		break;
	case STAGE_HOUSE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_1_1:
		for each(SMapInfo dat in Stage_1_2)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_1_2:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_1_BOSS:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_1_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_1_BOSS_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_2_1:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_2_2:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_2_BOSS:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_2_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_2_BOSS_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_3_1:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_3_2:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_3_BOSS:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_3_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_3_BOSS_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_4_1:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_4_2:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_4_BOSS:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_4_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_4_BOSS_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_5_1:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_5_2:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_5_BOSS:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_5_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	case STAGE_5_BOSS_BATTLE:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	default:
		for each(SMapInfo dat in Stage_1_1)
		{
			m_mapchip[num] = NewGO<MapChip>(0);
			m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
			num++;
		}
		break;
	}
	m_mapchip[num] = nullptr;
}

void Map::Update()
{
}

void Map::Delete()
{
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; m_mapchip[i] != nullptr; i++)
	{
		m_mapchip[i]->Delete();
		m_mapchip[i] = nullptr;
	}
}