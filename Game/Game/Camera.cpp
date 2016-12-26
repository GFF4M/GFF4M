#include "stdafx.h"
#include "Camera.h"
#include "Scene.h"
#include "Player.h"

Camera* g_gameCamera;

Camera::Camera()
{ 
	//初期化
	m_position = { 0.0f,2.5f,0.0f };
	m_look_position = CVector3::Zero;
	m_scale = 3.0f;
	m_angle = { 0.0f,45.0f };

	m_target = CT_NOTARGET;

	m_rotation = true;
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
	if (Pad(0).IsTrigger(enButtonRB3))
	{
		m_rotation = !m_rotation;
	}

	if (m_rotation)
	{
		Rotation();
	}
	else
	{
		Zoom();
	}

	CameraPos();

	m_camera.Update();
}

void Camera::CameraPos()
{
	//カメラ座標を求める
	CVector3	angle_pos = CVector3::Zero;
	angle_pos.x = sin(-CMath::DegToRad(m_angle.x));
	angle_pos.y = sin(CMath::DegToRad(m_angle.y));
	angle_pos.z = cos(-CMath::DegToRad(m_angle.x));
	angle_pos.Scale(m_scale);
	m_position = angle_pos;

	//注視点の変更
	CVector3 camera_pos = CVector3::Zero;
	if (g_scene->GetPlayer() == nullptr)
	{
		SetTarget(CT_NOTARGET);
	}

	switch (m_target)
	{
	case CT_NOTARGET:
		m_look_position = CVector3::Zero;
		break;
	case CT_PLAYER:
		camera_pos = g_scene->GetPlayer()->GetLookPos();
		camera_pos.Add(m_position);
		m_look_position = g_scene->GetPlayer()->GetLookPos();
		break;
	case CT_ENEMY:
		camera_pos = g_scene->GetPlayer()->GetLookPos();
		camera_pos.Add(m_position);
		m_look_position = g_scene->GetPlayer()->GetLookPos();
		break;
	default:
		break;
	}

	camera_pos.Add(m_position);
	m_camera.SetPosition(camera_pos);
	m_camera.SetTarget(m_look_position);

}

void Camera::Rotation()
{
	CVector3	add_angle;
	add_angle.x = -Pad(0).GetRStickXF() * ADD_ANGLE * DELTA_TIME;
	add_angle.y = -Pad(0).GetRStickYF() * ADD_ANGLE * DELTA_TIME;

	m_angle.x += add_angle.x;
	m_angle.y += add_angle.y;

	//角度の正規化
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
}

void Camera::Zoom()
{
	m_scale += -Pad(0).GetRStickYF() * ADD_SCALE * DELTA_TIME;

	//スケールの正規化
	if (m_scale < 0.5f)
	{
		m_scale = 0.5f;
	}
	else if (m_scale > 10.0f)
	{
		m_scale = 10.0f;
	}
}