#pragma once
#include "Player.h"
class Magic :
	public IGameObject
{
public:
	Magic();
	~Magic();

	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);

	void Delete();
	enum MagicNo {
		FIER,
		SUNDER,
		ICE,
		AQUA,
		WIND
	};
	
private:
	CSprite m_magic;			//���@
	CTexture m_magic_tex;	//���@�̃e�N�X�`��
	/*Player*				m_play;*/
	int				m_magicNo;

	const CVector2 MAGICMAXSIZE = { 300.0f, 300.0f };
	const CVector2 MAGICPOS = { 500.0f, -250.0f };

	
};