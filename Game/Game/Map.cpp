#include "stdafx.h"
#include "Map.h"

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
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
	for (int i = 0; i < numObject; i++) {
		//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
		NewGO<MapChip>(0) -> Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}
}

void Map::Update()
{

}

void Map::Delete()
{
	DeleteGO(this);
}