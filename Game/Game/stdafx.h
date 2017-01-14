/*!
 * @brief	プリコンパイル済みヘッダー。
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_


#include <windows.h>
#include <time.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"
#include "tkEngine/Physics/tkPhysics.h"
using namespace tkEngine;
#include "tkEngine/random/tkRandom.h"
#include "tkEngine/graphics/sprite/tkSprite.h"
#include "tkEngine/particle/tkParticleEmitter.h"

#include "EnumDat.h"

#define DELTA_TIME 1.0f / 60.0f

extern CLight g_defaultLight;	//デフォルトライト。

#endif // _STDAFX_H_