#pragma once
#include "tkEngine/character/tkCharacterController.h"
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
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelDataHandle	m_skinModelData;				//スキンモデルデータ。
	CCharacterController	m_characterController;			//キャラクタ―コントローラー。
	CVector3				m_position;						//座標。
	CVector3				m_look_pos;						//注視点。
	CQuaternion				m_rotation;						//回転。
	CVector3				m_scale;						//拡大。
	float					m_angle;						//角度。

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

	int						m_magicNo;
};
