#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"
#include "Load.h"
#include "Enemy.h"
#include "Bar.h"

#define ENEMY_NUM 1

class Scene : public IGameObject
{
public:
	enum Scenes
	{
		NOSCENES,
		START,
		STAGE_HOUSE,
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
	SC_Load*	m_load;
	Enemy*		m_enem[ENEMY_NUM];
	Map*		m_map;
	SC_Start*	m_start;
	SC_Bar*		m_bar;

	Scenes		m_scene;
	LoadStat	m_loadstat;
};

extern Scene	*g_scene;
