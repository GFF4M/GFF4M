#pragma once

#include "Map.h"
#include "Player.h"

class Scene : public IGameObject
{
public:
	enum Scenes
	{
		START,
		LOAD,

	};
	
	Scene();
	~Scene();

	void Start();
	void Update();

private:
	Player*		m_play;
	Map*		m_map;

	int			m_time = 0;
};

