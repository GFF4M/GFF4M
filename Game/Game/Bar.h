#pragma once
class SC_Bar : public IGameObject
{
public:
	enum Bar_Target{
		PLAYER_HP,
		PLAYER_MP,
		PLAYER_LV,
	};

	SC_Bar();
	~SC_Bar();
	void Start(Bar_Target target);
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

	Bar_Target m_target;

	struct BarDat
	{
		CVector2 s_bar_max_size;
		CVector2 s_bar_pos;

		CVector2 s_gauge_max_size;
		CVector2 s_gauge_pos;

		const char* s_bar_name;
		const char* s_back_name;
		const char* s_gauge_name;
	};

	const BarDat m_bar_dat[2] =
	{ 
		{
			{ 230.5f, 7.2f },
			{ -592.95f, 330.0f },
			{ 245.0f, 15.75f },
			{ -600.0f, 330.0f },
			"White.png",
			"Yellow.png",
			"Black.png",
		},
		{
			{ 230.5f, 7.2f },
			{ -592.95f, 350.0f },
			{ 245.0f, 15.75f },
			{ -600.0f, 350.0f },
			"Black.png",
			"Yellow.png",
			"White.png",
		}, 
	};
};


const CVector2 GAUGE_MAX_SIZE = { 245.0f, 15.75f };
const CVector2 BAR_MAX_SIZE = { 230.5f, 7.2f };
const CVector2 BAR_POS = { -592.95f, 320.0f };
const CVector2 GAUGE_POS = { -600.0f, 320.0f };