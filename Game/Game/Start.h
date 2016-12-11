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

	CSprite		m_continue;				//�Â�����
	CTexture	m_continue_tex;			//�Â�����̃e�N�X�`��

	CSprite		m_newgame;				//�͂��߂���
	CTexture	m_newgame_tex;			//�͂��߂���̃e�N�X�`��

	CSprite		m_title;				//�^�C�g��
	CTexture	m_title_tex;			//�^�C�g���̃e�N�X�`��

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