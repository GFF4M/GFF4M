#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();
	void Move();

	void SetPos(CVector3 pos)
	{
		m_position = pos;
	}

	CVector3 GetPos()
	{
		return m_position;
	}

private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelData			m_skinModelData;				//スキンモデルデータ。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CQuaternion				m_rotation;						//回転。
	float					m_angle;						//角度。
};

extern Player* g_play;
