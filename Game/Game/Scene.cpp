#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	m_load = nullptr;
	m_play = nullptr;
	m_map = nullptr;
	m_start = nullptr;
	m_scene = NOSCENES;
	m_loadstat = NOSTAT;
}

Scene::~Scene()
{
}

void Scene::Start()
{
	Change(START);
}

void Scene::Update()
{
	LoadCheck();

	static int a = 0;
	if (a < 101)
	{
		a++;
	}
	if (a == 100)
	{
		Change(STAGE_HOUSE);
	}
}

void Scene::LoadCheck()
{
	if (m_loadstat == NOSTAT)
	{
		return;
	}

	switch (m_loadstat)
	{
	case LOADSTART:
		m_load = NewGO<SC_Load>(0);
		m_loadstat = LOADING;
		break;

	case LOADING:
		m_loadstat = LOADFIN;
		break;

	case LOADFIN:
		m_load->Delete();
		m_load = nullptr;
		m_loadstat = NOSTAT;
		break;

	default:
		break;
	}
}

void Scene::Change(Scenes scenes)
{
	switch (m_scene)
	{
	case NOSTAT:
		break;

	case START:
		m_start->Delete();
		m_start = nullptr;
		m_play = NewGO<Player>(0);
		m_enem = NewGO<Enemy>(0);
		break;

	case STAGE_HOUSE:
		m_map->Delete();
		m_map = nullptr;
		break;

	default:
		break;
	}

	switch (scenes)
	{
	case START:
		if (m_play != nullptr)
		{
			m_play->Delete();
			m_play = nullptr;
		}
		if (m_enem != nullptr)
		{
			m_enem->Delete();
			m_enem = nullptr;
		}
		m_start = NewGO<SC_Start>(0);
		break;
	case STAGE_HOUSE:
		m_map = NewGO<Map>(0);
	default:
		break;
	}
	m_scene = scenes;

	m_loadstat = LOADSTART;

	LoadCheck();
}