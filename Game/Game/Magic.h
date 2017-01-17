#pragma once
class SC_Magic : public IGameObject
{
public:
	SC_Magic();
	~SC_Magic();

	void Start();
	void Update();
	void PostRender(CRenderContext& renderContext);

	void Delete();

	void Change();
	
private:
	
	CSprite m_magic;		//���@
	CTexture m_magic_tex;	//���@�̃e�N�X�`��
	CTexture m_all_magic_tex[MAGICNUM];	//���@�̃e�N�X�`��

	const CVector2 MAGICMAXSIZE = { 300.0f, 300.0f };
	const CVector2 MAGICPOS = { 500.0f, -250.0f };

	
};