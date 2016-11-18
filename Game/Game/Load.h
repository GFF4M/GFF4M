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
	CSprite  m_back;			//�w�i�B
	CTexture m_back_tex;		//�w�i�̃e�N�X�`���B

	CSprite m_load;		//�Â�����
	CTexture m_load_tex;	//�Â�����̃e�N�X�`��

};