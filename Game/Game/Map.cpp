#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	modelName;
	CVector3	position;
	CQuaternion	rotation;
	CVector3	scale;
};

//�}�b�v�̔z�u���B
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
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) 
	{
		//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
		m_mapchip[i] = NewGO<MapChip>(0);
		m_mapchip[i]->Start(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation, mapLocInfo[i].scale);
	}
}

void Map::Update()
{
}

void Map::Delete()
{
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++)
	{
		m_mapchip[i]->Delete();
	}
	DeleteGO(this);
}