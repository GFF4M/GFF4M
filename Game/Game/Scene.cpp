#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Start()
{
	m_map = NewGO<Map>(0);
	m_play = NewGO<Player>(0);
}

void Scene::Update()
{
}
