#include "stdafx.h"
#include "MapChip.h"
#include "Camera.h"

MapChip::MapChip()
{
}


MapChip::~MapChip()
{
}
void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(&skinModelData);
	//デフォルトライトを設定して。
	skinModel.SetLight(&g_defaultLight);
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	skinModel.Update(position, rotation, CVector3::One);
}
void MapChip::Update()
{
	//初期化の時に作成しているので何もしない。
}
void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}