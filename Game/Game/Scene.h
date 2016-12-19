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
		//�X�^�[�g���
		START,
		//��
		STAGE_HOUSE,
		//��
		STAGE_1_1,
		STAGE_1_2,
		STAGE_1_BOSS,
		//��
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_BOSS,
		//�X
		STAGE_3_1,
		STAGE_3_2,
		STAGE_3_BOSS,
		//��
		STAGE_4_1,
		STAGE_4_2,
		STAGE_4_BOSS,
		//��
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
	SC_Load*			m_load;
	EnemyManager*		m_enem_manage;
	Map*				m_map;
	SC_Start*			m_start;
	SC_Bar*				m_bar;

	Scenes				m_scene;
	LoadStat			m_loadstat;
};

extern Scene	*g_scene;
