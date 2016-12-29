#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Camera : public IGameObject
{
public:

	Camera();
	~Camera();
	void Start();
	void Update();
	void CameraPos();
	void Rotation();
	void Zoom();


	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}

	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}

	const CVector2 GetAngle()
	{
		return m_angle;
	}

	CVector3 GetPos()
	{
		return m_position;
	}

	CVector3 GetLookPos()
	{
		return m_look_position;
	}

	void SetTarget(CameraTarget target)
	{
		m_target = target;
	}
	CCamera& GetCamera()
	{
		return m_camera;
	}

private:
	CCamera					m_camera;	//カメラ。
	CVector3				m_position; //座標。
	
	CVector3				m_look_position;
	const	float			DIST = 10.0f;

	CVector2				m_angle;
	const	float			ADD_ANGLE = 360.0f / 4.5f;

	float					m_scale;
	const	float			ADD_SCALE = 5.0f;
	
	const	float			DELTA_TIME = 1.0f / 60.0f;
	
	CameraTarget			m_target;

	bool					m_rotation;
};

extern Camera* g_gameCamera;

