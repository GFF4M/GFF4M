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
private:
	CSkinModel			m_skinModel;		//�X�L�����f���B
	CSkinModelData		m_skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider		m_meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			m_rigidBody;		//���́B
};

