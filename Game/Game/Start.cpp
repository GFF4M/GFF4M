#include "stdafx.h"
#include "Start.h"

SC_Start::SC_Start()
{
}


SC_Start::~SC_Start()
{
}

void SC_Start::Start()
{
	m_continue_tex.Load("Assets/Sprite/Continue-1.png");
	m_newgame_tex.Load("Assets/Sprite/New Game-2.png");
	m_title_tex.Load("Assets/Sprite/Title-1.png");

	m_continue.Init(&m_continue_tex);
	m_newgame.Init(&m_newgame_tex);
	m_title.Init(&m_title_tex);

	m_continue.SetSize(CONTINUEMAXSIZE);
	m_newgame.SetSize(NEWGAMEMAXSIZE);
	m_title.SetSize(TITLEMAXSIZE);


	m_continue.SetPivot({ 0.5f,0.5f });
	m_newgame.SetPivot({ 0.5f, 0.5f });
	m_title.SetPivot({ 0.5f,0.5f });

	m_continue.SetPosition(CONTINUEPOS);
	m_newgame.SetPosition(NEWGAMEPOS);
	m_title.SetPosition(TITLEPOS);

	/*soundSource.Init("Assets/modelData/bgm_maoudamashii_piano25.wav");
	soundSource.Play(true);*/
}

void SC_Start::Update()
{
	/*soundSource.Update();*/
}

void SC_Start::PostRender(CRenderContext& renderContext)
{
	m_continue.Draw(renderContext);
	m_newgame.Draw(renderContext);
	m_title.Draw(renderContext);
}

void SC_Start::Delete()
{
	DeleteGO(this);
}