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

	std::vector<SMapInfo> map_dat;
	switch (scene)
	{
	case NOSCENES:
		break;
	case START:
		break;
	case STAGE_T_1:
		map_dat = Stage_T_1;
		break;
	case STAGE_T_BATTLE:
		map_dat = Stage_T_B;
		break;
	case STAGE_1_1:
		map_dat = Stage_1_1;
		break;
	case STAGE_1_BATTLE:
		map_dat = Stage_1_B;
		break;
	case STAGE_2_1:
		map_dat = Stage_2_1;
		break;
	case STAGE_2_BATTLE:
		map_dat = Stage_2_B;
		break;
	case STAGE_3_1:
		map_dat = Stage_3_1;
		break;
	case STAGE_3_BATTLE:
		map_dat = Stage_3_B;
		break;
	case STAGE_4_1:
		map_dat = Stage_4_1;
		break;
	case STAGE_4_BATTLE:
		map_dat = Stage_4_B;
		break;
	case STAGE_5_1:
		map_dat = Stage_5_1;
		break;
	case STAGE_5_BATTLE:
		map_dat = Stage_5_B;
		break;
	default:
		map_dat = Stage_T_1;
		break;
	}

	int num = 0;
	for each(SMapInfo dat in map_dat)
	{
		m_mapchip[num] = NewGO<MapChip>(0);
		m_mapchip[num]->Start(dat.s_modelName, dat.s_position, dat.s_rotation, dat.s_scale);
		num++;
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