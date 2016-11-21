#pragma once
class Camera : public IGameObject
{
public:

	Camera();
	~Camera();
	void Start();
	void Update();
	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}

private:
	CCamera		m_camera;	//カメラ。
	CVector3	m_position; //座標。
};

extern Camera* g_gameCamera;

