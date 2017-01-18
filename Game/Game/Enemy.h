#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "StatusAilment.h"

class Enemy : public IGameObject
{
public:
	struct EneDat
	{
		Scenes			s_scene;		//発生場所
		char*			s_filename;		//ファイル名
		char*			s_name;			//名前
		int				s_hp;			//HP
		CVector3		s_pos;			//基本初期座標
		CVector3		s_look_pos;		//注視点
		CVector3		s_scale;		//スケール
		MagicNo			s_property;		//属性
	};

	/*!
	* @brief	コンストラクタ。
	*/
	Enemy();

	/*!
	* @brief	デストラクタ。
	*/
	~Enemy();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start(EneDat enedat, bool isBattle);

	/*!
	* @brief	更新。
	*/
	void Update();

	/*!
	* @brief	描画。
	*/
	void Render(CRenderContext& renderContext);

	/*!
	* @brief	削除。
	*/
	void Delete();

	/*!
	* @brief	移動。
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

		if (m_StatusAilment.GetStatusAilment(StatusAilment::SA_Eng::SA_IGNITION) > 0.0f ||
			m_StatusAilment.GetStatusAilment(StatusAilment::SA_Eng::SA_FROZEN) > 0.0f || 
			m_StatusAilment.GetStatusAilment(StatusAilment::SA_Eng::SA_BLEEDING) > 0.0f)
		{
			damage *= 1.5f;
		}

		switch (m_magicNo)
		{
		case FIRE:
			if (magic == AQUA)
			{
				damage *= 1.5f;
			}
			else if (magic == ICE)
			{
				damage *= 0.5f;
			}
			break;
		case WIND:
			if (magic == THUNDER)
			{
				damage *= 1.5f;
			}
			else if (magic == ICE)
			{
				damage *= 0.5f;
			}
			break;
		case THUNDER:
			if (magic == WIND)
			{
				damage *= 1.5f;
			}
			else if (magic == AQUA)
			{
				damage *= 0.5f;
			}
			break;
		case ICE:
			if (magic == FIRE)
			{
				damage *= 1.5f;
			}
			else if (magic == THUNDER)
			{
				damage *= 0.5f;
			}
			break;
		case AQUA:
			if (magic == THUNDER)
			{
				damage *= 1.5f;
			}
			else if (magic == FIRE)
			{
				damage *= 0.5f;
			}
			break;
		default:
			break;
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

	int GetMaxHP()
	{
		return m_maxhp;
	}

	CVector3 GetScale()
	{
		return m_scale;
	}

	StatusAilment GetStatusAilment()
	{
		return m_StatusAilment;
	}

	enum AnimationStat
	{
		AnimationAttack,
		AnimationWalk,
		AnimationStand
	};
private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelDataHandle	m_skinModelData;				//スキンモデルデータ。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CVector3				m_look_pos;						//注視点。
	CQuaternion				m_rotation;						//回転。
	CVector3				m_scale;						//拡大。
	float					m_angle;						//角度。

	StatusAilment			m_StatusAilment;

	MagicNo					m_property;						//属性
	float					m_radius;

	bool					m_dead;

	char*					m_filename;
	char*					m_name;
	int						m_hp;
	int						m_maxhp;

	CRandom					m_random;
	bool					m_isBattle;

	CAnimation				m_animation;						//アニメーション。
	AnimationStat			m_animationStat;

	float					m_attack_timer;

	CParticleEmitter		*m_particle;
	float					m_particletimer;

	float					m_damagetimer_ABSORPTION_player;
	float					m_damagetimer_ABSORPTION;
	float					m_damagetimer_BLEEDING;
	float					m_damagetimer_POISON;
	float					m_damagetimer_IGNITION;

	int						m_magicNo;
};
