#include "stdafx.h"
#include "MapChip.h"
#include "Camera.h"

MapChip::MapChip()
{
}


MapChip::~MapChip()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	m_skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	m_skinModel.Init(&m_skinModelData);
	//デフォルトライトを設定して。
	m_skinModel.SetLight(&g_defaultLight);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	m_skinModel.Update(position, rotation, CVector3::One);

	//メッシュコライダーの作成。
	m_meshCollider.CreateFromSkinModel(&m_skinModel, m_skinModelData.GetRootBoneWorldMatrix());

	//剛体の作成。
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = &m_meshCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	m_rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&m_rigidBody);
}
void MapChip::Update()
{
	//初期化の時に作成しているので何もしない。
}
void MapChip::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}