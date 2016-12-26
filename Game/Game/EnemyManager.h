#pragma once

#include "Enemy.h"

#define ENEMY_NUM 1
#define ENEMY_DAT 2

class EnemyManager : public IGameObject
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

	struct Enemies
	{
		Scenes			s_scene;
		char*			s_filename;
		char*			s_name;
		int				s_hp;
		float			s_movelim;
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
	void Start(Scenes scene);

	/*!
	* @brief	�X�V�B
	*/
	void Update();

	/*!
	* @brief	�폜�B
	*/
	void Delete();


private:
	Enemy*					m_enemy[ENEMY_NUM];

	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,	"dog","�G",100,5.0f  },
		{	STAGE_1_1,	"Player","�G",100,0.5f },
	};

	CRandom					m_random;
};

