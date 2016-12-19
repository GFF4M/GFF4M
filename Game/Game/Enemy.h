#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy :public IGameObject
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
	void Start(char* filename, char* enemyname, int maxhp);

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

	/*!
	* @brief	�ړ����E�l�ݒ�
	*			(�������W�𒆐S�Ƃ������a(����1)����������)�B
	*/
	void SetMoveLimit(float lim)
	{
		m_movelimit = lim;
	}

	CVector3 GetPos()
	{
		return m_position;
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
	CQuaternion				m_rotation;						//��]�B
	CVector3				m_scale;						//�g��B
	float					m_movelimit;					//�ړ��ł���Œ��͈�

	float					m_radius;

	bool					m_dead;

	struct EnemyDat
	{
		char*				s_filename;
		char*				s_name;
		int					s_hp;
		int					s_maxhp;
	};

	EnemyDat				m_enemydat;
	CRandom					m_random;
};

