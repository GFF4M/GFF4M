#include "stdafx.h"
#include "Load.h"

namespace {
	const CVector2 backPos = { 0.0f, 0.0f };
	const CVector2 backMaxSize = { 1500.0f, 1000.0f };
	const CVector2 loadMaxSize = { 230.0f, 80.0f };
	const CVector2 loadPos = { 0.0f, -100.0f };
}

SC_Load::SC_Load()
{
}


SC_Load::~SC_Load()
{
}

void SC_Load::Start()
{

	m_back_tex.Load("Assets/Sprite/Black-1.png");
	m_load_tex.Load("Assets/Sprite/Loading-1.png");

	m_back.Init(&m_back_tex);
	m_load.Init(&m_load_tex);


	m_back.SetSize(backMaxSize);
	m_load.SetSize(loadMaxSize);


	m_back.SetPivot({ 0.5f, 0.5f });
	m_load.SetPivot({ 0.5f,0.5f });

	m_back.SetPosition(backPos);
	m_load.SetPosition(loadPos);

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