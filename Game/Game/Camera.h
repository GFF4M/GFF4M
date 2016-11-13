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
	CCamera m_camera;	//�J�����B
};

extern Camera* g_gameCamera;

