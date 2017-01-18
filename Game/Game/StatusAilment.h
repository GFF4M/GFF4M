#pragma once
#define SA_NUM 25

class StatusAilment
{
public:
	enum SA_Eng
	{
		SA_DARKNESS,	//�È�
		SA_FAINT,		//�C��
		SA_ABSORPTION,	//�z��
		SA_FEAR,		//���|
		SA_BLEEDING,	//�o��
		SA_FROZEN,		//����
		SA_POISON,		//��
		SA_IGNITION,	//����
		SA_PARALYSIS,	//���
		SA_DATNUM		
	};

	struct StatusAilmentData
	{
		MagicNo			s_magicNo;
		SA_Eng			s_engName;
		int				s_per;
		float			s_time;
	};

	StatusAilment();
	~StatusAilment();

	enum AttackStat
	{
		AS_ME,
		AS_OTHER
	};

	void Execute(AttackStat stat, MagicNo magic);

	void Update();

	float GetStatusAilment(SA_Eng stat)
	{
		return m_timer[stat];
	}


private:
	const StatusAilmentData		m_SA_Dat[SA_NUM] =
	{
		{NORMAL, SA_FEAR, 10, 4.2f},
		
		{WIND, SA_ABSORPTION, 10, 5.4f},
		{WIND, SA_POISON, 20, 6.0f},
		{WIND, SA_PARALYSIS, 25, 5.4f},
		
		{FIRE, SA_FAINT, 2, 5.5f},
		{FIRE, SA_FEAR, 20, 8.0f},
		{FIRE, SA_BLEEDING, 30, 6.0f},
		{FIRE, SA_IGNITION, 20, 6.0f},
		
		{ICE, SA_FAINT, 10, 3.5f},
		{ICE, SA_ABSORPTION, 20, 5.0f},
		{ICE, SA_FEAR, 25, 3.0f},
		{ICE, SA_FROZEN, 50, 3.5f},
		{ICE, SA_PARALYSIS, 10, 3.5f},

		{THUNDER, SA_DARKNESS, 10, 4.6f},
		{THUNDER, SA_FAINT, 20, 4.5f},
		{THUNDER, SA_FEAR, 10, 5.0f},
		{THUNDER, SA_BLEEDING, 30, 10.0f},
		{THUNDER, SA_PARALYSIS, 10, 8.2f},

		{AQUA, SA_DARKNESS, 20, 8.2f},
		{AQUA, SA_FAINT, 10, 5.0f},
		{AQUA, SA_ABSORPTION, 80, 8.0f},
		{AQUA, SA_FEAR, 20, 4.0f},
		{AQUA, SA_POISON, 40, 5.4f},
		{AQUA, SA_PARALYSIS, 10, 4.0f}
	};

	const char*				m_sa_jpn[SA_DATNUM] =
	{
		"�È�",
		"�C��",
		"�z��",
		"���|",
		"�o��",
		"����",
		"��",
		"����",
		"���"
	};

	float					m_timer[SA_DATNUM];

	CRandom					m_random;
};

