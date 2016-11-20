#pragma once
class SC_Start :
	public IGameObject
{
public:
	SC_Start();
	~SC_Start();

	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext) override;

	void Delete();
private:
	/*CSoundSource	soundSource;*/

	CSprite		m_continue;				//つづきから
	CTexture	m_continue_tex;			//つづきからのテクスチャ

	CSprite		m_newgame;				//はじめから
	CTexture	m_newgame_tex;			//はじめからのテクスチャ

	CSprite		m_title;				//タイトル
	CTexture	m_title_tex;			//タイトルのテクスチャ


	const CVector2 NEWGAMEPOS		= { 0.0f, -100.0f };
	const CVector2 NEWGAMEMAXSIZE	= { 230.0f, 80.0f };

	const CVector2 CONTINUEPOS		= { 0.0f,-280.0f };
	const CVector2 CONTINUEMAXSIZE	= { 230.0f,80.0f };

	const CVector2 TITLEPOS			= { 0.0f,150.0f };
	const CVector2 TITLEMAXSIZE		= { 700.0f,200.0f };
};