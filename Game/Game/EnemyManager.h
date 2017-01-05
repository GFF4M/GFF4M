#pragma once

#include "Enemy.h"

#define ENEMY_NUM 3
#define ENEMY_DAT 4

class EnemyManager : public IGameObject
{
public:
	struct Enemies
	{
		Scenes			s_scene;		//発生場所
		char*			s_filename;		//ファイル名
		char*			s_name;			//名前
		int				s_hp;			//HP
		CVector3		s_pos;			//基本初期座標
		CVector3		s_look_pos;		//注視点
	};

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
	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,			"dog",		"敵",	100,	{ 3.0f,55.0f,0.0f },	{0.0f,1.0f,0.0f}},
		{	STAGE_1_1,			"Player",	"敵",	100,	{ 3.0f,55.0f,3.0f },	{0.0f,1.0f,0.0f}},
		{	STAGE_1_BATTLE,		"dog",		"敵",	100,	{ 3.0f,70.0f,0.0f },	{ 0.0f,1.0f,0.0f } },
		{	STAGE_1_BATTLE,		"Player",	"敵",	100,	{ 3.0f,70.0f,3.0f },	{ 0.0f,1.0f,0.0f } },
	};

	CRandom					m_random;
};

