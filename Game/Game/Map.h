#pragma once
#include "MapChip.h"
#define MAP_CHIP_MAX 1000

class Map : public IGameObject
{
public:

	/*!
	* @brief	コンストラクタ。
	*/
	Map();

	/*!
	* @brief	デストラクタ。
	*/
	~Map();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start();

	/*!
	* @brief	更新。
	*/
	void Update();

	/*!
	* @brief	削除。
	*/
	void Delete();

private:
	MapChip*		m_mapchip[100];
};

