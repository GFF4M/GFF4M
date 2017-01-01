#pragma once
#include "MapChip.h"

#define MAP_CHIP_MAX 1000

class Map : public IGameObject
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Map();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Map();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start();

	/*!
	* @brief	�}�b�v�̕ύX�B
	*/
	void Change(Scenes scene);

	/*!
	* @brief	�X�V�B
	*/
	void Update();

	/*!
	* @brief	�폜�B
	*/
	void Delete();

private:
	MapChip*		m_mapchip[MAP_CHIP_MAX];
	bool			m_dead;
};

