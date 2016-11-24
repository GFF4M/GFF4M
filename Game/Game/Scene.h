#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"
#include "Load.h"
#include "Enemy.h"

class Scene : public IGameObject
{
public:
	enum Scenes
	{
		NOSCENES,
		START,
		STAGE_HOUSE,
	};

	enum LoadStat
	{
		NOSTAT,
		LOADSTART,
		LOADING,
		LOADFIN,
	};
	
	Scene();
	~Scene();

	void Start();
	void Update();
	void LoadCheck();

	void Change(Scenes scenes);

private:
	SC_Load*	m_load;
	Player*		m_play;
	Enemy*		m_enem;
	Map*		m_map;
	SC_Start*	m_start;

	Scenes		m_scene;
	LoadStat	m_loadstat;
};
