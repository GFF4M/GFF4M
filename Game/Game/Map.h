#pragma once
#include "MapChip.h"
#define MAP_CHIP_MAX 1000

class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Start();
	void Update();

	void Change();

private:
	MapChip*	m_mapchip[MAP_CHIP_MAX];
	int			m_mapchipnum = 0;
};

