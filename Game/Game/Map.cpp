#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char*	s_modelName;
	CVector3	s_position;
	CQuaternion	s_rotation;
	CVector3	s_scale;
};

//�}�b�v�̔z�u���B
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
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++)
	{
		//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
		m_mapchip[i] = NewGO<MapChip>(0);
		m_mapchip[i]->Start(mapLocInfo[i].s_modelName, mapLocInfo[i].s_position, mapLocInfo[i].s_rotation, mapLocInfo[i].s_scale);
	}

}

void Map::Update()
{
	if (m_dead)
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
}

void Map::Delete()
{
	m_dead = true;
}