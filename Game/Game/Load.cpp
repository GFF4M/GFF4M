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
	//îwåi
	m_back_tex.Load("Assets/Sprite/White.png");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	m_load_tex.LoadEx("Assets/Sprite/Loading-A.png",0);
	m_load.Init(&m_load_tex);
	m_load.SetSize(LOADMAXSIZE);
	m_load.SetPivot({ 0.5f,0.5f });
	m_load.SetPosition(LOADPOS);

	/*soundSource.Init("Assets/modelData/bgm_maoudamashii_piano25.wav");
	soundSource.Play(true);*/
}

void SC_Load::Update()
{
	/*soundSource.Update();*/
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