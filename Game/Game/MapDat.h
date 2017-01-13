#pragma once

struct SMapInfo {
	const char*	s_modelName;
	CVector3	s_position;
	CQuaternion	s_rotation;
	CVector3	s_scale;
};

std::vector<SMapInfo> Stage_1_1
{
#include "MapData/Mkazan.h"
};

std::vector<SMapInfo> Stage_1_2
{
#include "MapData/Mkazan6.h"
};