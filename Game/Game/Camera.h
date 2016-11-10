#pragma once
class Camera : public IGameObject
{
public:
	//ここからメンバ関数。
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
	//ここからメンバ変数。
	CCamera camera;	//カメラ。
};

extern Camera* g_gameCamera;

