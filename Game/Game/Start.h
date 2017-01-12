#pragma once


class SC_Start :
	public IGameObject
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	SC_Start();

	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~SC_Start();

	/*!
	* @brief	UpDate()�̑O��1�񂾂��Ă΂��B
	*/
	void Start();

	/*!
	* @brief	�X�V�B
	*/
	void Update();

	/*!
	* @brief	�`��B
	*/
	void PostRender(CRenderContext& renderContext) override;

	/*!
	* @brief	�X�V�B
	*/
	void SetTexSize();

	/*!
	* @brief	�����̑傫���ݒ�B
	*/
	void SetScene();

	/*!
	* @brief	�폜�B
	*/
	void Delete();
private:
	/*CSoundSource* m_soundSource;*/

	CSprite		m_back;					//�w�i
	CTexture	m_back_tex;				//�w�i�̃e�N�X�`��

	CSprite		m_continue;				//�Â�����
	CTexture	m_continue_tex;			//�Â�����̃e�N�X�`��

	CSprite		m_newgame;				//�͂��߂���
	CTexture	m_newgame_tex;			//�͂��߂���̃e�N�X�`��

	CSprite		m_title;				//�^�C�g��
	CTexture	m_title_tex;			//�^�C�g���̃e�N�X�`��

	bool		m_UPressflag;
	bool		m_DPressflag;

	enum TexNum
	{
		NEWGAME,
		CONTINUE,
		TEXNUM,
	};

	TexNum		m_tex_num;

	const CVector2	BACK_POS			= { 0.0f, 0.0f };
	const CVector2	BACK_MAX_SIZE		= { 1500.0f, 1000.0f };

	const CVector2	NEWGAME_POS			= { 0.0f, -100.0f };
	const CVector2	NEWGAME_MAX_SIZE	= { 230.0f, 80.0f };

	const CVector2	CONTINUE_POS		= { 0.0f,-280.0f };
	const CVector2	CONTINUE_MAX_SIZE	= { 230.0f,80.0f };

	const CVector2	TITLE_POS			= { 0.0f,150.0f };
	const CVector2	TITLE_MAX_SIZE		= { 700.0f,200.0f };

	const float		SIZE_SCALE = 1.5f;
};