#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
	CVector3	scale;
};

//マップの配置情報。
SMapInfo mapLocInfo[] = 
{
#include "MapData/locationInfo2.h"
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
		m_mapchip[i]->Start(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation, mapLocInfo[i].scale);
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