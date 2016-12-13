#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy :public IGameObject
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
	void Start();

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

	/*!
	* @brief	移動限界値設定
	*			(初期座標を中心とした半径(引数1)だけ動ける)。
	*/
	void SetMoveLimit(float lim)
	{
		m_movelimit = lim;
	}

	CVector3 GetPos()
	{
		return m_position;
	}

private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelDataHandle	m_skinModelData;				//スキンモデルデータ。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CQuaternion				m_rotation;						//回転。
	CVector3				m_scale;						//拡大。
	float					m_movelimit;					//移動できる最長範囲	
};

