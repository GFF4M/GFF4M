#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy : public IGameObject
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Enemy();

	/*!
	* @brief	デストラクタ。
	*/
	~Enemy();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start(char* filename, char* enemyname, int maxhp, float movelim, CVector3 look_pos);

	/*!
	* @brief	更新。
	*/
	void Update();
	
	/*!
	* @brief	描画。
	*/
	void Render(CRenderContext& renderContext);

	/*!
	* @brief	削除。
	*/
	void Delete();

	/*!
	* @brief	移動。
	*/
	void Move();

	CVector3 GetPos()
	{
		return m_position;
	}

	CVector3 GetLookPos()
	{
		return m_look_pos;
	}

	float GetRadius()
	{
		return m_radius;
	}

private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelDataHandle	m_skinModelData;				//スキンモデルデータ。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CVector3				m_look_pos;						//注視点。
	CQuaternion				m_rotation;						//回転。
	CVector3				m_scale;						//拡大。

	float					m_radius;

	bool					m_dead;

	char*					m_filename;
	char*					m_name;
	int						m_hp;
	int						m_maxhp;
	float					m_movelim;

	CRandom					m_random;
};
