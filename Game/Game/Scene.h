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
	* @brief	�R���X�g���N�^�B
	*/
	Scene();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Scene();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start();


	/*!
	* @brief	�X�V�B
	*/
	void Update();


	/*!
	* @brief	���[�h��ʂ̑���B
	*/
	void LoadCheck();

	/*!
	* @brief	��ʑJ�ځB
	*/
	void Change(Scenes scenes);

	/*!
	* @brief	�v���C���ƓG�Ƃ̂����蔻��B
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
