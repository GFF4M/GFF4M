#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	MapChip();
	~MapChip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation, CVector3 scale);
	void Update();
	void Render(CRenderContext& renderContext);
private:
	CSkinModel				m_skinModel;		//スキンモデル。
	CSkinModelData			m_skinModelData;	//スキンモデルデータ。
	CMeshCollider			m_meshCollider;		//メッシュコライダー。
	CRigidBody				m_rigidBody;		//剛体。
};

