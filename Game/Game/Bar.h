#pragma once
class SC_Bar : public IGameObject
{
public:
	SC_Bar();
	~SC_Bar();
	void Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

	void Delete();

private:
	enum EnState {
		STATE_NORMAL,
		STATE_DAMAGEWAIT,		//�_���[�W���o�J�n�̑҂��B
		STATE_DAMAGE,			//�_���[�W���o�B

	};
	CVector3 m_color;
	CSprite  m_Bar;				//�o�[�B
	CSprite  m_Gauge;			//�Q�[�W�B
	CSprite  m_BarBack;			//�o�[�̔w�i�B
	CTexture m_BarTex;			//�o�[�̃e�N�X�`���B
	CTexture m_GaugeTex;		//�Q�[�W�̃e�N�X�`���B
	CTexture m_BarBackTex;		//�o�[�̔w�i�̃e�N�X�`��
	EnState m_state;
	int m_LastFrame;			//1�t���[���O�̃Q�[�W�G
	float m_timer;		//�^�C�}�[�B

	const CVector2 GAUGE_MAX_SIZE = { 245.0f, 15.75f };
	const CVector2 BAR_MAX_SIZE = { 230.5f, 7.2f };
	const CVector2 BAR_POS = { -592.95f, 320.0f };
	const CVector2 GAUGE_POS = { -600.0f, 320.0f };
};

