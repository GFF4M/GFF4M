#pragma once


class SC_Start :
	public IGameObject
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	SC_Start();

	/*!
	* @brief	デストラクタ。
	*/
	~SC_Start();

	/*!
	* @brief	UpDate()の前に1回だけ呼ばれる。
	*/
	void Start();

	/*!
	* @brief	更新。
	*/
	void Update();

	/*!
	* @brief	描画。
	*/
	void PostRender(CRenderContext& renderContext) override;

	/*!
	* @brief	更新。
	*/
	void SetTexSize();

	/*!
	* @brief	文字の大きさ設定。
	*/
	void SetScene();

	/*!
	* @brief	削除。
	*/
	void Delete();
private:
	/*CSoundSource* m_soundSource;*/

	CSprite		m_back;					//背景
	CTexture	m_back_tex;				//背景のテクスチャ

	CSprite		m_continue;				//つづきから
	CTexture	m_continue_tex;			//つづきからのテクスチャ

	CSprite		m_newgame;				//はじめから
	CTexture	m_newgame_tex;			//はじめからのテクスチャ

	CSprite		m_title;				//タイトル
	CTexture	m_title_tex;			//タイトルのテクスチャ

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