#pragma once
#include "MapChip.h"
#define MAP_CHIP_MAX 1000

class Map : public IGameObject
{
public:
	Map();
	~Map();
	void Start();
	void SetField();
	void Update();

	void Delete();

private:
};

