#include "stdafx.h"
#include "Result.h"
#include "Scene.h"

SC_Result::SC_Result()
{
}


SC_Result::~SC_Result()
{
}

void SC_Result::Start()
{
	//”wŒi
	m_back_tex.Load("Assets/Sprite/White.png");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	m_Result_tex.LoadEx("Assets/Sprite/completed.png", 0);
	m_Result.Init(&m_Result_tex);
	m_Result.SetSize(RESULTMAXSIZE);
	m_Result.SetPivot({ 0.5f,0.5f });
	m_Result.SetPosition(RESULTPOS);

}

void SC_Result::Update()
{
	if (Pad(0).IsTrigger(enButtonA))
	{
		g_scene->Change(START);
	}
}

void SC_Result::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_Result.Draw(renderContext);
}

void SC_Result::Delete()
{
	DeleteGO(this);
}