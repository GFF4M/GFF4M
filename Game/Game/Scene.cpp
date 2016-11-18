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
	a++;
	if (a > 100)
	{
		Change(STAGE_HOUSE);
		a = 0;
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
		break;

	case STAGE_HOUSE:
		m_map->Delete();
		break;

	default:
		break;
	}

	switch (scenes)
	{
	case START:
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