#pragma once

#include "Enemy.h"

#define ENEMY_NUM 5
#define ENEMY_DAT 2

class EnemyManager : public IGameObject
{
public:

	struct Enemies
	{
		Scenes			s_scene;		//登場シーン
		char*			s_filename;		//ファイル名
		char*			s_name;			//名前
		int				s_hp;			//HP
		float			s_movelim;		//移動制限
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

	/*!
	* @brief	敵の変更。
	*/

	void Delete();


	void Change(Scenes scene, bool isBattle);


private:
	Enemy*					m_enemy[ENEMY_NUM];
	int cnt;
	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,	"dog",		"敵",	100,	15.5f,	{0.0f,1.0f,0.0f}},
		{	STAGE_1_1,	"Player",	"敵",	100,	12.5f,	{0.0f,1.0f,0.0f}},
	};

	CRandom					m_random;

	bool					m_isBattle;
};

