#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = /*CVector3::Zero*/{ 0.0f,15.0f,0.0f };
	m_rotation = CQuaternion::Identity;
	m_animationStat = AnimationStand;
	m_characterController.Init(0.5f, 1.0f, m_position);//キャラクタコントローラの初期化。
}

Player::~Player()
{
}

void Player::Start()
{

	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/kanoDash2.X", &m_animation);

	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//デフォルトライトを設定。

	m_animation.SetAnimationLoopFlag(AnimationAttack,false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
}

void Player::Update()
{

	if (Pad(0).IsTrigger(enButtonA))
	{
		m_animation.PlayAnimation(AnimationAttack,0.3f);
	}

	Move();

	m_animation.Update(2.0 / 60.0f);

	//ワールド行列の更新。
	m_skinModel.Update(m_position,m_rotation, CVector3::One);

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
		m_angle -= g_gameCamera->GetAngle();

		//回転した方向に移動
		move.x = LenXZ * sin(CMath::DegToRad(m_angle));
		move.z = LenXZ * cos(CMath::DegToRad(m_angle));
	}
	else
	{
		if (m_animationStat != AnimationStand)
		{
			m_animationStat = AnimationStand;
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
	m_characterController.RemoveRigidBoby();
	DeleteGO(this);
}
