#pragma once
class SC_result : public IGameObject
{
public:
	SC_result();
	~SC_result();
	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
	void Delete();

private:

	CSprite		m_result;					//���[�h
	CTexture	m_result_tex;				//���[�h�̃e�N�X�`��

	CSprite		m_back;					//�w�i
	CTexture	m_back_tex;				//�w�i�̃e�N�X�`��

	const CVector2 RESULTMAXSIZE = { 230.0f, 80.0f };
	const CVector2 RESULTPOS = { 0.0f, -100.0f };

	const CVector2	BACK_POS = { 0.0f, 0.0f };
	const CVector2	BACK_MAX_SIZE = { 1500.0f, 1000.0f };
};