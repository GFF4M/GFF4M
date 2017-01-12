#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;
CRandom random;

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

	m_hp	= 100;
	m_maxhp = 100;
	m_mp	= 100;
	m_maxmp = 100;
	random.Init((unsigned int) + time(NULL));
	m_magicNo = 0;
	m_ismagic = false;
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
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}
	if (KeyInput().GetPad(0).IsTrigger(enButtonRB2))
	{
		m_magicNo++;
	}
	if (m_magicNo > WIND) {
		m_magicNo = FIER;
	}
	CVector3 m_oldpos;
	m_oldpos = m_position;

	//if (m_ismagic == true&&m_oldpos != m_position) {//魔法中移動などできないようにする

	//	m_position = m_oldpos;

	//}

	if (m_ismagic == false) {
		if (KeyInput().GetPad(0).IsTrigger(enButtonA))
		{

			m_animationStat = Animationmagic;
			m_animation.PlayAnimation(m_animationStat, 0.3f);
			m_ismagic = true;
		}
		
	}

		if (m_animation.IsPlay() == false &&m_ismagic==true){

			paticle();
			m_ismagic = false;
		}
	
	
	Move();

	m_animation.Update(2.0 / 60.0f);

	//ワールド行列の更新。
	m_skinModel.Update(m_position,m_rotation, m_scale);
	
}


void Player::Move()
{
	//キャラクターの移動速度を決定。
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 10.0f;
	move.z = -Pad(0).GetLStickYF() * 10.0f;

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//方向ベクトル
	moveXZ.y = 0.0f;

	float    LenXZ = moveXZ.Length();

	if (LenXZ > 0.0f)
	{
		if (m_animationStat != AnimationWalk&&m_ismagic == false)
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
		move.x = LenXZ * sin(CMath::DegToRad(m_angle));
		move.z = LenXZ * cos(CMath::DegToRad(m_angle));

		if (m_particle != nullptr)
		{
			DeleteGO(m_particle);//パーティクルの消去
			m_particle = nullptr;
		}
	}
	else
	{
		
		if (m_animationStat != AnimationStand&&m_ismagic==false)
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
	if (KeyInput().GetPad(0).IsPress(enButtonLB3) && m_characterController.IsOnGround())
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

void Player::paticle() {
	switch (m_magicNo) {
	case FIER:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度。
			0.8f,											//!<寿命。単位は秒。
			0.8f,											//!<発生時間。単位は秒。
			7.0f,											//!<パーティクルの幅。
			7.0f,											//!<パーティクルの高さ。
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
			m_position);
		break;
	case SUNDER:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/Sunder2.tga",				//!<テクスチャのファイwルパス。
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
			m_position);
		break;
	case ICE:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/ice.tga",//!<テクスチャのファイwルパス。
			{ 0.0f, 0.0f, 1.0f },								//!<初速度。
			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			4.0f,											//!<パーティクルの幅。
			4.0f,											//!<パーティクルの高さ。
			{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
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
			m_position);
		break;
	case AQUA:
			//パーティクルの生成
			m_particle = NewGO<CParticleEmitter>(0);
			m_particle->Init(random, g_gameCamera->GetCamera(),
			{
				"Assets/paticle/aqua.png",				//!<テクスチャのファイwルパス。
				{ 0.0f, 0.0f, 0.0f },								//!<初速度。
				0.4f,											//!<寿命。単位は秒。
				0.4f,											//!<発生時間。単位は秒。
				8.0f,											//!<パーティクルの幅。
				7.0f,											//!<パーティクルの高さ。
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
				m_position);
			break;
	case WIND:
		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<テクスチャのファイwルパス。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度。
			0.4f,											//!<寿命。単位は秒。
			0.4f,											//!<発生時間。単位は秒。
			4.0f,											//!<パーティクルの幅。
			4.0f,											//!<パーティクルの高さ。
			{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
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
		m_position);
		break;
	}
}
