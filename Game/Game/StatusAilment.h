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
		{NORMAL, "ã∞ï|", 10, 1.2f},
		
		{WIND, "ãzé˚", 10, 2.4f},
		{WIND, "ì≈", 20, 3.0f},
		{WIND, "ñÉ·É", 25, 2.4f},
		
		{FIRE, "ãCê‚", 1, 2.5f},
		{FIRE, "ã∞ï|", 20, 5.0f},
		{FIRE, "èoåå", 30, 3.0f},
		{FIRE, "î≠âŒ", 20, 3.0f},
		
		{ICE, "ãCê‚", 10, 0.5f},
		{ICE, "ãzé˚", 20, 5.0f},
		{ICE, "ã∞ï|", 25, 3.0f},
		{ICE, "ìÄåã", 50, 0.5f},
		{ICE, "ñÉ·É", 20, 0.5f},

		{THUNDER, "à√à≈", 10, 1.6f},
		{THUNDER, "ãCê‚", 20, 1.5f},
		{THUNDER, "ã∞ï|", 10, 2.0f},
		{THUNDER, "èoåå", 30, 7.0f},
		{THUNDER, "ñÉ·É", 10, 5.2f},

		{AQUA, "à√à≈", 20, 5.2f},
		{AQUA, "ãCê‚", 10, 2.0f},
		{AQUA, "ãzé˚", 80, 5.0f},
		{AQUA, "ã∞ï|", 20, 1.0f},
		{AQUA, "ì≈", 40, 2.4f},
		{AQUA, "ñÉ·É", 10, 1.0f}
	};
};

