#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"
#include "Load.h"
#include "EnemyManager.h"
#include "Bar.h"

class Scene : public IGameObject
{
public:
	enum Scenes
	{
		NOSCENES,
		//スタート画面
		START,
		//家
		STAGE_HOUSE,
		//風
		STAGE_1_1,
		STAGE_1_2,
		STAGE_1_BOSS,
		//炎
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_BOSS,
		//氷
		STAGE_3_1,
		STAGE_3_2,
		STAGE_3_BOSS,
		//雷
		STAGE_4_1,
		STAGE_4_2,
		STAGE_4_BOSS,
		//光
		STAGE_5_1,
		STAGE_5_2,
		STAGE_5_BOSS,
	};

	enum LoadStat
	{
		NOSTAT,
		LOADSTART,
		LOADING,
		LOADFIN,
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

private:
	SC_Load*			m_load;
	EnemyManager*		m_enem_manage;
	Map*				m_map;
	SC_Start*			m_start;
	SC_Bar*				m_bar;

	Scenes				m_scene;
	LoadStat			m_loadstat;
};

extern Scene	*g_scene;
