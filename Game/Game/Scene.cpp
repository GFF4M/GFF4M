#include "stdafx.h"
#include "Scene.h"
#include "Start.h"

Scene::Scene()
{
	m_scene = NOSTAT;
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
	static int a = 0;
	a++;
	if (a > 100)
	{
		Change(STAGE_HOUSE);
		a = 0;
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
}