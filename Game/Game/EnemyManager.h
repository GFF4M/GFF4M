#pragma once

#include "Enemy.h"

#define ENEMY_NUM 1
#define ENEMY_DAT 2

class EnemyManager : public IGameObject
{
public:

	/*!
	* @brief	コンストラクタ。
	*/
	EnemyManager();

	/*!
	* @brief	デストラクタ。
	*/
	~EnemyManager();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start();

	/*!
	* @brief	更新。
	*/
	void Update();

	void Delete();

	/*!
	* @brief	敵の変更。
	*/
	void Change(Scenes scene);

	/*!
	* @brief	<引数1>に<引数2>番目に近いエネミーの座標を返す。(0が一番近い)
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

