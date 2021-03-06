#include "stdafx.h"
#include "Load.h"

SC_Load::SC_Load()
{
}


SC_Load::~SC_Load()
{
}

void SC_Load::Start()
{
	//�w�i
	m_back_tex.Load("Assets/Sprite/Black.png");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	m_load_tex.LoadEx("Assets/Sprite/Loading-1.png",0);
	m_load.Init(&m_load_tex);
	m_load.SetSize(LOADMAXSIZE);
	m_load.SetPivot({ 0.5f,0.5f });
	m_load.SetPosition(LOADPOS);

	
}

void SC_Load::Update()
{
	
}

void SC_Load::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_load.Draw(renderContext);
}

void SC_Load::Delete()
{
	DeleteGO(this);
}