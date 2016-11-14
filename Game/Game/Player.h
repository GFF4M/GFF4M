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
	CVector3				m_position = CVector3::Zero;	//座標。
};

