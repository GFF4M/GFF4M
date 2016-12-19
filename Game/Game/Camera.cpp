#include "stdafx.h"
#include "Camera.h"
#include "Scene.h"
#include "Player.h"

Camera* g_gameCamera;

Camera::Camera()
{ 
	//èâä˙âª
	m_position = { 0.0f,2.5f,0.0f };
	m_look_position = CVector3::Zero;
	m_scale = 1.0f;
	m_angle = { 0.0f,45.0f };

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
	CVector3	add_angle;
	add_angle.x = -Pad(0).GetRStickXF() * ADD_ANGLE * DELTA_TIME;
	add_angle.y = -Pad(0).GetRStickYF() * ADD_ANGLE * DELTA_TIME;
	
	//âÒì]å„ÇÃç¿ïWÇãÅÇﬂÇÈ
	CVector3	angle_pos = m_position;
	angle_pos.x = DIST * sin(-CMath::DegToRad(m_angle.x + add_angle.x));
	angle_pos.y = DIST * sin(CMath::DegToRad(m_angle.y + add_angle.y));
	angle_pos.z = DIST * cos(-CMath::DegToRad(m_angle.x + add_angle.x));

	m_position = angle_pos;

	m_angle.x += add_angle.x;
	m_angle.y += add_angle.y;

	//äpìxÇÃê≥ãKâª
	if (m_angle.x < -180.0f)
	{
		m_angle.x += 360.0f;
	}
	else if (180.0f < m_angle.x)
	{
		m_angle.x -= 360.0f;
	}
	if (m_angle.y < -30.0f)
	{
		m_angle.y = -30.0f;
	}
	else if (60.0f < m_angle.y)
	{
		m_angle.y = 60.0f;
	}

	//íçéãì_ÇÃïœçX
	CVector3 camera_pos = CVector3::Zero;
	if (g_play == nullptr)

	{
		SetTarget(NOTARGET);
	}

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
