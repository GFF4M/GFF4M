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
		//スタート画面
		START,
		//家
		STAGE_HOUSE,
		//風
		STAGE_1_1,
		STAGE_1_2,
		STAGE_1_BOSS,
		//炎
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_BOSS,
		//氷
		STAGE_3_1,
		STAGE_3_2,
		STAGE_3_BOSS,
		//雷
		STAGE_4_1,
		STAGE_4_2,
		STAGE_4_BOSS,
		//光
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
	void Start(Scenes scene);

	/*!
	* @brief	更新。
	*/
	void Update();

	/*!
	* @brief	削除。
	*/
	void Delete();


private:
	Enemy*					m_enemy[ENEMY_NUM];

	const Enemies			m_enemiesdat[ENEMY_DAT] =
	{ 
		{	STAGE_1_1,	"dog","敵",100,5.0f  },
		{	STAGE_1_1,	"Player","敵",100,0.5f },
	};

	CRandom					m_random;
};

