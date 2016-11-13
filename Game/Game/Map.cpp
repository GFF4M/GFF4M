#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//マップの配置情報。
SMapInfo mapLocInfo[] = 
{
#include "MapData/Sample.h"
};

Map::Map()
{
}


Map::~Map()
{
}

void Map::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		m_mapchip[m_mapchipnum] = NewGO<MapChip>(0);
		//モデル名、座標、回転を与えてマップチップを初期化する。
		m_mapchip[m_mapchipnum]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		m_mapchipnum++;
	}
}

void Map::Update()
{

}

void Map::Change()
{
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < m_mapchipnum; i++) {
		m_mapchip[i]->Delete();
	}
	m_mapchipnum = 0;

	Start();
}