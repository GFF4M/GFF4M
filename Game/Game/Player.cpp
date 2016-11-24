#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
}


Player::~Player()
{
}


void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Player.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
											
	m_characterController.Init(0.5f, 1.0f, m_position);//キャラクタコントローラの初期化。
}

void Player::Update()
{
	Move();
	//ワールド行列の更新。
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}

void Player::Move()
{
	//キャラクターの移動速度を決定。
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//回転させる
	CVector3 moveXZ = move;						//方向ベクトル
	moveXZ.y = 0.0f;

	//AxisZとmoveXZのなす角を求める
	if (moveXZ.Length() > 0.0f)
	{
		m_angle = moveXZ.Dot(CVector3::AxisZ);
		m_angle /= (moveXZ.Length() + 0.00001f);
		m_angle = acosf(m_angle);
		m_angle = m_angle * 180.0 / CMath::PI;

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}
	
		//カメラによる補正
		m_angle -= g_gameCamera->GetAngle();

		move.x = moveXZ.Length() * sin(CMath::DegToRad(m_angle));
		move.z = moveXZ.Length() * cos(CMath::DegToRad(m_angle));
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
	DeleteGO(this);
}
