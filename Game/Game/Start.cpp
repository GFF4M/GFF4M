#include "stdafx.h"
#include "Start.h"
#include "Scene.h"

SC_Start::SC_Start()
{
	m_tex_num = NEWGAME;
	m_UPressflag = false;
	m_DPressflag = false;
}


SC_Start::~SC_Start()
{
	DeleteGO(m_sound_choise);
}

void SC_Start::Start()
{
	//”wŒi
	m_back_tex.Load("Assets/Sprite/1.jpg");
	m_back.Init(&m_back_tex);
	m_back.SetSize(BACK_MAX_SIZE);
	m_back.SetPivot({ 0.5f,0.5f });
	m_back.SetPosition(BACK_POS);

	//ƒ^ƒCƒgƒ‹
	m_title_tex.LoadEx("Assets/Sprite/Title-A.png",0);
	m_title.Init(&m_title_tex);
	m_title.SetSize(TITLE_MAX_SIZE);
	m_title.SetPivot({ 0.5f,0.5f });
	m_title.SetPosition(TITLE_POS);

	//New Game
	m_newgame_tex.LoadEx("Assets/Sprite/4.png",0);
	m_newgame.Init(&m_newgame_tex);
	m_newgame.SetSize(NEWGAME_MAX_SIZE);
	m_newgame.SetPivot({ 0.5f, 0.5f });
	m_newgame.SetPosition(NEWGAME_POS);

	//Continue
	m_continue_tex.LoadEx("Assets/Sprite/2.png", 0);
	m_continue.Init(&m_continue_tex);
	m_continue.SetSize(CONTINUE_MAX_SIZE);
	m_continue.SetPivot({ 0.5f,0.5f });
	m_continue.SetPosition(CONTINUE_POS);

}

void SC_Start::Update()
{
	SetTexSize();
	SetScene();
}

void SC_Start::SetTexSize()
{
	CVector2 NewGameSize = NEWGAME_MAX_SIZE;
	CVector2 ContinueSize = CONTINUE_MAX_SIZE;

	switch (m_tex_num)
	{
	case NEWGAME:
		NewGameSize.Scale(SIZE_SCALE);
		break;
	case CONTINUE:
		ContinueSize.Scale(SIZE_SCALE);
		break;
	default:
		break;
	}

	m_continue.SetSize(ContinueSize);
	m_newgame.SetSize(NewGameSize);
}

void SC_Start::SetScene()
{
	float move = KeyInput().GetPad(0).GetLStickYF();

	int tex_num = m_tex_num;

	if (move < 0.0f || (GetAsyncKeyState(VK_UP) & 0x8000))
	{
		if (!m_UPressflag)
		{
			tex_num--;
			m_sound_choise = NewGO<CSoundSource>(0);
			m_sound_choise->Init("Assets/Sound/se_maoudamashii_system24.wav");
			m_sound_choise->Play(false);
			m_UPressflag = true;
		}
	}
	else
	{
		m_UPressflag = false;
	}
	
	if (move > 0.0f || (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		if (!m_DPressflag)
		{
			tex_num++;
			m_sound_choise = NewGO<CSoundSource>(0);
			m_sound_choise->Init("Assets/Sound/se_maoudamashii_system24.wav");
			m_sound_choise->Play(false);
			m_DPressflag = true;
		}
	}
	else
	{
		m_DPressflag = false;
	}

	if (tex_num < 0)
	{
		tex_num = TEXNUM - 1;
	}
	else if(TEXNUM <= tex_num)
	{
		tex_num = 0;
	}
	m_tex_num = (TexNum)tex_num;

	if (!KeyInput().GetPad(0).IsTrigger(enButtonA))
	{
		return;
	}

	switch (m_tex_num)
	{
	case NEWGAME:
		g_scene->Change(Scenes::NEWGAME);
		m_sound_choise = NewGO<CSoundSource>(0);
		m_sound_choise->Init("Assets/Sound/se_maoudamashii_system24.wav");
		m_sound_choise->Play(false);
		break;
	case CONTINUE:
		g_scene->Change(Scenes::CONTINUE);
		m_sound_choise = NewGO<CSoundSource>(0);
		m_sound_choise->Init("Assets/Sound/se_maoudamashii_system24.wav");
		m_sound_choise->Play(false);
		break;
	default:
		break;
	}
}

void SC_Start::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_continue.Draw(renderContext);
	m_newgame.Draw(renderContext);
	m_title.Draw(renderContext);
}

void SC_Start::Delete()
{
	DeleteGO(this);
}