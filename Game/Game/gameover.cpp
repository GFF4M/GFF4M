#include "stdafx.h"
#include "Gameover.h"


SC_Gameover::SC_Gameover()
{
}


SC_Gameover::~SC_Gameover()
{
}

void SC_Gameover::Start()
{
	//îwåi
	m_back_tex.Load("Assets/Sprite/White.png");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	m_Gameover_tex.LoadEx("Assets/Sprite/Game Over-2.png", 0);
	m_Gameover.Init(&m_Gameover_tex);
	m_Gameover.SetSize(GAMEOVERMAXSIZE);
	m_Gameover.SetPivot({ 0.5f,0.5f });
	m_Gameover.SetPosition(GAMEOVERPOS);

}

void SC_Gameover::Update()
{

}

void SC_Gameover::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_Gameover.Draw(renderContext);
}

void SC_Gameover::Delete()
{
	DeleteGO(this);
}