#include "stdafx.h"
#include "Gameover.h"
#include "Scene.h"

SC_Gameover::SC_Gameover()
{
}


SC_Gameover::~SC_Gameover()
{
}

void SC_Gameover::Start()
{
	//”wŒi
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
	if (Pad(0).IsTrigger(enButtonA))
	{
		g_scene->Change(START);
		SaveGameover();
	}
}

void SC_Gameover::PostRender(CRenderContext& renderContext)
{
	m_back.Draw(renderContext);
	m_Gameover.Draw(renderContext);
}


bool SC_Gameover::SaveGameover()
{
	g_scene->GetPlayer()->SetHP(g_scene->GetPlayer()->GetMaxHP());
	g_scene->GetPlayer()->SetMP(g_scene->GetPlayer()->GetMaxMP());

	FILE *fp;

	fp = fopen(SAVE, "r");

	if (fp == NULL)
	{
		return false;
	}

	char dat[1000];

	fgets(dat, 1000, fp);

	Scenes r_scene;
	CVector3 r_pos;
	int r_hp;
	int r_mp;

	sscanf(dat, "%d,%f,%f,%f,%d,%d",
		&r_scene,
		&r_pos.x,
		&r_pos.y,
		&r_pos.z,
		&r_hp,
		&r_mp
	);

	fclose(fp);

	fp = fopen(SAVE, "w");

	if (fp == NULL)
	{
		return false;
	}

	sprintf(dat, "%d,%.5f,%.5f,%.5f,%d,%d",
		r_scene,
		r_pos.x,
		r_pos.y,
		r_pos.z,
		g_scene->GetPlayer()->GetMaxHP(),
		g_scene->GetPlayer()->GetMaxMP()
	);

	fputs(dat, fp);

	fclose(fp);

	return true;
}

void SC_Gameover::Delete()
{
	DeleteGO(this);
}