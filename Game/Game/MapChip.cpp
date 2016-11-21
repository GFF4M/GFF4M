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
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	m_skinModelData.LoadModelData(filePath, NULL);
	//CSkinModel���������B
	m_skinModel.Init(&m_skinModelData);
	//�f�t�H���g���C�g��ݒ肵�āB
	m_skinModel.SetLight(&g_defaultLight);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	m_skinModel.Update(position, rotation, CVector3::One);

	//���b�V���R���C�_�[�̍쐬�B
	m_meshCollider.CreateFromSkinModel(&m_skinModel, m_skinModelData.GetRootBoneWorldMatrix());

	//���̂̍쐬�B
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &m_meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	m_rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&m_rigidBody);
}
void MapChip::Update()
{
	//�������̎��ɍ쐬���Ă���̂ŉ������Ȃ��B
}
void MapChip::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}