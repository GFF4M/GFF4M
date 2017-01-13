#pragma once

#include "Map.h"
#include "Player.h"
#include "Start.h"
#include "Load.h"
#include "Magic.h"
#include "EnemyManager.h"
#include "Bar.h"

#define CHANGEDAT_NUM	22

#define SAVE			"SaveDat.txt"

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
	1...�J�ڌ�
	2...�J�ڐ�
	3...�f�[�^�X�V-�X�^�[�g���
	4...�f�[�^�X�V-�v���C��
	5...�f�[�^�X�V-�G�l�~�[
	6...�f�[�^�X�V-�}�b�v
	7...�ړ�����W
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

	/*
	1...�V�[��
	2...�|�W�V����
	3...�A���O��
	*/
	struct SaveData
	{
		Scenes			s_scene;
		CVector3		s_pos;
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
	* @brief	�f�[�^�X�V
	*/
	void ChangeData();

	/*!
	* @brief	�v���C���ƓG�Ƃ̂����蔻��B
	*/
	void Collision();

	Player* GetPlayer()
	{
		return m_play;
	}

	EnemyManager* GetEnemy()
	{
		return m_enem_manage;
	}

	bool SetSaveDat();

	bool GetSaveDat();

	/*!
	* @brief	�Í���(�������ł��܂�)
	*
	*	1...char*:�Í������镶����
	*/
	void Encryption(char *);

private:
	SC_Load*			m_load;
	Player*				m_play;
	EnemyManager*		m_enem_manage;
	Map*				m_map;
	SC_Start*			m_start;
	SC_Bar*				m_hp_bar;
	SC_Bar*				m_mp_bar;
	Magic*				m_magic;

	Scenes				m_scene;
	LoadStat			m_loadstat;

	CameraTarget		m_cameraTarget;

	bool				m_loadsavedat;
	CVector3			m_loadpos;

	int					m_dat_num;
	const ChangeDat		m_changedat[CHANGEDAT_NUM] =
	{
		{ NOSCENES,				START,					CS_ADD,			CS_ADD,			CS_ADD,			CS_ADD		, CVector3(0.0f,0.0f,0.0f)},
	
		{ START,				NEWGAME,				CS_NOSTAT,		CS_NOSTAT,		CS_NOSTAT,		CS_NOSTAT	, CVector3(0.0f,55.0f,0.0f) },
		{ START,				CONTINUE,				CS_NOSTAT,		CS_NOSTAT,		CS_NOSTAT,		CS_NOSTAT	, CVector3(0.0f,55.0f,0.0f) },
		
		{ NEWGAME,				STAGE_T_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },

		{ CONTINUE,				STAGE_T_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ CONTINUE,				STAGE_1_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ CONTINUE,				STAGE_2_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ CONTINUE,				STAGE_3_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ CONTINUE,				STAGE_4_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ CONTINUE,				STAGE_5_1,				CS_DELETE,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },

		{ STAGE_T_1,			STAGE_T_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_1_1,			STAGE_1_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_2_1,			STAGE_2_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_3_1,			STAGE_3_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_4_1,			STAGE_4_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_5_1,			STAGE_5_BATTLE,			CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		
		{ STAGE_T_BATTLE,		STAGE_1_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_1_BATTLE,		STAGE_2_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_2_BATTLE,		STAGE_3_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_3_BATTLE,		STAGE_4_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_4_BATTLE,		STAGE_5_1,				CS_NOSTAT,		CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },
		{ STAGE_5_BATTLE,		START,					CS_ADD,			CS_NOSTAT,		CS_CHANGE,		CS_CHANGE	, CVector3(0.0f,55.0f,0.0f) },

	};
};

extern Scene	*g_scene;