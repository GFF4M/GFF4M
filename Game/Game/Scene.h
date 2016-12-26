#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"
#include "Load.h"
#include "EnemyManager.h"
#include "Bar.h"

#define CHANGEDAT_NUM 47
class Scene : public IGameObject
{
public:
	enum LoadStat
	{
		LS_NOSTAT,
		LS_LOADSTART,
		LS_LOADING,
		LS_LOADFIN,
	};

	enum ChangeStat
	{
		CS_NOSTAT,
		CS_ADD,
		CS_DELETE,
		CS_CHANGE,
	};

	/*
	1...遷移元
	2...遷移先
	3...データ更新-スタート画面
	4...データ更新-プレイヤ
	5...データ更新-エネミー
	6...データ更新-マップ
	*/
	struct ChangeDat
	{
		Scenes			s_now_scene;
		Scenes			s_move_scene;

		ChangeStat		s_change_start;
		ChangeStat		s_change_player;
		ChangeStat		s_change_enemy;
		ChangeStat		s_change_map;

		CVector3		s_next_pos;
	};


	/*!
	* @brief	コンストラクタ。
	*/
	Scene();

	/*!
	* @brief	デストラクタ。
	*/
	~Scene();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start();

	/*!
	* @brief	更新。
	*/
	void Update();


	/*!
	* @brief	ロード画面の操作。
	*/
	void LoadCheck();

	/*!
	* @brief	画面遷移。
	*/
	void Change(Scenes scenes);

	/*!
	* @brief	プレイヤと敵とのあたり判定。
	*/
	void Collision();

	Player* GetPlayer()
	{
		return m_play;
	}

private:
	SC_Load*			m_load;
	Player*				m_play;
	EnemyManager*		m_enem_manage;
	Map*				m_map;
	SC_Start*			m_start;
	SC_Bar*				m_bar;

	Scenes				m_scene;
	LoadStat			m_loadstat;

	CameraTarget		m_cameraTarget;

	const ChangeDat		m_changedat[CHANGEDAT_NUM] =
	{
		{ NOSCENES,				START,					CS_ADD,			CS_NOSTAT,		CS_ADD,			CS_NOSTAT	, CVector3(0.0f,0.0f,0.0f)},

		{ START,				STAGE_HOUSE,			CS_DELETE,		CS_ADD,			CS_NOSTAT,		CS_ADD		, CVector3(0.0f,55.0f,0.0f) },

		{ STAGE_HOUSE,			STAGE_1_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(10.0f,35.0f,0.0f) },
		{ STAGE_HOUSE,			STAGE_2_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_HOUSE,			STAGE_3_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_HOUSE,			STAGE_4_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_HOUSE,			STAGE_5_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		
		{ STAGE_1_1,			STAGE_1_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(30.0f,55.0f,0.0f) },
		{ STAGE_2_1,			STAGE_2_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_1,			STAGE_3_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_1,			STAGE_4_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_1,			STAGE_5_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_1,			STAGE_1_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_1,			STAGE_2_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_1,			STAGE_3_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_1,			STAGE_4_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_1,			STAGE_5_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_BATTLE,		STAGE_1_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_BATTLE,		STAGE_2_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_BATTLE,		STAGE_3_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_BATTLE,		STAGE_4_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_BATTLE,		STAGE_5_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_2,			STAGE_1_BOSS,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_2,			STAGE_2_BOSS,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_2,			STAGE_3_BOSS,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_2,			STAGE_4_BOSS,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_2,			STAGE_5_BOSS,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_2,			STAGE_1_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_2,			STAGE_2_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_2,			STAGE_3_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_2,			STAGE_4_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_2,			STAGE_5_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_BATTLE,		STAGE_1_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_BATTLE,		STAGE_2_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_BATTLE,		STAGE_3_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_BATTLE,		STAGE_4_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_BATTLE,		STAGE_5_2,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_BOSS,			STAGE_1_BOSS_BATTLE,	CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_NOSTAT	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_BOSS,			STAGE_1_BOSS_BATTLE,	CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_NOSTAT	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_BOSS,			STAGE_1_BOSS_BATTLE,	CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_NOSTAT	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_BOSS,			STAGE_1_BOSS_BATTLE,	CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_NOSTAT	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_BOSS,			STAGE_1_BOSS_BATTLE,	CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_NOSTAT	, CVector3(0.0f,15.0f,0.0f) },

		{ STAGE_1_BOSS_BATTLE,	STAGE_HOUSE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_2_BOSS_BATTLE,	STAGE_HOUSE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_3_BOSS_BATTLE,	STAGE_HOUSE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_4_BOSS_BATTLE,	STAGE_HOUSE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
		{ STAGE_5_BOSS_BATTLE,	STAGE_HOUSE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,15.0f,0.0f) },
	};
};

extern Scene	*g_scene;