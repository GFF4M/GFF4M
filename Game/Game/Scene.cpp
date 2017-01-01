#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

Scene	*g_scene;

Scene::Scene()
{
	//メンバ変数初期化
	m_load = nullptr;
	m_play = nullptr;
	m_map = nullptr;
	m_start = nullptr;
	m_enem_manage = nullptr;

	m_bar = nullptr;
	m_scene = NOSCENES;
	m_loadstat = LS_NOSTAT;

	m_cameraTarget = CT_PLAYER;
}

Scene::~Scene()
{
}

void Scene::Start()
{
	//スタート画面に遷移
	Change(START);
}

void Scene::Update()
{
	if (GetAsyncKeyState('Q'))
	{
		Change(STAGE_1_1);
	}
	if (Pad(0).IsTrigger(enButtonLB1))
	{
		switch (m_cameraTarget)
		{
		case CT_PLAYER:
			m_cameraTarget = CT_ENEMY;
			break;
		case CT_ENEMY:
			m_cameraTarget = CT_PLAYER;
			break;
		default:
			break;
		}
	}

	g_gameCamera->SetTarget(m_cameraTarget);

	//ロード画面を表示するか？
	Collision();
	LoadCheck();
}

void Scene::LoadCheck()
{
	//ロード画面を出さないなら早期リターン
	if (m_loadstat == LS_NOSTAT)
	{
		return;
	}

	switch (m_loadstat)
	{
	//ロード開始
	case LS_LOADSTART:
		m_load = NewGO<SC_Load>(1);
		m_loadstat = LS_LOADING;
		break;

	//ロード中
	case LS_LOADING:
		ChangeData();
		m_loadstat = LS_LOADFIN;
		break;

	//ロード終了
	case LS_LOADFIN:
		m_load->Delete();
		m_load = nullptr;
		m_loadstat = LS_NOSTAT;
		break;

	default:
		break;
	}
}

void Scene::Change(Scenes scenes)
{
	bool found = false;

	m_dat_num = 0;
	//切り替え可能か調べる
	for each(ChangeDat ch_dat in m_changedat)
	{
		if (m_scene == ch_dat.s_now_scene && scenes == ch_dat.s_move_scene)
		{
			found = true;
			break;
		}
		m_dat_num++;
	}
	
	//見つからなかった
	if (!found)
	{
		m_dat_num = -1;
		return;
	}

	m_scene = scenes;

	//ロード画面開始
	if (m_loadstat == LS_NOSTAT)
	{
		m_loadstat = LS_LOADSTART;
	}
}

void Scene::ChangeData()
{
	ChangeDat dat = m_changedat[m_dat_num];

	//スタートのデータ更新
	switch (dat.s_change_start)
	{
	case CS_ADD:
		m_start = NewGO<SC_Start>(1);
		break;
	case CS_DELETE:
		m_start->Delete();
		m_start = nullptr;
		break;
	default:
		break;
	}

	//プレイヤのデータ更新
	switch (dat.s_change_player)
	{
	case CS_ADD:
		m_play = NewGO<Player>(0);
		break;

	case CS_DELETE:
		m_play->Delete();
		m_play = nullptr;
		break;
	default:
		break;
	}

	//エネミーのデータ更新
	switch (dat.s_change_enemy)
	{
	case CS_ADD:
		m_enem_manage = NewGO<EnemyManager>(0);
		m_enem_manage->Change(dat.s_move_scene);
		break;
	case CS_CHANGE:
		m_enem_manage->Change(dat.s_move_scene);
		break;
	default:
		break;
	}

	//マップのデータ更新
	switch (dat.s_change_map)
	{
	case CS_ADD:
		m_map = NewGO<Map>(0);
		m_map->Change(dat.s_move_scene);
		break;
	case CS_CHANGE:
		m_map->Change(dat.s_move_scene);
		break;
	default:
		break;
	}

	if (m_play != nullptr)
	{
		m_play->SetPos(dat.s_next_pos);
	}
}

void Scene::Collision()
{
	if (m_play == nullptr)
	{
		return;
	}

	/*
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		CVector3 distance = g_play->GetPos();

		distance.Subtract(m_enem_manage->GetPos());

		if (distance.Length() <= g_play->GetRadius() + m_enem[i]->GetRadius() + 0.05f)
		{
			g_play->Delete();
			g_play = nullptr;
			m_bar->Delete();
			m_bar = nullptr;
			m_enem[i]->Delete();
			m_enem[i] = nullptr;
			m_map->Delete();
			m_map = nullptr;
			Change(STAGE_HOUSE);
			g_play = NewGO<Player>(0);
			m_bar = NewGO<SC_Bar>(0);
			m_enem[i] = NewGO<Enemy>(0);
			m_enem[i]->Start("Player", "Enemy", 100);
		}
	}*/
}
