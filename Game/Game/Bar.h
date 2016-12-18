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
		STATE_DAMAGEWAIT,		//ダメージ演出開始の待ち。
		STATE_DAMAGE,			//ダメージ演出。

	};
	CVector3 m_color;
	CSprite  m_Bar;				//バー。
	CSprite  m_Gauge;			//ゲージ。
	CSprite  m_BarBack;			//バーの背景。
	CTexture m_BarTex;			//バーのテクスチャ。
	CTexture m_GaugeTex;		//ゲージのテクスチャ。
	CTexture m_BarBackTex;		//バーの背景のテクスチャ
	EnState m_state;
	int m_LastFrame;			//1フレーム前のゲージ；
	float m_timer;		//タイマー。

	const CVector2 GAUGE_MAX_SIZE = { 245.0f, 15.75f };
	const CVector2 BAR_MAX_SIZE = { 230.5f, 7.2f };
	const CVector2 BAR_POS = { -592.95f, 320.0f };
	const CVector2 GAUGE_POS = { -600.0f, 320.0f };
};

