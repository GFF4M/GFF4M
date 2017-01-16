#include "stdafx.h"
#include "Magic.h"
#include "Scene.h"

SC_Magic::SC_Magic()
{
}


SC_Magic::~SC_Magic()
{
}

void SC_Magic::Start()
{

	
	m_all_magic_tex[FIER].LoadEx("Assets/Sprite/magicFIRE.png", 0);
	m_all_magic_tex[SUNDER].LoadEx("Assets/Sprite/magicTHUNDER.png", 0);
	m_all_magic_tex[ICE].LoadEx("Assets/Sprite/magicICE.png", 0);
	m_all_magic_tex[AQUA].LoadEx("Assets/Sprite/magicAQUA.png", 0);
	m_all_magic_tex[WIND].LoadEx("Assets/Sprite/magicWIND.png", 0);

	m_magic_tex = m_all_magic_tex[FIER];

	m_magic.Init(&m_magic_tex);
	m_magic.SetSize(MAGICMAXSIZE);
	m_magic.SetPivot({ 0.5f,0.5f });
	m_magic.SetPosition(MAGICPOS);


}

void SC_Magic::Update()
{

	
	
	
}

void SC_Magic::PostRender(CRenderContext& renderContext)
{
	m_magic.Draw(renderContext);
}

void SC_Magic::Change()
{
	m_magic_tex = m_all_magic_tex[g_scene->GetPlayer()->GetMagicNo()];
}

void SC_Magic::Delete()

{
	DeleteGO(this);
}