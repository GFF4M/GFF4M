#pragma once

enum Scenes
{
	NOSCENES,
	//�X�^�[�g���
	START,
	//�͂��߂���
	NEWGAME,
	//�R���e�B�j���[
	CONTINUE,
	//�`���[�g���A��
	STAGE_T_1,
	STAGE_T_BATTLE,
	//��
	STAGE_1_1,
	STAGE_1_BATTLE,
	//��
	STAGE_2_1,
	STAGE_2_BATTLE,
	//�X
	STAGE_3_1,
	STAGE_3_BATTLE,
	//��
	STAGE_4_1,
	STAGE_4_BATTLE,
	//��
	STAGE_5_1,
	STAGE_5_BATTLE,
	STAGE_NUM,
};

enum CameraTarget
{
	CT_NOTARGET,
	CT_PLAYER,
	CT_ENEMY,
};
