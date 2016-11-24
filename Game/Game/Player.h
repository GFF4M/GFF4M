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
	CSkinModel				m_skinModel;					//�X�L�����f���B
	CSkinModelData			m_skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	m_characterController;			//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position;						//���W�B
	CQuaternion				m_rotation;						//��]�B
	float					m_angle;						//�p�x�B
};

extern Player* g_play;
