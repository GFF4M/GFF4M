#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Scene.h"

Enemy::Enemy()
{
	m_position = { 0.0f,0.0f,0.0f };
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.6f,0.6f,0.6f };
	m_radius = 0.5f;
	m_dead = false;

	m_filename = NULL;
	m_name = NULL;
	m_hp = 0;
	m_maxhp = 0;
	m_angle = 0.0f;
	m_attack_timer = 0.0f;

	m_characterController.Init(m_radius, 1.0f, m_position);

	m_random.Init((unsigned int)time(NULL));

	m_particle = nullptr;
}

Enemy::~Enemy()
{
}

void Enemy::Start(EneDat enedat, bool isBattle)
{
	m_filename = enedat.s_filename;
	m_name = enedat.s_name;
	m_hp = enedat.s_hp;
	m_maxhp = enedat.s_hp;
	m_position = enedat.s_pos;
	m_look_pos = enedat.s_look_pos;
	m_scale = enedat.s_scale;
	m_isBattle = isBattle;
	m_animationStat = AnimationStand;
	m_property = enedat.s_property;

	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", m_filename);

	SkinModelDataResources().Load(m_skinModelData, filePath, &m_animation);
	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。

	m_characterController.SetPosition(m_position);

	m_animation.SetAnimationLoopFlag(AnimationAttack, false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
	m_animation.SetAnimationLoopFlag(Animationmagic, false);
	m_animation.SetAnimationLoopFlag(AnimationDamage, false);
}

void Enemy::Update()
{
	if (m_particle != nullptr && m_particletimer <= 0.0f)
	{
		DeleteGO(m_particle);
		m_particle = nullptr;
	}

	if (m_particletimer > 0.0f)
	{
		m_particletimer -= 1.0f / 60.0f;
	}

	if (m_position.y < 0.0f)
	{
		m_hp = 0;
	}

	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}

	Move();
	m_skinModel.Update(m_position, m_rotation, m_scale);//ワールド行列の更新。
}

void Enemy::Move()
{
	CVector3 move = m_characterController.GetMoveSpeed();

	Player* player = g_scene->GetPlayer();

	if (m_isBattle && player != nullptr)
	{
		m_animation.Update(1.0 / 60.0f);

		CVector3 moveXZ = player->GetPos();
		moveXZ.Subtract(m_position);
		moveXZ.y = 0.0f;

		if (m_look_pos.y * m_scale.y / 1.25f < moveXZ.Length())
		{
			moveXZ.Normalize();
			moveXZ.Scale(2.0f);

			move.x = moveXZ.x;
			move.z = moveXZ.z;

			if (m_animationStat != AnimationWalk)
			{
				m_animationStat = AnimationWalk;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//アニメーションの再生
			}
		}
		else
		{
			m_attack_timer += DELTA_TIME;

			move.Scale({ 0.0f,1.0f,0.0f });
			
			if (2.0f < m_attack_timer)
			{
				m_attack_timer = 0.0f;
				m_animationStat = AnimationAttack;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//アニメーションの再生
				g_scene->GetPlayer()->SetDamage(100);
				Particle();
			}
			else if (m_animationStat != AnimationStand)
			{
				m_animationStat = AnimationStand;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//アニメーションの再生
			}
		}
		//AxisZとmoveXZのなす角を求める
		m_angle = moveXZ.AngleBetween(CVector3::AxisZ);

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}
	}

	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();


	m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
}

void Enemy::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext,g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}

void Enemy::Delete()
{
	m_dead = true;
}

void Enemy::Particle() {
	if (m_particle != nullptr)
	{
		return;
	}
	if (m_animationStat == NORMAL)
	{
		return;
	}

	CVector3 target = g_scene->GetPlayer()->GetLookPos();

	switch (m_property) {
	case FIRE:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度。
			0.8f,											//!<寿命。単位は秒。
			0.8f,											//!<発生時間。単位は秒。
			17.0f,											//!<パーティクルの幅。
			17.0f,											//!<パーティクルの高さ。
			{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
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
			{ 0.0f, 0.0f, 1.0f },								//!<初速度。
			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			10.0f,											//!<パーティクルの幅。
			10.0f,											//!<パーティクルの高さ。
			{ 1.0f, 1.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f, 0.5f, 0.5f },//0.25,0.5,0.75,1UとVの位置
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
		m_particletimer = 0.4f;
		break;
	case AQUA:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/aqua.png",				//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },								//!<初速度。
			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			10.0f,											//!<パーティクルの幅。
			10.0f,											//!<パーティクルの高さ。
			{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
			{

				{ 0.0f, 0.0f, 0.25f,0.25f },//0.25,0.5,0.75,1UとVの位置
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
		m_particletimer = 0.4f;
		break;
	case WIND:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<テクスチャのファイwルパス。
			{ 1.0f, 0.0f, 0.0f },							//!<初速度。

			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			10.0f,											//!<パーティクルの幅。
			10.0f,											//!<パーティクルの高さ。
			{ 1.0f, 1.0f, 0.0f },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
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
		m_particletimer = 0.4f;
		break;
	}
}
