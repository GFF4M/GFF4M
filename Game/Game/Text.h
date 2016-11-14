#pragma once
class Text :
	public IGameObject
{
public:
	Text();
	~Text();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
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

};