#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "StatusAilment.h"

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
	void Particle();
	void DeadCheck();
	void Charge();
	void DeleteCheck();
	void MagicChange();
	void Magic();

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

		CVector3 addpos = m_look_pos;
		addpos.Scale(m_scale);

		retpos.Add(addpos);

		return retpos;
	}

	float GetRadius()
	{
		return m_radius;
	}

	void SetHP(int hp)
	{
		m_hp = hp;
	}

	int GetHP()
	{
		return m_hp;
	}

	CVector3 GetScale()
	{
		return m_scale;
	}

	void SetDamage(int damage, MagicNo magic)
	{
		if (damage <= 0)
		{
			return;
		}
		
		if (magic < MAGICNUM)
		{
			m_StatusAilment.Execute(StatusAilment::AttackStat::AS_OTHER, magic);
		}

		m_hp -= damage;
		if (m_hp < 0)
		{
			m_hp = 0;
		}		
	}

	int GetMaxHP()
	{
		return m_maxhp;
	}

	void SetMP(int mp)
	{
		m_mp = mp;
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

	StatusAilment GetStatusAilment()
	{
		return m_StatusAilment;
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


	int GetMagicNo()
	{
		return m_magicNo;
	}
private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelDataHandle	m_skinModelData;				//スキンモデルデータハンドル。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CVector3				m_look_pos;						//カメラの注視点
	CVector3				m_scale;
	CQuaternion				m_rotation;						//回転。
	float					m_angle;						//角度。

	float					m_radius;

	bool					m_dead;

	CAnimation				m_animation;						//アニメーション。
	AnimationStat			m_animationStat;

	StatusAilment			m_StatusAilment;

	int						m_hp;
	int						m_maxhp;
	const float				m_hp_charge_delta = 0.5f * DELTA_TIME;
	float					m_hp_charge;

	int						m_mp;
	int						m_maxmp;
	const float				m_mp_charge_delta = 991.5f * DELTA_TIME;
	float					m_mp_charge;

	CParticleEmitter		*m_particle;
	float					m_particletimer;

	CParticleEmitter		*m_particle_charge;
	float					m_particletimer_charge;

	float					m_damagetimer_ABSORPTION_enemy;
	float					m_damagetimer_ABSORPTION;
	float					m_damagetimer_BLEEDING;
	float					m_damagetimer_POISON;
	float					m_damagetimer_IGNITION;

	CRandom					m_random;
	int						m_magicNo;
	bool					m_ismagic;
	bool					m_moveflg;

	int						m_magic_mp[MAGICNUM] = { 10,20,30,40,50 };

};