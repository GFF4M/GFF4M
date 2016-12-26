#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;
CRandom random;
Player::Player()
{
	m_angle = 0.0f;
	m_position = { 0.0f,1.0f,0.0f };
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
}

Player::~Player()
{
}

void Player::Start()
{
	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/golem.X", &m_animation);

	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。

	m_animation.SetAnimationLoopFlag(AnimationAttack,false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
}

void Player::Update()
{
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}

	

		//CParticleEmitter *particle;
		//particle = NewGO<CParticleEmitter>(0);
		//particle->Init(random, g_gameCamera->GetCamera(),
		//{
		//	"Assets/modelData/realExplosion.png",				//!<テクスチャのファイルパス。
		//	{ 0.0f, 0.0f, 0.0f },								//!<初速度。
		//	1.5f,											//!<寿命。単位は秒。
		//	1.0f,											//!<発生時間。単位は秒。
		//	5.0f,											//!<パーティクルの幅。
		//	5.0f,											//!<パーティクルの高さ。
		//	{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
		//	{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
		//	{ 0.0f, 0.0f, 0.0f },							//!<速度の積分のときのランダム幅。
		//	{
		//		{ 0.0f, 0.0f, 0.33f, 0.33f },
		//		{ 0.0f, 0.0f, 0.0f, 0.0f },
		//		{ 0.0f, 0.0f, 0.0f, 0.0f },
		//		{ 0.0f, 0.0f, 0.0f, 0.0f }
		//	},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		//	1,												//!<UVテーブルのサイズ。
		//	{ 0.0f, 0.0f, 0.0f },							//!<重力。
		//	true,											//!<死ぬときにフェードアウトする？
		//	0.3f,											//!<フェードする時間。
		//	1.0f,											//!<初期アルファ値。
		//	true,											//!<ビルボード？
		//	0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		//	0,												//!<0半透明合成、1加算合成。
		//	{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		//},
		//	m_position);
	

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
		move.x = LenXZ * sin(CMath::DegToRad(m_angle));
		move.z = LenXZ * cos(CMath::DegToRad(m_angle));
	}
	else
	{
		if (m_animationStat != AnimationAttack)
		{
			m_animationStat = AnimationAttack;
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
	if (KeyInput().GetPad(0).IsPress(enButtonX) && m_characterController.IsOnGround())
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
