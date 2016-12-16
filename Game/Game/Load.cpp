#include "stdafx.h"
#include "Load.h"

namespace {
}

SC_Load::SC_Load()
{
}


SC_Load::~SC_Load()
{
}

void SC_Load::Start()
{
	m_load_tex.Load("Assets/Sprite/Loading-1.png");

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
	m_load.Draw(renderContext);
}

void SC_Load::Delete()
{
	DeleteGO(this);
}