#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip : public IGameObject
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	MapChip();

	/*!
	* @brief	デストラクタ。
	*/
	~MapChip();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start(const char* modelName, CVector3 position, CQuaternion rotation, CVector3 scale);

	/*!
	* @brief	更新。
	*/
	void Update();

	/*!
	* @brief	描画。
	*/
	void Render(CRenderContext& renderContext);

	/*!
	* @brief	削除。
	*/
	void Delete();
private:
	CSkinModel				m_skinModel;		//スキンモデル。
	CSkinModelData			m_skinModelData;	//スキンモデルデータ。
	CMeshCollider			m_meshCollider;		//メッシュコライダー。
	CRigidBody				m_rigidBody;		//剛体。

	bool					m_dead;
};

