#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"

class Scene : public IGameObject
{
public:
	enum Scenes
	{
		NOSTAT,
		START,
		STAGE_HOUSE,
	};
	
	Scene();
	~Scene();

	void Start();
	void Update();

	void Change(Scenes scenes);

private:
	Player*		m_play;
	Map*		m_map;
	SC_Start*	m_start;

	Scenes		m_scene;
	Scenes		m_changeto;
};

