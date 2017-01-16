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

	CSprite		m_Gameover;				//�Q�[���I�[�o�[
	CTexture	m_Gameover_tex;			//�Q�[���I�[�o�[�̃e�N�X�`��

	CSprite		m_back;					//�w�i
	CTexture	m_back_tex;				//�w�i�̃e�N�X�`��

	const CVector2 GAMEOVERMAXSIZE = { 230.0f, 80.0f };
	const CVector2 GAMEOVERPOS = { 0.0f, -100.0f };

	const CVector2	BACK_POS = { 0.0f, 0.0f };
	const CVector2	BACK_MAX_SIZE = { 1500.0f, 1000.0f };
};

