#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy : public IGameObject
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Enemy();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Enemy();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start(char* filename, char* enemyname, int maxhp, float movelim, CVector3 look_pos);

	/*!
	* @brief	�X�V�B
	*/
	void Update();
	
	/*!
	* @brief	�`��B
	*/
	void Render(CRenderContext& renderContext);

	/*!
	* @brief	�폜�B
	*/
	void Delete();

	/*!
	* @brief	�ړ��B
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
	CSkinModel				m_skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	m_skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	m_characterController;			//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position;						//���W�B
	CVector3				m_look_pos;						//�����_�B
	CQuaternion				m_rotation;						//��]�B
	CVector3				m_scale;						//�g��B

	float					m_radius;

	bool					m_dead;

	char*					m_filename;
	char*					m_name;
	int						m_hp;
	int						m_maxhp;
	float					m_movelim;

	CRandom					m_random;
};
