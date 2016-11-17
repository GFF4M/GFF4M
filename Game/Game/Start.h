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
	CSprite  haikei;			//�w�i�B
	CTexture haikeiTex;		//�w�i�̃e�N�X�`���B

	CSprite contenyu;		//�Â�����
	CTexture contenyuTex	//�Â�����̃e�N�X�`��
		;

	CSprite  newGame;			//�͂��߂���
	CTexture newGameTex;		//�͂��߂���̃e�N�X�`��

	CSprite Title;				//�^�C�g��
	CTexture TitleTex;			//�^�C�g���̃e�N�X�`��



	const CVector2 haikeiPos = { 0.0f, 0.0f };
	const CVector2 haikeiMaxSize = { 1500.0f, 1000.0f };
	const CVector2 newGameMaxSize = { 230.0f, 80.0f };
	const CVector2 newGamePos = { 0.0f, -100.0f };
	const CVector2 contenyuPos = { 0.0f,-280.0f };
	const CVector2 contenyuMaxSize = { 230.0f,80.0f };
	const CVector2 TitlePos = { 0.0f,150.0f };
	const CVector2 TitleMaxSize = { 700.0f,200.0f };
};