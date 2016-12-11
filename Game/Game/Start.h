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

	void SetTexSize();

	void SetScene();

	void Delete();
private:
	/*CSoundSource	soundSource;*/

	CSprite		m_continue;				//つづきから
	CTexture	m_continue_tex;			//つづきからのテクスチャ

	CSprite		m_newgame;				//はじめから
	CTexture	m_newgame_tex;			//はじめからのテクスチャ

	CSprite		m_title;				//タイトル
	CTexture	m_title_tex;			//タイトルのテクスチャ

	enum TexNum
	{
		NEWGAME,
		CONTINUE,
		TEXNUM,
	};

	union
	{
		TexNum		m_tex_num;
		int			m_tex_num_i;
	};
	const CVector2	NEWGAME_POS		= { 0.0f, -100.0f };
	const CVector2	NEWGAME_MAX_SIZE	= { 230.0f, 80.0f };

	const CVector2	CONTINUE_POS		= { 0.0f,-280.0f };
	const CVector2	CONTINUE_MAX_SIZE	= { 230.0f,80.0f };

	const CVector2	TITLE_POS			= { 0.0f,150.0f };
	const CVector2	TITLE_MAX_SIZE		= { 700.0f,200.0f };

	const float		SIZE_SCALE = 1.5f;
};