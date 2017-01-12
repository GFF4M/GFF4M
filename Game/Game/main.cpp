#include "stdafx.h"
#include "Camera.h"
#include "Scene.h"
 
CLight	g_defaultLight;	//�f�t�H���g���C�g�B

/*!
 * @brief	tkEngine�̏������B
 */

void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//�R�}���h�o�b�t�@�̃T�C�Y�̃e�[�u���B
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//�����_�����O�R���e�L�X�g�͈�{
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
	
	//�f�t�H���g���C�g�̏������B
	g_defaultLight.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	g_defaultLight.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });
	Engine().Init(initParam);	//�������B

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

	//tkEngine�̏������B
	InitTkEngine( hInst );
	
	g_gameCamera = NewGO<Camera>(0);	//�J�����𐶐��B
	g_scene = NewGO<Scene>(0);
	Engine().RunGameLoop();				//�Q�[�����[�v�����s�B

	return 0;
}

/*
GitHub
ID:GFF4M
Pass:team_4m
*/

/*
�K�v�C���ӏ�

�w�i�������Ȃ�
�����̏����ŏd���Ȃ�iDOF���e���A�ق��ɂ�����������H�j
�X�^�[�g�O�̃��[�h�������iNewGO�������j
�^�C�g���̔w�i�i����͌�񂵁j
�Z�̎d�l�i�ŏd�v�j
�}�b�v�̓�̗��Ƃ����i�����͓���ρj
���x���̎���
�Z�[�u�f�[�^�̎���
��b����
�Ƃ���̈ړ�����
�_���[�W����ǂ����悤��
�G�̓���2��ޏ�������


�w�i�������Ȃ�
�p�[�e�B�N����G�̍��W�ɂ���
�U���̃p�[�e�B�N���Ƃ̓����蔻��(1���)
���U���g��ʂ̍쐬�i�X�v���C�g�j
�G�l�~�[�̃A�j���[�V�����̐���
dog.X(�U��,�ړ�,)
doragon.X(�U��,�U��2,�ړ�,)
golem.X(�U��,�ړ�,)
woodAttack.X(�U��,�ړ�,)
kinokomove.X(�U��,�ړ�,)
�v���C���[�̃A�j���[�V�����̐���
kano
�_���[�W�̏���(�G�ƃv���C���[)
��揑�H
����쐬
*/