#pragma once

enum Scenes
{
	NOSCENES,
	//スタート画面
	START,
	//はじめから
	NEWGAME,
	//コンティニュー
	CONTINUE,
	//チュートリアル
	STAGE_T_1,
	STAGE_T_BATTLE,
	//風
	STAGE_1_1,
	STAGE_1_BATTLE,
	//炎
	STAGE_2_1,
	STAGE_2_BATTLE,
	//氷
	STAGE_3_1,
	STAGE_3_BATTLE,
	//雷
	STAGE_4_1,
	STAGE_4_BATTLE,
	//光
	STAGE_5_1,
	STAGE_5_BATTLE,

	GAME_CLEAR,

	GAMEOVER,
	//リザルト
	RESULT,

	STAGE_NUM,
};

enum CameraTarget
{
	CT_NOTARGET,
	CT_PLAYER,
	CT_ENEMY,
};

enum AnimationStat {
	AnimationStand2,
	AnimationStand,
	AnimationDamage,
	Animationmagic,
	AnimationAttack,
	AnimationWalk,
	AnimationNum,
};

enum MagicNo {
	FIER,
	SUNDER,
	ICE,
	AQUA,
	WIND,
	MAGICNUM,
};