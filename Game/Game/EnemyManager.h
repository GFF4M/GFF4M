#pragma once

#include "Enemy.h"

#define ENEMY_NUM 5
#define ENEMY_DAT 2

class EnemyManager : public IGameObject
{
public:

	struct Enemies
	{
		Scenes			s_scene;		//�o��V�[��
		char*			s_filename;		//�t�@�C����
		char*			s_name;			//���O
		int				s_hp;			//HP
		float			s_movelim;		//�ړ�����
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

	/*!
	* @brief	�G�̕ύX�B
	*/

	void Delete();


	void Change(Scenes scene, bool isBattle);


private:
	Enemy*					m_enemy[ENEMY_NUM];
	int cnt;
	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,	"dog",		"�G",	100,	15.5f,	{0.0f,1.0f,0.0f}},
		{	STAGE_1_1,	"Player",	"�G",	100,	12.5f,	{0.0f,1.0f,0.0f}},
	};

	CRandom					m_random;

	bool					m_isBattle;
};

