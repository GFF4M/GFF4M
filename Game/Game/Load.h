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
	CSprite m_load;			//���[�h
	CTexture m_load_tex;	//���[�h�̃e�N�X�`��

	const CVector2 LOADMAXSIZE	= { 230.0f, 80.0f };
	const CVector2 LOADPOS		= { 0.0f, -100.0f };

};