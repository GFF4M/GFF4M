#include "stdafx.h"
#include "Camera.h"
#include "Scene.h"
#include "Player.h"

Camera* g_gameCamera;

Camera::Camera()
{ 
	//èâä˙âª
	m_position = DEF_POS;
	m_look_position = CVector3::Zero;
	m_scale = 1.0f;
	m_angle = 0.0f;

	m_target = NOTARGET;
}

Camera::~Camera()
{
}

void Camera::Start()
{
	m_camera.SetPosition(m_position);
	m_camera.SetTarget(m_look_position);
	m_camera.SetUp(CVector3::AxisY);
}

void Camera::Update()
{
	CameraPos();

	m_camera.Update();
}

void Camera::CameraPos()
{
	CVector3 posXZ = m_position;
	CVector3 posYZ = m_position;
	posXZ.y = 0.0f;
	posYZ.x = 0.0f;

	float lenXZ = posXZ.Length();
	
	float	add_angle;
	add_angle = -Pad(0).GetRStickXF() * ADD_ANGLE * DELTA_TIME;
	
	//âÒì]å„ÇÃç¿ïWÇãÅÇﬂÇÈ
	CVector3	angle_pos = m_position;
	angle_pos.x = lenXZ * sin(-CMath::DegToRad(m_angle + add_angle));
	angle_pos.z = lenXZ * cos(-CMath::DegToRad(m_angle + add_angle));

	m_position = angle_pos;

	m_angle += add_angle;

	//äpìxÇÃê≥ãKâª
	if (m_angle < -180.0f)
	{
		m_angle += 360.0f;
	}
	else if (180.0f < m_angle)
	{
		m_angle -= 360.0f;
	}

	//íçéãì_ÇÃïœçX
	CVector3 camera_pos = CVector3::Zero;
	switch (m_target)
	{
	case NOTARGET:
		m_look_position = CVector3::Zero;
		break;
	case PLAYER:
		camera_pos = g_play->GetPos();
		m_look_position = g_play->GetPos();
		break;
	default:
		break;
	}

	camera_pos.Add(m_position);
	m_camera.SetPosition(camera_pos);
	m_camera.SetTarget(m_look_position);

}
