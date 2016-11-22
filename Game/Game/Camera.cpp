#include "stdafx.h"
#include "Camera.h"

Camera* g_gameCamera;

Camera::Camera()
{ 
	m_position = DEF_POS;
	m_angle = 0.0f;
}

Camera::~Camera()
{
}

void Camera::Start()
{
	//éŒÇﬂè„Ç©ÇÁå©â∫ÇÎÇ∑ä¥Ç∂ÇÃÉJÉÅÉâÇ…Ç∑ÇÈ
	m_camera.SetPosition(m_position);
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
}

void Camera::Update()
{
	CVector3 pos = m_position;
	pos.y = 0.0f;
	float len = pos.Length();

	m_position.x = len * cos(m_angle + ADD_ANGLE);
	m_position.z = len * sin(m_angle + ADD_ANGLE);
	m_angle += ADD_ANGLE * DELTA_TIME;

	m_camera.SetPosition(m_position);
	m_camera.Update();
}