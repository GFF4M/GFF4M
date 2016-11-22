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

	float GetAngle()
	{
		return m_angle;
	}

private:
	CCamera					m_camera;	//カメラ。
	CVector3				m_position; //座標。
	const	CVector3		DEF_POS = { 0.0f,2.0f,5.0f };
	float					m_angle;
	const	float			ADD_ANGLE = 0.05f;
	const	float			DELTA_TIME = 1.0f / 60.0f;
};

extern Camera* g_gameCamera;

