#pragma once

#include "Enemy.h"

#define ENEMY_NUM 3
#define ENEMY_DAT 4

class EnemyManager : public IGameObject
{
public:
	struct Enemies
	{
		Scenes			s_scene;		//�����ꏊ
		char*			s_filename;		//�t�@�C����
		char*			s_name;			//���O
		int				s_hp;			//HP
		CVector3		s_pos;			//��{�������W
		CVector3		s_look_pos;		//�����_
	};

	/*!
	* @brief	�R���X�g���N�^�B
	*/
	EnemyManager();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~EnemyManager();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start();

	/*!
	* @brief	�X�V�B
	*/
	void Update();

	void Delete();

	/*!
	* @brief	�G�̕ύX�B
	*/
	void Change(Scenes scene);

	/*!
	* @brief	<����1>��<����2>�Ԗڂɋ߂��G�l�~�[�̍��W��Ԃ��B(0����ԋ߂�)
	*/
	Enemy* GetNearestEnemy(CVector3 pos, int no);

	int GetEnemyNum()
	{
		return m_enemy_num;
	}

	bool IsBattle()
	{
		return m_isBattle;
	}

private:
	bool					m_isBattle;

	Enemy*					m_enemy[ENEMY_NUM];
	int						m_enemy_num;
	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,			"dog",		"�G",	100,	{ 3.0f,55.0f,0.0f },	{0.0f,1.0f,0.0f}},
		{	STAGE_1_1,			"Player",	"�G",	100,	{ 3.0f,55.0f,3.0f },	{0.0f,1.0f,0.0f}},
		{	STAGE_1_BATTLE,		"dog",		"�G",	100,	{ 3.0f,70.0f,0.0f },	{ 0.0f,1.0f,0.0f } },
		{	STAGE_1_BATTLE,		"Player",	"�G",	100,	{ 3.0f,70.0f,3.0f },	{ 0.0f,1.0f,0.0f } },
	};

	CRandom					m_random;
};

