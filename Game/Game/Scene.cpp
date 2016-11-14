#include "stdafx.h"
#include "Scene.h"
#include "Text.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Start()
{
	NewGO<Text>(0);
}

void Scene::Update()
{
}
