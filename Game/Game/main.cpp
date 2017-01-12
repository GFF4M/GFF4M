#include "stdafx.h"
#include "Camera.h"
#include "Scene.h"
 
CLight	g_defaultLight;	//デフォルトライト。

/*!
 * @brief	tkEngineの初期化。
 */

void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;

	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;

	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = false;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 3;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	//DOF
	initParam.graphicsConfig.dofConfig.isEnable = false;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = false;
	
	//デフォルトライトの初期化。
	g_defaultLight.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	g_defaultLight.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });
	Engine().Init(initParam);	//初期化。

	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(40.0f);
	
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{

	//tkEngineの初期化。
	InitTkEngine( hInst );
	
	g_gameCamera = NewGO<Camera>(0);	//カメラを生成。
	g_scene = NewGO<Scene>(0);
	Engine().RunGameLoop();				//ゲームループを実行。

	return 0;
}

/*
GitHub
ID:GFF4M
Pass:team_4m
*/

/*
必要修正箇所

背景が黒くなる
何かの処理で重くなる（DOFが影響、ほかにも原因がある？）
スタート前のロードが長い（NewGOしすぎ）
タイトルの背景（これは後回し）
技の仕様（最重要）
マップの謎の落とし穴（原因は特定済）
レベルの実装
セーブデータの実装
会話実装
家からの移動実装
ダメージ判定どうしようか
敵の動き2種類書きたい


背景が黒くなる
パーティクルを敵の座標にする
攻撃のパーティクルとの当たり判定(1種類)
リザルト画面の作成（スプライト）
エネミーのアニメーションの制御
dog.X(攻撃,移動,)
doragon.X(攻撃,攻撃2,移動,)
golem.X(攻撃,移動,)
woodAttack.X(攻撃,移動,)
kinokomove.X(攻撃,移動,)
プレイヤーのアニメーションの制御
kano
ダメージの処理(敵とプレイヤー)
企画書？
動画作成
*/