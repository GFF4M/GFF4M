#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy : public IGameObject
{
public:
	struct EneDat
	{
		Scenes			s_scene;		//�����ꏊ
		char*			s_filename;		//�t�@�C����
		char*			s_name;			//���O
		int				s_hp;			//HP
		CVector3		s_pos;			//��{�������W
		CVector3		s_look_pos;		//�����_
		CVector3		s_scale;		//�X�P�[��
		MagicNo			s_property;		//����
	};

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
	void Start(EneDat enedat, bool isBattle);

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

	void Particle();

	CVector3 GetPos()
	{
		return m_position;
	}

	CVector3 GetLookPos()
	{
		CVector3 retpos = m_position;

		CVector3 addpos = m_look_pos;
		addpos.Scale(m_scale);

		retpos.Add(addpos);

		return retpos;
	}

	float GetRadius()
	{
		return m_radius;
	}

	void SetDamage(int damage)
	{
		if (damage <= 0)
		{
			return;
		}
		m_hp -= damage;
		if (m_hp < 0)
		{
			m_hp = 0;
		}
	}

	int GetHP()
	{
		return m_hp;
	}

	CVector3 GetScale()
	{
		return m_scale;
	}

	enum AnimationStat
	{
		AnimationAttack,
		AnimationWalk,
		AnimationStand
	};
private:
	CSkinModel				m_skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	m_skinModelData;				//�X�L�����f���f�[�^�B
	CCharacterController	m_characterController;			//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position;						//���W�B
	CVector3				m_look_pos;						//�����_�B
	CQuaternion				m_rotation;						//��]�B
	CVector3				m_scale;						//�g��B
	float					m_angle;						//�p�x�B

	MagicNo					m_property;						//����
	float					m_radius;

	bool					m_dead;

	char*					m_filename;
	char*					m_name;
	int						m_hp;
	int						m_maxhp;

	CRandom					m_random;
	bool					m_isBattle;

	CAnimation				m_animation;						//�A�j���[�V�����B
	AnimationStat			m_animationStat;

	float					m_attack_timer;

	CParticleEmitter		*m_particle;
	float					m_particletimer;

	int						m_magicNo;
};
