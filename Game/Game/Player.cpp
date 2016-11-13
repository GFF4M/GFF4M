#include "stdafx.h"
#include "Player.h"
#include "Camera.h"


Player::Player()
{
}


Player::~Player()
{
}


void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Player.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
											//キャラクタコントローラの初期化。
	m_characterController.Init(0.5f, 1.0f, m_position);
}

void Player::Update()
{
	//キャラクターの移動速度を決定。
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
	m_characterController.Execute();
	//実行結果を受け取る。
	m_position = m_characterController.GetPosition();
	//ワールド行列の更新。
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
}
void Player::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}
