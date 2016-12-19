#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	s_modelName;
	CVector3	s_position;
	CQuaternion	s_rotation;
	CVector3	s_scale;
};

//マップの配置情報。
SMapInfo mapLocInfo[] = 
{


#include "MapData/sougen2.h"

};

Map::Map()
{
	m_dead = false;
}

Map::~Map()
{
}

void Map::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++)
	{
		//モデル名、座標、回転を与えてマップチップを初期化する。
		m_mapchip[i] = NewGO<MapChip>(0);
		m_mapchip[i]->Start(mapLocInfo[i].s_modelName, mapLocInfo[i].s_position, mapLocInfo[i].s_rotation, mapLocInfo[i].s_scale);
	}

}

void Map::Update()
{
	if (m_dead)
	{
		//マップにいくつのオブジェクトが配置されているか調べる。
		int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++)
		{
			m_mapchip[i]->Delete();
		}
		DeleteGO(this);
	}
}

void Map::Delete()
{
	m_dead = true;
}