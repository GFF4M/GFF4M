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
	skinModelData.LoadModelData("Assets/modelData/Player.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
											//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);
}

void Player::Update()
{
	//キャラクターの移動速度を決定。
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	//決定した移動速度をキャラクタコントローラーに設定。
	characterController.SetMoveSpeed(move);
	//キャラクターコントローラーを実行。
	characterController.Execute();
	//実行結果を受け取る。
	position = characterController.GetPosition();
	//ワールド行列の更新。
	skinModel.Update(position, CQuaternion::Identity, CVector3::One);
}
void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}
