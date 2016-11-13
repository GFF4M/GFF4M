#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CSkinModel				skinModel;					//スキンモデル。
	CSkinModelData			skinModelData;				//スキンモデルデータ。
	CCharacterController	characterController;		//キャラクタ―コントローラー。
	CVector3				position = CVector3::Zero;	//座標。
};

