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
		return camera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}

private:
	CCamera camera;	//�J�����B
};

extern Camera* g_gameCamera;

