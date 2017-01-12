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
	void paticle();

	void SetPos(CVector3 pos)
	{
		m_position = pos;
		m_characterController.SetPosition(pos);
	}

	CVector3 GetPos()
	{
		return m_position;
	}

	float GetAngle()
	{
		return m_angle;
	}

	CVector3 GetLookPos()
	{
		CVector3 retpos = m_position;

		retpos.Add(m_look_pos);

		return retpos;
	}

	float GetRadius()
	{
		return m_radius;
	}

	int GetHP()
	{
		return m_hp;
	}

	int GetMaxHP()
	{
		return m_maxhp;
	}

	int GetMP()
	{
		return m_mp;
	}

	int GetMaxMP()
	{
		return m_maxmp;
	}

	void SetMoveFlag(bool dat)
	{
		m_moveflg = dat;
	}

	enum AnimationStat{
		AnimationStand2,
		AnimationStand,
		AnimationDamage,
		Animationmagic,
		AnimationAttack,
		AnimationWalk,
		AnimationNum,
	};
	enum MagicNo {
		FIER,
		SUNDER,
		ICE,
		AQUA,
		WIND
	};
private:
	CSkinModel				m_skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	m_skinModelData;				//�X�L�����f���f�[�^�n���h���B
	CCharacterController	m_characterController;			//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position;						//���W�B
	CVector3				m_look_pos;						//�J�����̒����_
	CVector3				m_scale;
	CQuaternion				m_rotation;						//��]�B
	float					m_angle;						//�p�x�B

	float					m_radius;

	bool					m_dead;

	CAnimation				m_animation;						//�A�j���[�V�����B
	AnimationStat			m_animationStat;

	int						m_hp;
	int						m_maxhp;
	int						m_mp;
	int						m_maxmp;

	CParticleEmitter	*m_particle;
	int						m_magicNo;
	bool					m_ismagic;
	bool					m_moveflg;


};