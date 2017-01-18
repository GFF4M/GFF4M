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

	m_player_hp_bar = nullptr;
	m_player_mp_bar = nullptr;
	m_scene = NOSCENES;
	m_loadstat = LS_NOSTAT;

	m_cameraTarget = CT_NOTARGET;

	m_loadsavedat = false;
	m_loadpos = CVector3::Zero;

	m_sound_bgm_play = NewGO<CSoundSource>(0);
	m_sound_bgm_play->Init("Assets/Sound/bgm_maoudamashii_fantasy10.wav");

	m_sound_bgm_start = NewGO<CSoundSource>(0);
	m_sound_bgm_start->Init("Assets/Sound/bgm_maoudamashii_piano25.wav");

	m_gameover = nullptr;
	m_result = nullptr;
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
		g_gameCamera->SetTarget(m_cameraTarget);
	}
	if (m_cameraTarget == CT_NOTARGET)
	{
		g_gameCamera->SetTarget(CT_PLAYER);
	}

	Collision();
	//ロード画面を表示するか？
	LoadCheck();
	SetSaveDat();
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

		m_sound_bgm_play->Stop();
		m_sound_bgm_start->Stop();
		switch (m_scene)
		{
		case START:
			m_sound_bgm_start->Play(true);
			break;
		case STAGE_T_1:
			m_sound_bgm_play->Play(true);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

void Scene::Change(Scenes scenes)
{
	if (scenes == NOSCENES)
	{
		return;
	}

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

	switch (m_scene)
	{
	case NEWGAME:
		Change(STAGE_T_1);
		break;
	case CONTINUE:
		if (!GetSaveDat())
		{
			Change(STAGE_T_1);
		}
		break;
	default:
		break;
	}

	if (m_scene == GAMEOVER)
	{
		m_gameover = NewGO<SC_Gameover>(1);
		return;
	}
	if (m_scene == GAME_CLEAR)
	{
		m_result = NewGO<SC_Result>(1);
		return;
	}

	//ロード画面開始
	if (m_loadstat == LS_NOSTAT)
	{
		m_loadstat = LS_LOADSTART;
	}
}

void Scene::ChangeData()
{
	if (m_dat_num < 0)
	{
		return;
	}

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

	if (m_scene == START)
	{
		if (m_gameover != nullptr)
		{
			m_gameover->Delete();
			m_gameover = nullptr;
		}
		if (m_result != nullptr)
		{
			m_result->Delete();
			m_result = nullptr;
		}
	}

	//プレイヤのデータ更新
	switch (dat.s_change_player)
	{
	case CS_ADD:
		m_play = NewGO<Player>(0);
		m_magic = NewGO<SC_Magic>(0);
		m_player_hp_bar = NewGO<SC_Bar>(0);
		m_player_hp_bar->Start(SC_Bar::Bar_Target::PLAYER_HP);
		m_player_mp_bar = NewGO<SC_Bar>(0);
		m_player_mp_bar->Start(SC_Bar::Bar_Target::PLAYER_MP);
		break;
	case CS_DELETE:
		m_play->Delete();
		m_play = nullptr;
		m_magic->Delete();
		m_magic=nullptr;
		m_player_hp_bar->Delete();
		m_player_mp_bar->Delete();
		m_player_hp_bar = nullptr;
		m_player_mp_bar = nullptr;
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
		m_enemy_hp_bar = NewGO<SC_Bar>(0);
		m_enemy_hp_bar->Start(SC_Bar::Bar_Target::ENEMY_HP);
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
		switch (m_scene)
		{
		case NOSCENES:
		case START:
		case NEWGAME:
		case CONTINUE:
			m_play->SetMoveFlag(false);
			break;
		default:
			m_play->SetMoveFlag(true);
			break;
		}

		if (m_loadsavedat)
		{
			m_play->SetPos(m_loadpos);
			m_loadsavedat = false;
		}
		else
		{
			m_play->SetPos(dat.s_next_pos);
		}
	}
}

void Scene::Collision()
{
	if (m_play == nullptr)
	{
		return;
	}

	if (m_enem_manage == nullptr)
	{
		return;
	}

	if (m_enem_manage->GetEnemyNum() == 0)
	{
		return;
	}

	if (m_loadstat != LS_NOSTAT)
	{
		return;
	}

	if (m_enem_manage->IsBattle())
	{
		return;
	}

	CVector3 dis = m_play->GetPos();
	Enemy* enemy = m_enem_manage->GetNearestEnemy(m_play->GetPos(), 0);

	dis.Subtract(enemy->GetPos());
	dis.y = 0.0f;

	Scenes scenes = NOSCENES;
	if (dis.Length() <= 50.0f)
	{
		switch (m_scene)
		{
		case STAGE_T_1:
			scenes = STAGE_T_BATTLE;
			break;
		case STAGE_1_1:
			scenes = STAGE_1_BATTLE;
			break;
		case STAGE_2_1:
			scenes = STAGE_2_BATTLE;
			break;
		case STAGE_3_1:
			scenes = STAGE_3_BATTLE;
			break;
		case STAGE_4_1:
			scenes = STAGE_4_BATTLE;
			break;
		case STAGE_5_1:
			scenes = STAGE_5_BATTLE;
			break;
		default:
			break;
		}
	}
	if (scenes == NOSCENES)
	{
		return;
	}
	Change(scenes);
	m_enem_manage->IsBattle();
}

bool Scene::SetSaveDat()
{
	bool ret = false;

	switch (m_scene)
	{
	case STAGE_T_1:
	case STAGE_1_1:
	case STAGE_2_1:
	case STAGE_3_1:
	case STAGE_4_1:
	case STAGE_5_1:
		break;
	default:
		ret = true;
		break;
	}

	if (ret)
	{
		return false;
	}



	FILE *fp;

	fp = fopen(SAVE, "w");

	if (fp == NULL)
	{
		return false;
	}

	char dat[1000];

	sprintf(dat, "%d,%.5f,%.5f,%.5f,%d,%d",
		(int)m_scene,
		m_play->GetPos().x,
		m_play->GetPos().y,
		m_play->GetPos().z,
		m_play->GetHP(),
		m_play->GetMP()
	);

	fputs(dat, fp);

	fclose(fp);

	return true;
}

bool Scene::GetSaveDat()
{
	bool ret = false;
	switch (m_scene)
	{
	case CONTINUE:
		break;

	default:
		ret = true;
		break;
	}

	if (ret)
	{
		return false;
	}
	
	FILE *fp;

	fp = fopen(SAVE, "r");

	if (fp == NULL)
	{
		return false;
	}

	char dat[1000];

	fgets(dat, 1000, fp);

	Scenes r_scene;
	CVector3 r_pos;
	int r_hp;
	int r_mp;

	sscanf(dat, "%d,%f,%f,%f,%d,%d", 
		&r_scene,
		&r_pos.x,
		&r_pos.y,
		&r_pos.z,
		&r_hp,
		&r_mp
	);

	m_play->SetHP(r_hp);
	m_play->SetMP(r_mp);

	Change(r_scene);

	m_loadsavedat = true;
	m_loadpos = r_pos;

	fclose(fp);

	return true;
}

void Scene::Encryption(char *dat)
{
	int a = 0x43;
}