#include "stdafx.h"
#include "Magic.h"

Magic::Magic()
{
	m_magicNo = 0;
	
}


Magic::~Magic()
{
}

void Magic::Start()
{
	
	/*int magicNo = m_play->GetMagicNo();
	m_play = nullptr;*/
	
	m_magic_tex.LoadEx("Assets/Sprite/magicFIRE.png", 0);

	m_magic.Init(&m_magic_tex);
	m_magic.SetSize(MAGICMAXSIZE);
	m_magic.SetPivot({ 0.5f,0.5f });
	m_magic.SetPosition(MAGICPOS);


}

void Magic::Update()
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
			m_magic_tex.LoadEx("Assets/Sprite/magicAQUA.png", 0);
			break;
		case AQUA:
			m_magic_tex.LoadEx("Assets/Sprite/magicICE.png", 0);
			break;
		case WIND:
			m_magic_tex.LoadEx("Assets/Sprite/magicWIND.png", 0);
			break;
		}
	}
	
	
	
}

void Magic::PostRender(CRenderContext& renderContext)
{
	m_magic.Draw(renderContext);
}

void Magic::Delete()
{
	DeleteGO(this);
}