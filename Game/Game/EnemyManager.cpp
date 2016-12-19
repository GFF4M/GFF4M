#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Start(Scenes scene)
{
	switch (scene)
	{
	case EnemyManager::NOSCENES:
		break;
	case EnemyManager::START:
		break;
	case EnemyManager::STAGE_HOUSE:
		break;
	default:
		break;
	}
}

void EnemyManager::Update()
{

}

void EnemyManager::Render(CRenderContext& renderContext)
{

}

void EnemyManager::Delete()
{

}
