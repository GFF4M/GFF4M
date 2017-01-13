#include "stdafx.h"
#include "Magic.h"

SC_Magic::SC_Magic()
{
	m_magicNo = 0;
	
}


SC_Magic::~SC_Magic()
{
}

void SC_Magic::Start()
{
	
	/*int magicNo = m_play->GetMagicNo();
	m_play = nullptr;*/
	
	m_magic_tex.LoadEx("Assets/Sprite/magicFIRE.png", 0);

	m_magic.Init(&m_magic_tex);
	m_magic.SetSize(MAGICMAXSIZE);
	m_magic.SetPivot({ 0.5f,0.5f });
	m_magic.SetPosition(MAGICPOS);


}

void SC_Magic::Update()
{
	
	if (KeyInput().GetPad(0).IsTrigger(enButtonRB2))
	{
		m_magicNo++;
		if (m_magicNo > WIND) {
			m_magicNo = FIER;
		}
		switch (m_magicNo) {
		case FIER:
			m_magic_tex.LoadEx("Assets/Sprite/magicFIRE.png", 0);
			break;
		case SUNDER:
			m_magic_tex.LoadEx("Assets/Sprite/magicTHUNDER.png", 0);
			break;
		case ICE:
			m_magic_tex.LoadEx("Assets/Sprite/magicICE.png", 0);
			break;
		case AQUA:
			m_magic_tex.LoadEx("Assets/Sprite/magicAQUA.png", 0);
			break;
		case WIND:
			m_magic_tex.LoadEx("Assets/Sprite/magicWIND.png", 0);
			break;
		}
	}
	
	
	
}

void SC_Magic::PostRender(CRenderContext& renderContext)
{
	m_magic.Draw(renderContext);
}

void SC_Magic::Delete()
{
	DeleteGO(this);
}