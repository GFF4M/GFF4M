#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

Scene	*g_scene;

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
		DeleteDat(m_load);
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
		DeleteDat(m_start);
		m_play = NewGO<Player>(0);
		g_play = m_play;
		m_enem = NewGO<Enemy>(0);
		break;

	case STAGE_HOUSE:
		DeleteDat(m_map);
		break;

	default:
		break;
	}

	switch (scenes)
	{
	case START:
		if (m_play != nullptr)
		{
			DeleteDat(m_play);
			g_play = nullptr;
		}

		if (m_enem != nullptr)
		{
			DeleteDat(m_enem);
		}

		m_start = NewGO<SC_Start>(0);
		g_gameCamera->SetTarget(Camera::Target::NOTARGET);
		break;

	case STAGE_HOUSE:
		m_map = NewGO<Map>(0);
		g_gameCamera->SetTarget(Camera::Target::PLAYER);
		break;

	default:
		break;
	}
	m_scene = scenes;

	m_loadstat = LOADSTART;

	LoadCheck();
}
