#include "stdafx.h"
#include "Bar.h"
#include "Player.h"
#include "Scene.h"


SC_Bar::SC_Bar()
{
	m_state = STATE_NORMAL;
	m_LastFrame = 0;
	m_timer = 0.0f;

	m_target = PLAYER_HP;
}

SC_Bar::~SC_Bar()
{
}

void SC_Bar::Start(Bar_Target target)
{
	m_target = target;

	char filePath[256];
	sprintf(filePath, "Assets/sprite/%s", m_bar_dat[m_target].s_bar_name);
	m_BarTex.Load(filePath);
	m_Bar.Init(&m_BarTex);
	m_Bar.SetSize(m_bar_dat[m_target].s_bar_max_size);
	m_Bar.SetPivot({ 0.0f, 0.5f });
	m_Bar.SetPosition(m_bar_dat[m_target].s_bar_pos);

	sprintf(filePath, "Assets/sprite/%s", m_bar_dat[m_target].s_back_name);
	m_BarBackTex.Load(filePath);
	m_BarBack.Init(&m_BarBackTex);
	m_BarBack.SetSize(m_bar_dat[m_target].s_bar_max_size);
	m_BarBack.SetPivot({ 0.0f, 0.5f });
	m_BarBack.SetPosition(m_bar_dat[m_target].s_bar_pos);

	sprintf(filePath, "Assets/sprite/%s", m_bar_dat[m_target].s_gauge_name);
	m_GaugeTex.Load(filePath);
	m_Gauge.Init(&m_GaugeTex);
	m_Gauge.SetSize(m_bar_dat[m_target].s_gauge_max_size);
	m_Gauge.SetPivot({ 0.0f, 0.5f });
	m_Gauge.SetPosition(m_bar_dat[m_target].s_gauge_pos);

	switch (m_target)
	{
	case PLAYER_HP:
		m_LastFrame = (float)g_scene->GetPlayer()->GetHP();
		break;
	case PLAYER_MP:
		m_LastFrame = (float)g_scene->GetPlayer()->GetMP();
		break;
	case PLAYER_LV:
		break;
	default:
		break;
	}
}

void SC_Bar::Update()
{
	float Rate;
	//データに応じてバーのサイズを変える。
	switch (m_target)
	{
	case PLAYER_HP:
		Rate = (float)g_scene->GetPlayer()->GetHP() / (float)g_scene->GetPlayer()->GetMaxHP();
		break;
	case PLAYER_MP:
		Rate = (float)g_scene->GetPlayer()->GetMP() / (float)g_scene->GetPlayer()->GetMaxMP();
		break;
	case PLAYER_LV:	
		break;
	default:
		break;
	}

	CVector2 size = m_bar_dat[m_target].s_bar_max_size;
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
	case STATE_DAMAGE:
		CVector2 sizeBack = m_BarBack.GetSize();
		sizeBack.x -= 2.5f;

		if (sizeBack.x < size.x) 
		{
			m_state = STATE_NORMAL;
			sizeBack.x = size.x;
		}
		
		m_BarBack.SetSize(sizeBack);
		break;
	case STATE_NORMAL:
		switch (m_target)
		{
		case PLAYER_HP:
			if (m_LastFrame > g_scene->GetPlayer()->GetHP()) {
				//ダメージを受けた。
				m_state = STATE_DAMAGEWAIT;
				m_timer = 0.0f;
			}
			else if (m_LastFrame < g_scene->GetPlayer()->GetHP()) {
				//回復している。
				m_BarBack.SetSize(size);
			}	
			break;
		case PLAYER_MP:
			if (m_LastFrame > g_scene->GetPlayer()->GetMP()) {
				//ダメージを受けた。
				m_state = STATE_DAMAGEWAIT;
				m_timer = 0.0f;
			}
			else if (m_LastFrame < g_scene->GetPlayer()->GetMP()) {
				//回復している。
				m_BarBack.SetSize(size);
			}
			break;
		case PLAYER_LV:
			break;
		default:
			break;
		}
		break;
	}
	switch (m_target)
	{
	case PLAYER_HP:
		m_LastFrame = (float)g_scene->GetPlayer()->GetHP();
		break;
	case PLAYER_MP:
		m_LastFrame = (float)g_scene->GetPlayer()->GetMP();
		break;
	case PLAYER_LV:
		break;
	default:
		break;
	}
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