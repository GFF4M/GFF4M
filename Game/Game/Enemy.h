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
private:
	CSkinModel				m_skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	m_skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	m_characterController;			//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position;						//���W�B
	CQuaternion				m_rotation;						//��]�B
	CVector3				m_scale;						//�g��B
};

