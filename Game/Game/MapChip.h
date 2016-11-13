#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();
private:
	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelData		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。
};

