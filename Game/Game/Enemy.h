#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();
	void Move();

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

