#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "Scene.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = { 0.0f,0.0f,0.0f };
	m_look_pos = { 0.0f,2.0f,0.0f };
	m_scale = {0.7f,0.7f,0.7f };
	m_rotation = CQuaternion::Identity;
	m_animationStat = AnimationStand;
	m_radius = 0.5f;
	m_dead = false;

	m_characterController.Init(m_radius, 1.0f, m_position);//キャラクタコントローラの初期化。

	m_hp	= 5000;
	m_maxhp = 5000;
	m_hp_charge = 0.0f;

	m_mp	= 200;
	m_maxmp = 200;
	m_mp_charge = 0.0f;
	
	m_random.Init((unsigned int)time(NULL));
	m_magicNo = FIRE;
	m_ismagic = false;

	m_moveflg = false;

	m_particle = nullptr;

	m_particletimer = 0.0f;

	m_particle_charge = nullptr;

	m_particletimer_charge = 0.0f;
}

Player::~Player()
{
}

void Player::Start()
{
	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/kano.X", &m_animation);

	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。

	m_animation.SetAnimationLoopFlag(AnimationAttack, false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
	m_animation.SetAnimationLoopFlag(Animationmagic, false);
	m_animation.SetAnimationLoopFlag(AnimationDamage, false);
}

void Player::Update()
{
	DeadCheck();

	Charge();

	DeleteCheck();

	MagicChange();

	Magic();

	if (m_moveflg && !m_ismagic)
	{
		Move();
	}
	else if (m_moveflg && m_ismagic)
	{
		CVector3 move = m_characterController.GetMoveSpeed();
		move.Scale({ 0.0f,1.0f,0.0f });
		//決定した移動速度をキャラクタコントローラーに設定。
		m_characterController.SetMoveSpeed(move);
		//キャラクターコントローラーを実行。
		m_characterController.Execute();
		//実行結果を受け取る。
		m_position = m_characterController.GetPosition();

		m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
	}
	
	switch (m_animationStat)
	{
	case AnimationDamage:
		m_animation.Update(1.0f / 60.0f);
		break;
	default:
		m_animation.Update(2.0f / 60.0f);
		break;
	}
	//ワールド行列の更新。
	m_skinModel.Update(m_position,m_rotation, m_scale);

	if (m_particle != nullptr && m_particletimer <= 0.0f)
	{
		DeleteGO(m_particle);
		m_particle = nullptr;
	}

	if (m_particletimer > 0.0f)
	{
		m_particletimer -= 1.0f / 60.0f;
	}

	if (m_particle_charge != nullptr && m_particletimer_charge <= 0.0f)
	{
		DeleteGO(m_particle_charge);
		m_particle_charge = nullptr;
	}

	if (m_particletimer_charge > 0.0f)
	{
		m_particletimer_charge -= 1.0f / 60.0f;
	}
}

void Player::Move()
{
	//キャラクターの移動速度を決定。
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF();
	move.z = -Pad(0).GetLStickYF();

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//方向ベクトル
	moveXZ.y = 0.0f;

	if (moveXZ.Length() > 0.0f)
	{
		if (m_animationStat != AnimationWalk)
		{
			m_animationStat = AnimationWalk;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//アニメーションの再生
		}

		//AxisZとmoveXZのなす角を求める
		m_angle = moveXZ.AngleBetween(CVector3::AxisZ);

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}

		//カメラによる補正
		m_angle -= g_gameCamera->GetAngle().x;

		//回転した方向に移動
		move.x = sin(CMath::DegToRad(m_angle)) * 1000.0f * DELTA_TIME;
		move.z = cos(CMath::DegToRad(m_angle)) * 1000.0f * DELTA_TIME;
	}
	else
	{
		if (m_animationStat != AnimationStand && !m_ismagic)
		{
			m_animationStat = AnimationStand2;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//アニメーションの再生
			
		}
	}
	
	//角度の正規化
	if (m_angle < -180.0f)
	{
		m_angle += 360.0f;
	}
	else if (180.0f < m_angle)
	{
		m_angle -= 360.0f;
	}

	//一段ジャンプ
	if (KeyInput().GetPad(0).IsPress(enButtonA) && m_characterController.IsOnGround())
	{
		m_characterController.Jump();
		move.y = 8.0f;
		
	}

	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
	m_characterController.Execute();
	//実行結果を受け取る。
	m_position = m_characterController.GetPosition();

	m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
}

void Player::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Player::Delete()
{
	m_dead = true;
}

void Player::Particle() {
	if (m_particle != nullptr)
	{
		return;
	}

	CVector3 target = g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->GetPos();

	target.y = GetLookPos().y;

	switch (m_magicNo) {
	case FIRE:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度。
			0.8f,											//!<寿命。単位は秒。
			0.01f,											//!<発生時間。単位は秒。
			17.0f,											//!<パーティクルの幅。
			17.0f,											//!<パーティクルの高さ。
			{ 3.0f, 3.0f, 3.0f },							//!<初期位置のランダム幅。
			{ 1.0f, 1.0f, 1.0f },							//!<初速度のランダム幅。
			{ 1.0f, 1.0f, 1.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f,0.25f, 0.25f },//0.25,0.5,0.75,1UとVの位置
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, 0.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);
		m_particletimer = 0.8f;
		break;
	case THUNDER:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/Thunder2.tga",				//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },								//!<初速度。

			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			10.0f,											//!<パーティクルの幅。
			10.0f,											//!<パーティクルの高さ。
			{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f, 1.0f, 0.5f },//0.25,0.5,0.75,1UとVの位置
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, 0.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);
		m_particletimer = 0.4f;
		break;
	case ICE:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/ice.tga",//!<テクスチャのファイルパス。
			{ 0.0f, 5.0f, 0.0f },								//!<初速度。
			0.4f,											//!<寿命。単位は秒。
			0.1f,											//!<発生時間。単位は秒。
			10.0f * (1.0f - (float)m_random.GetRandDouble() / 2.0f),											//!<パーティクルの幅。
			10.0f * (1.0f - (float)m_random.GetRandDouble() / 2.0f),											//!<パーティクルの高さ。
			{ 5.0f, 6.0f, 5.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 2.0f, 0.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f, 0.5f, 0.5f },//0.25,0.5,0.75,1UとVの位置
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, -2.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);
		m_particletimer = 0.4f;
		break;
	case AQUA:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/aqua.png",				//!<テクスチャのファイルパス。
			{ 0.0f, 20.0f, 0.0f },								//!<初速度。
			2.0f,											//!<寿命。単位は秒。
			0.01f,											//!<発生時間。単位は秒。
			2.0f + ((float)m_random.GetRandDouble() - 0.5f),											//!<パーティクルの幅。
			2.0f + ((float)m_random.GetRandDouble() - 0.5f),											//!<パーティクルの高さ。
			{ 0.0f, 5.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 5.0f, 0.0f, 5.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{

				{ 0.0f, 0.0f, 0.25f,0.25f },//0.25,0.5,0.75,1UとVの位置
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, -20.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);
		m_particletimer = 2.0f;
		break;
	case WIND:
		m_random.GetRandDouble();
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<テクスチャのファイwルパス。
			{ 10.0f, 0.0f, 0.0f },							//!<初速度。

			0.5f,											//!<寿命。単位は秒。
			0.2f,											//!<発生時間。単位は秒。
			10.0f * ((float)m_random.GetRandDouble() + 0.5f),											//!<パーティクルの幅。
			10.0f * ((float)m_random.GetRandDouble() + 0.5f),											//!<パーティクルの高さ。
			{ 5.0f, 3.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 3.0f, 5.0f, 1.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f, 1.0f, 1.0f },//0.25,0.5,0.75,1UとVの位置
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, 0.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);
		m_particletimer = .5f;
		break;
	}
}

void Player::DeadCheck()
{
	if (m_hp <= 0)
	{
		g_scene->Change(GAMEOVER);
	}
}

void Player::Charge()
{
	if (m_mp < m_maxmp)
	{
		m_mp_charge += m_mp_charge_delta;
		if (m_mp_charge >= 1.0f)
		{
			m_mp_charge = 0.0f;
			m_mp++;
		}
	}

	if (m_hp < m_maxhp)
	{
		m_hp_charge += m_hp_charge_delta;
		if (m_hp_charge >= 1.0f)
		{
			m_hp_charge = 0.0f;
			m_hp++;
		}
	}
}

void Player::DeleteCheck()
{
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}
}

void Player::MagicChange()
{
	if (Pad(0).IsTrigger(enButtonRB1))
	{
		m_magicNo++;
		if (WIND < m_magicNo) {
			m_magicNo = FIRE;
		}
		g_scene->GetMagic()->Change();
	}

	if (Pad(0).IsTrigger(enButtonLB1))
	{
		m_magicNo--;
		if (m_magicNo < FIRE) {
			m_magicNo = WIND;
		}

		g_scene->GetMagic()->Change();
	}
}

void Player::Magic()
{
	switch (g_scene->GetScenes())
	{
	case STAGE_T_BATTLE:
	case STAGE_1_BATTLE:
	case STAGE_2_BATTLE:
	case STAGE_3_BATTLE:
	case STAGE_4_BATTLE:
	case STAGE_5_BATTLE:
	{
		CVector3 dist = g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->GetLookPos();
		dist.Subtract(m_position);
		dist.y = 0.0f;

		CVector3 angle_pos;
		angle_pos.x = sin(CMath::DegToRad(m_angle));
		angle_pos.y = 0.0f;
		angle_pos.z = cos(CMath::DegToRad(m_angle));

		if (m_magic_mp[m_magicNo] <= m_mp)
		{
			if (dist.AngleBetween(angle_pos) < 30.0f)
			{
				if (!m_ismagic)
				{
					if (m_particle_charge == nullptr && m_particle == nullptr)
					{
						if (KeyInput().GetPad(0).IsTrigger(enButtonB))
						{
							m_animationStat = Animationmagic;
							m_animation.PlayAnimation(m_animationStat, 0.3f);
							m_ismagic = true;

							//パーティクルの生成
							m_particle_charge = NewGO<CParticleEmitter>(0);
							m_particle_charge->Init(m_random, g_gameCamera->GetCamera(),
							{
								"Assets/paticle/fx_Magiccircle_j.png",			//!<テクスチャのファイwルパス。
								{ 1.0f, 0.0f, 0.0f },							//!<初速度。
								0.7f,											//!<寿命。単位は秒。
								0.7f,											//!<発生時間。単位は秒。
								6.0f,											//!<パーティクルの幅。
								7.0f,											//!<パーティクルの高さ。
								{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
								{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
								{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
								{
									{ 0.0f, 0.0f, 0.25f,0.5f },//0.25,0.5,0.75,1UとVの位置
									{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
									{ 0.0f, 0.0f, 0.0f, 0.0f },
									{ 0.0f, 0.0f, 0.0f, 0.0f }
								},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
								1,												//!<UVテーブルのサイズ。
								{ 0.0f, 0.0f, 0.0f },							//!<重力。
								true,											//!<死ぬときにフェードアウトする？
								0.3f,											//!<フェードする時間。
								2.0f,											//!<初期アルファ値。
								true,											//!<ビルボード？
								3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
								0,												//!<0半透明合成、1加算合成。
								{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
							},
								GetLookPos());
							m_particletimer_charge = 0.7f;
						}
					}
				}
				if (!m_animation.IsPlay() && m_ismagic)
				{
					m_mp -= m_magic_mp[m_magicNo];
					Particle();
					g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->SetDamage(m_magic_mp[m_magicNo]);
					m_ismagic = false;
				}
			}
		}
	}
	break;
	default:
		break;
	}

}