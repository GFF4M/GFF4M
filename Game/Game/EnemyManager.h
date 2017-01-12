#pragma once

#include "Enemy.h"

#define ENEMY_NUM 1
#define ENEMY_DAT 2

class EnemyManager : public IGameObject
{
public:

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

	CRandom					m_random;
};

