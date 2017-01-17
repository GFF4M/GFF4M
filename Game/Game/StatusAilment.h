#pragma once
#define SA_NUM 24

class StatusAilment
{
public:
	StatusAilment();
	~StatusAilment();

	struct StatusAilmentData
	{
		MagicNo			s_magicNo;
		const char*		s_name;
		int				s_per;
		float			s_time;
	};

private:
	const StatusAilmentData		m_SA_Dat[SA_NUM] =
	{
		{NORMAL, "���|", 10, 1.2f},
		
		{WIND, "�z��", 10, 2.4f},
		{WIND, "��", 20, 3.0f},
		{WIND, "���", 25, 2.4f},
		
		{FIRE, "�C��", 1, 2.5f},
		{FIRE, "���|", 20, 5.0f},
		{FIRE, "�o��", 30, 3.0f},
		{FIRE, "����", 20, 3.0f},
		
		{ICE, "�C��", 10, 0.5f},
		{ICE, "�z��", 20, 5.0f},
		{ICE, "���|", 25, 3.0f},
		{ICE, "����", 50, 0.5f},
		{ICE, "���", 20, 0.5f},

		{THUNDER, "�È�", 10, 1.6f},
		{THUNDER, "�C��", 20, 1.5f},
		{THUNDER, "���|", 10, 2.0f},
		{THUNDER, "�o��", 30, 7.0f},
		{THUNDER, "���", 10, 5.2f},

		{AQUA, "�È�", 20, 5.2f},
		{AQUA, "�C��", 10, 2.0f},
		{AQUA, "�z��", 80, 5.0f},
		{AQUA, "���|", 20, 1.0f},
		{AQUA, "��", 40, 2.4f},
		{AQUA, "���", 10, 1.0f}
	};
};

