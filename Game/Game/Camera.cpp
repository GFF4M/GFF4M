#include "stdafx.h"
#include "Camera.h"

Camera* g_gameCamera;

Camera::Camera()
{ 
}


Camera::~Camera()
{
}
void Camera::Start()
{
	//�΂ߏォ�猩���낷�����̃J�����ɂ���
	m_camera.SetPosition({ 0.0f, 0.0f, 16.0f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
}
void Camera::Update()
{
	m_camera.Update();
}