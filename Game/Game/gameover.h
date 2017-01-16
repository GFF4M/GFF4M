#pragma once
class SC_Gameover :
	public IGameObject
{
public:
	SC_Gameover();
	~SC_Gameover();

	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
	bool SaveGameover();
	void Delete();

private:

	CSprite		m_Gameover;				//ゲームオーバー
	CTexture	m_Gameover_tex;			//ゲームオーバーのテクスチャ

	CSprite		m_back;					//背景
	CTexture	m_back_tex;				//背景のテクスチャ

	const CVector2 GAMEOVERMAXSIZE = { 230.0f, 80.0f };
	const CVector2 GAMEOVERPOS = { 0.0f, -100.0f };

	const CVector2	BACK_POS = { 0.0f, 0.0f };
	const CVector2	BACK_MAX_SIZE = { 1500.0f, 1000.0f };
};

