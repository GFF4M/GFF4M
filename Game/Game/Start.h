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
	CSprite		m_back;			//�w�i�B
	CTexture	m_back_tex;			//�w�i�̃e�N�X�`���B

	CSprite		m_continue;			//�Â�����
	CTexture	m_continue_tex;		//�Â�����̃e�N�X�`��

	CSprite		m_newgame;			//�͂��߂���
	CTexture	m_newgame_tex;		//�͂��߂���̃e�N�X�`��

	CSprite		m_title;				//�^�C�g��
	CTexture	m_title_tex;			//�^�C�g���̃e�N�X�`��


	const CVector2 BACKPOS			= { 0.0f, 0.0f };
	const CVector2 BACKMAXSIZE		= { 1500.0f, 1000.0f };

	const CVector2 NEWGAMEPOS		= { 0.0f, -100.0f };
	const CVector2 NEWGAMEMAXSIZE	= { 230.0f, 80.0f };

	const CVector2 CONTINUEPOS		= { 0.0f,-280.0f };
	const CVector2 CONTINUEMAXSIZE	= { 230.0f,80.0f };

	const CVector2 TITLEPOS			= { 0.0f,150.0f };
	const CVector2 TITLEMAXSIZE		= { 700.0f,200.0f };
};