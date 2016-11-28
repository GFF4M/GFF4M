#pragma once
#include "stdafx.h"
class ModelHandle
{
public:
	ModelHandle();
	~ModelHandle();

	CSkinModelDataHandle& GetModel_Player()
	{
		return m_model_player;
	};

private:
	CSkinModelDataHandle	m_model_player;				//スキンモデルデータハンドル。
};

extern ModelHandle* g_modelhandle;

