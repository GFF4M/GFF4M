#include "stdafx.h"
#include "Bar.h"
#include "Player.h"


SC_Bar::SC_Bar()
{
	m_state = STATE_NORMAL;
	m_LastFrame = 0;
	m_timer = 0.0f;
}

SC_Bar::~SC_Bar()
{
}

void SC_Bar::Start()
{
	m_BarTex.Load("Assets/sprite/White.png");
	m_Bar.Init(&m_BarTex);
	m_Bar.SetSize(BAR_MAX_SIZE);
	m_Bar.SetPivot({ 0.0f, 0.5f });
	m_Bar.SetPosition(BAR_POS);

	m_BarBackTex.Load("Assets/sprite/Yellow.png");
	m_BarBack.Init(&m_BarBackTex);
	m_BarBack.SetSize(BAR_MAX_SIZE);
	m_BarBack.SetPivot({ 0.0f, 0.5f });
	m_BarBack.SetPosition(BAR_POS);

	m_GaugeTex.Load("Assets/sprite/Black.png");
	m_Gauge.Init(&m_GaugeTex);
	m_Gauge.SetSize(GAUGE_MAX_SIZE);
	m_Gauge.SetPivot({ 0.0f, 0.5f });
	m_Gauge.SetPosition(GAUGE_POS);

	m_LastFrame = g_play->GetHP();
}

void SC_Bar::Update()
{
	//プレイヤーの残HPに応じてＨＰバーのサイズを変える。

	float Rate = (float)g_play->GetHP() / (float)g_play->GetMaxHP();
	CVector2 size = BAR_MAX_SIZE;
	size.x *= Rate;
	m_Bar.SetSize(size);
	switch (m_state) {
	case STATE_DAMAGEWAIT:
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 0.5f) {
			//ダメージ演出開始。
			m_state = STATE_DAMAGE;
			m_timer = 0.0f;
		}
		break;
	case STATE_DAMAGE: {
		CVector2 sizeHPBack = m_BarBack.GetSize();
		sizeHPBack.x -= 2.5f;
		if (sizeHPBack.x < size.x) {
			m_state = STATE_NORMAL;
			sizeHPBack.x = size.x;
		}
		m_BarBack.SetSize(sizeHPBack);
	}break;
	case STATE_NORMAL:
		if (m_LastFrame > g_play->GetHP()) {
			//ダメージを受けた。
			m_state = STATE_DAMAGEWAIT;
			m_timer = 0.0f;
		}
		else if (m_LastFrame < g_play->GetHP()) {
			//回復している。
			m_BarBack.SetSize(size);
		}
		break;
	}
	m_LastFrame = g_play->GetHP();
}

void SC_Bar::PostRender(CRenderContext& renderContext)
{
	m_Gauge.Draw(renderContext);
	m_BarBack.Draw(renderContext);
	m_Bar.Draw(renderContext);
}

void SC_Bar::Delete()
{
	DeleteGO(this);
}