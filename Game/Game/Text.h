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
	CSprite  haikei;			//�w�i�B
	CTexture haikeiTex;		//�w�i�̃e�N�X�`���B

	CSprite contenyu;		//�Â�����
	CTexture contenyuTex	//�Â�����̃e�N�X�`��
		;

	CSprite  newGame;			//�͂��߂���
	CTexture newGameTex;		//�͂��߂���̃e�N�X�`��

	CSprite Title;				//�^�C�g��
	CTexture TitleTex;			//�^�C�g���̃e�N�X�`��

};