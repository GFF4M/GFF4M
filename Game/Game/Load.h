#pragma once
class SC_Load :
	public IGameObject
{
public:
	SC_Load();
	~SC_Load();
	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);

	void Delete();
private:
	/*CSoundSource	soundSource;*/
	CSprite  m_back;			//背景。
	CTexture m_back_tex;		//背景のテクスチャ。

	CSprite m_load;		//つづきから
	CTexture m_load_tex;	//つづきからのテクスチャ

};