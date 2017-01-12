#pragma once
class SC_Load : public IGameObject
{
public:
	SC_Load();
	~SC_Load();
	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);

	void Delete();

private:
	
	CSprite m_load;			//ロード
	CTexture m_load_tex;	//ロードのテクスチャ

	CSprite		m_back;					//背景
	CTexture	m_back_tex;				//背景のテクスチャ

	const CVector2 LOADMAXSIZE	= { 230.0f, 80.0f };
	const CVector2 LOADPOS		= { 0.0f, -100.0f };

	const CVector2	BACK_POS = { 0.0f, 0.0f };
	const CVector2	BACK_MAX_SIZE = { 1500.0f, 1000.0f };
};