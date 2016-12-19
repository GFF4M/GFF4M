#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Camera : public IGameObject
{
public:
	enum Target
	{
		NOTARGET,
		PLAYER,
	};

	Camera();
	~Camera();
	void Start();
	void Update();
	void CameraPos();

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

	void SetTarget(Target target)
	{
		m_target = target;
	}

private:
	CCamera					m_camera;	//カメラ。
	CVector3				m_position; //座標。
	float					m_scale;
	
	CVector3				m_look_position;
	const	float			DIST = 10.0f;

	CVector2				m_angle;
	const	float			ADD_ANGLE = 360.0f / 4.5f;
	
	const	float			DELTA_TIME = 1.0f / 60.0f;
	
	Target					m_target;
};

extern Camera* g_gameCamera;

