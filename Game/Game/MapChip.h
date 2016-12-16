#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	MapChip();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~MapChip();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start(const char* modelName, CVector3 position, CQuaternion rotation, CVector3 scale);

	/*!
	* @brief	�X�V�B
	*/
	void Update();

	/*!
	* @brief	�`��B
	*/
	void Render(CRenderContext& renderContext);

	/*!
	* @brief	�폜�B
	*/
	void Delete();
private:
	CSkinModel				m_skinModel;		//�X�L�����f���B
	CSkinModelData			m_skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider			m_meshCollider;		//���b�V���R���C�_�[�B
	CRigidBody				m_rigidBody;		//���́B

	bool					m_dead;
};

