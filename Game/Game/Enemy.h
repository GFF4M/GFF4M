#pragma once
class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Start();
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();
	void Move();
private:
	CSkinModel				m_skinModel;					//スキンモデル。
	CSkinModelData			m_skinModelData;				//スキンモデルデータ。
	CVector3				m_position;						//座標。
	CQuaternion				m_rotation;						//回転。
	CVector3				m_scale;						//拡大w
};

