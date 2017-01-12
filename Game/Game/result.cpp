#include "stdafx.h"
#include "result.h"

SC_result::SC_result()
{
}


SC_result::~SC_result()
{
}

void SC_result::Start()
{
	//îwåi
	m_back_tex.Load("Assets/Sprite/White.png");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	m_result_tex.LoadEx("Assets/Sprite/Loading-A.png", 0);
	m_result.Init(&m_result_tex);
	m_result.SetSize(RESULTMAXSIZE);
	m_result.SetPivot({ 0.5f,0.5f });
	m_result.SetPosition(RESULTPOS);

}

void SC_result::Update()
{

}

void SC_result::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_result.Draw(renderContext);
}

void SC_result::Delete()
{
	DeleteGO(this);
}