#pragma once

struct SMapInfo {
	const char*	s_modelName;
	CVector3	s_position;
	CQuaternion	s_rotation;
	CVector3	s_scale;
};

std::vector<SMapInfo> Stage_T_1
{
#include "MapData/Msougen2.h"
};

std::vector<SMapInfo> Stage_T_B
{
#include "MapData/Msougen2.h"
};

std::vector<SMapInfo> Stage_1_1
{
#include "MapData/Mkazan6.h"
};

std::vector<SMapInfo> Stage_1_B
{
#include "MapData/Mkazan.h"
};

std::vector<SMapInfo> Stage_2_1
{
#include "MapData/Msougen3.h"
};

std::vector<SMapInfo> Stage_2_B
{
#include "MapData/Msougen3.h"
};

std::vector<SMapInfo> Stage_3_1
{
#include "MapData/Micestage5.h"
};

std::vector<SMapInfo> Stage_3_B
{
#include "MapData/Micestage5.h"
};

std::vector<SMapInfo> Stage_4_1
{
#include "MapData/Msougen2.h"
};

std::vector<SMapInfo> Stage_4_B
{
#include "MapData/Msougen2.h"
};

std::vector<SMapInfo> Stage_5_1
{
#include "MapData/Msougen3.h"
};

std::vector<SMapInfo> Stage_5_B
{
#include "MapData/Msougen3.h"
};
