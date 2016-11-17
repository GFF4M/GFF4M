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
	CSprite  haikei;			//背景。
	CTexture haikeiTex;		//背景のテクスチャ。

	CSprite contenyu;		//つづきから
	CTexture contenyuTex	//つづきからのテクスチャ
		;

	CSprite  newGame;			//はじめから
	CTexture newGameTex;		//はじめからのテクスチャ

	CSprite Title;				//タイトル
	CTexture TitleTex;			//タイトルのテクスチャ



	const CVector2 haikeiPos = { 0.0f, 0.0f };
	const CVector2 haikeiMaxSize = { 1500.0f, 1000.0f };
	const CVector2 newGameMaxSize = { 230.0f, 80.0f };
	const CVector2 newGamePos = { 0.0f, -100.0f };
	const CVector2 contenyuPos = { 0.0f,-280.0f };
	const CVector2 contenyuMaxSize = { 230.0f,80.0f };
	const CVector2 TitlePos = { 0.0f,150.0f };
	const CVector2 TitleMaxSize = { 700.0f,200.0f };
};