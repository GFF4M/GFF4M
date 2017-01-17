#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "Scene.h"

Player *g_play;

Player::Player()
{
	m_angle = 0.0f;
	m_position = { 0.0f,0.0f,0.0f };
	m_look_pos = { 0.0f,2.0f,0.0f };
	m_scale = {0.7f,0.7f,0.7f };
	m_rotation = CQuaternion::Identity;
	m_animationStat = AnimationStand;
	m_radius = 0.5f;
	m_dead = false;

	m_characterController.Init(m_radius, 1.0f, m_position);//�L�����N�^�R���g���[���̏������B

	m_hp	= 5000;
	m_maxhp = 5000;
	m_hp_charge = 0.0f;

	m_mp	= 200;
	m_maxmp = 200;
	m_mp_charge = 0.0f;
	
	m_random.Init((unsigned int)time(NULL));
	m_magicNo = FIRE;
	m_ismagic = false;

	m_moveflg = false;

	m_particle = nullptr;

	m_particletimer = 0.0f;

	m_particle_charge = nullptr;

	m_particletimer_charge = 0.0f;
}

Player::~Player()
{
}

void Player::Start()
{
	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/kano.X", &m_animation);

	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//�f�t�H���g���C�g��ݒ�B

	m_animation.SetAnimationLoopFlag(AnimationAttack, false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
	m_animation.SetAnimationLoopFlag(Animationmagic, false);
	m_animation.SetAnimationLoopFlag(AnimationDamage, false);
}

void Player::Update()
{
	DeadCheck();

	Charge();

	DeleteCheck();

	MagicChange();

	Magic();

	if (m_moveflg && !m_ismagic)
	{
		Move();
	}
	else if (m_moveflg && m_ismagic)
	{
		CVector3 move = m_characterController.GetMoveSpeed();
		move.Scale({ 0.0f,1.0f,0.0f });
		//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
		m_characterController.SetMoveSpeed(move);
		//�L�����N�^�[�R���g���[���[�����s�B
		m_characterController.Execute();
		//���s���ʂ��󂯎��B
		m_position = m_characterController.GetPosition();

		m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
	}
	
	switch (m_animationStat)
	{
	case AnimationDamage:
		m_animation.Update(1.0f / 60.0f);
		break;
	default:
		m_animation.Update(2.0f / 60.0f);
		break;
	}
	//���[���h�s��̍X�V�B
	m_skinModel.Update(m_position,m_rotation, m_scale);

	if (m_particle != nullptr && m_particletimer <= 0.0f)
	{
		DeleteGO(m_particle);
		m_particle = nullptr;
	}

	if (m_particletimer > 0.0f)
	{
		m_particletimer -= 1.0f / 60.0f;
	}

	if (m_particle_charge != nullptr && m_particletimer_charge <= 0.0f)
	{
		DeleteGO(m_particle_charge);
		m_particle_charge = nullptr;
	}

	if (m_particletimer_charge > 0.0f)
	{
		m_particletimer_charge -= 1.0f / 60.0f;
	}
}

void Player::Move()
{
	//�L�����N�^�[�̈ړ����x������B
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF();
	move.z = -Pad(0).GetLStickYF();

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//�����x�N�g��
	moveXZ.y = 0.0f;

	if (moveXZ.Length() > 0.0f)
	{
		if (m_animationStat != AnimationWalk)
		{
			m_animationStat = AnimationWalk;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
		}

		//AxisZ��moveXZ�̂Ȃ��p�����߂�
		m_angle = moveXZ.AngleBetween(CVector3::AxisZ);

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}

		//�J�����ɂ��␳
		m_angle -= g_gameCamera->GetAngle().x;

		//��]���������Ɉړ�
		move.x = sin(CMath::DegToRad(m_angle)) * 1000.0f * DELTA_TIME;
		move.z = cos(CMath::DegToRad(m_angle)) * 1000.0f * DELTA_TIME;
	}
	else
	{
		if (m_animationStat != AnimationStand && !m_ismagic)
		{
			m_animationStat = AnimationStand2;
			m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
			
		}
	}
	
	//�p�x�̐��K��
	if (m_angle < -180.0f)
	{
		m_angle += 360.0f;
	}
	else if (180.0f < m_angle)
	{
		m_angle -= 360.0f;
	}

	//��i�W�����v
	if (KeyInput().GetPad(0).IsPress(enButtonA) && m_characterController.IsOnGround())
	{
		m_characterController.Jump();
		move.y = 8.0f;
		
	}

	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	m_characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s�B
	m_characterController.Execute();
	//���s���ʂ��󂯎��B
	m_position = m_characterController.GetPosition();

	m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
}

void Player::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Player::Delete()
{
	m_dead = true;
}

void Player::Particle() {
	if (m_particle != nullptr)
	{
		return;
	}

	CVector3 target = g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->GetPos();

	target.y = GetLookPos().y;

	switch (m_magicNo) {
	case FIRE:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.8f,											//!<�����B�P�ʂ͕b�B
			0.01f,											//!<�������ԁB�P�ʂ͕b�B
			17.0f,											//!<�p�[�e�B�N���̕��B
			17.0f,											//!<�p�[�e�B�N���̍����B
			{ 3.0f, 3.0f, 3.0f },							//!<�����ʒu�̃����_�����B
			{ 1.0f, 1.0f, 1.0f },							//!<�����x�̃����_�����B
			{ 1.0f, 1.0f, 1.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f,0.25f, 0.25f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);
		m_particletimer = 0.8f;
		break;
	case THUNDER:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/Thunder2.tga",				//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },								//!<�����x�B

			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f,											//!<�p�[�e�B�N���̕��B
			10.0f,											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f, 1.0f, 0.5f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			0.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);
		m_particletimer = 0.4f;
		break;
	case ICE:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/ice.tga",//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 5.0f, 0.0f },								//!<�����x�B
			0.4f,											//!<�����B�P�ʂ͕b�B
			0.1f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f * (1.0f - (float)m_random.GetRandDouble() / 2.0f),											//!<�p�[�e�B�N���̕��B
			10.0f * (1.0f - (float)m_random.GetRandDouble() / 2.0f),											//!<�p�[�e�B�N���̍����B
			{ 5.0f, 6.0f, 5.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 2.0f, 0.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f, 0.5f, 0.5f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, -2.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);
		m_particletimer = 0.4f;
		break;
	case AQUA:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/aqua.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 20.0f, 0.0f },								//!<�����x�B
			2.0f,											//!<�����B�P�ʂ͕b�B
			0.01f,											//!<�������ԁB�P�ʂ͕b�B
			2.0f + ((float)m_random.GetRandDouble() - 0.5f),											//!<�p�[�e�B�N���̕��B
			2.0f + ((float)m_random.GetRandDouble() - 0.5f),											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 5.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 5.0f, 0.0f, 5.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{

				{ 0.0f, 0.0f, 0.25f,0.25f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, -20.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);
		m_particletimer = 2.0f;
		break;
	case WIND:
		m_random.GetRandDouble();
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<�e�N�X�`���̃t�@�Cw���p�X�B
			{ 10.0f, 0.0f, 0.0f },							//!<�����x�B

			0.5f,											//!<�����B�P�ʂ͕b�B
			0.2f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f * ((float)m_random.GetRandDouble() + 0.5f),											//!<�p�[�e�B�N���̕��B
			10.0f * ((float)m_random.GetRandDouble() + 0.5f),											//!<�p�[�e�B�N���̍����B
			{ 5.0f, 3.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 3.0f, 5.0f, 1.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f, 1.0f, 1.0f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);
		m_particletimer = .5f;
		break;
	}
}

void Player::DeadCheck()
{
	if (m_hp <= 0)
	{
		g_scene->Change(GAMEOVER);
	}
}

void Player::Charge()
{
	if (m_mp < m_maxmp)
	{
		m_mp_charge += m_mp_charge_delta;
		if (m_mp_charge >= 1.0f)
		{
			m_mp_charge = 0.0f;
			m_mp++;
		}
	}

	if (m_hp < m_maxhp)
	{
		m_hp_charge += m_hp_charge_delta;
		if (m_hp_charge >= 1.0f)
		{
			m_hp_charge = 0.0f;
			m_hp++;
		}
	}
}

void Player::DeleteCheck()
{
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}
}

void Player::MagicChange()
{
	if (Pad(0).IsTrigger(enButtonRB1))
	{
		m_magicNo++;
		if (WIND < m_magicNo) {
			m_magicNo = FIRE;
		}
		g_scene->GetMagic()->Change();
	}

	if (Pad(0).IsTrigger(enButtonLB1))
	{
		m_magicNo--;
		if (m_magicNo < FIRE) {
			m_magicNo = WIND;
		}

		g_scene->GetMagic()->Change();
	}
}

void Player::Magic()
{
	switch (g_scene->GetScenes())
	{
	case STAGE_T_BATTLE:
	case STAGE_1_BATTLE:
	case STAGE_2_BATTLE:
	case STAGE_3_BATTLE:
	case STAGE_4_BATTLE:
	case STAGE_5_BATTLE:
	{
		CVector3 dist = g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->GetLookPos();
		dist.Subtract(m_position);
		dist.y = 0.0f;

		CVector3 angle_pos;
		angle_pos.x = sin(CMath::DegToRad(m_angle));
		angle_pos.y = 0.0f;
		angle_pos.z = cos(CMath::DegToRad(m_angle));

		if (m_magic_mp[m_magicNo] <= m_mp)
		{
			if (dist.AngleBetween(angle_pos) < 30.0f)
			{
				if (!m_ismagic)
				{
					if (m_particle_charge == nullptr && m_particle == nullptr)
					{
						if (KeyInput().GetPad(0).IsTrigger(enButtonB))
						{
							m_animationStat = Animationmagic;
							m_animation.PlayAnimation(m_animationStat, 0.3f);
							m_ismagic = true;

							//�p�[�e�B�N���̐���
							m_particle_charge = NewGO<CParticleEmitter>(0);
							m_particle_charge->Init(m_random, g_gameCamera->GetCamera(),
							{
								"Assets/paticle/fx_Magiccircle_j.png",			//!<�e�N�X�`���̃t�@�Cw���p�X�B
								{ 1.0f, 0.0f, 0.0f },							//!<�����x�B
								0.7f,											//!<�����B�P�ʂ͕b�B
								0.7f,											//!<�������ԁB�P�ʂ͕b�B
								6.0f,											//!<�p�[�e�B�N���̕��B
								7.0f,											//!<�p�[�e�B�N���̍����B
								{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
								{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
								{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
								{
									{ 0.0f, 0.0f, 0.25f,0.5f },//0.25,0.5,0.75,1U��V�̈ʒu
									{ 0.0f, 0.0f, 0.0f, 0.0f },//X,Y,X,Y
									{ 0.0f, 0.0f, 0.0f, 0.0f },
									{ 0.0f, 0.0f, 0.0f, 0.0f }
								},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
								1,												//!<UV�e�[�u���̃T�C�Y�B
								{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
								true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
								0.3f,											//!<�t�F�[�h���鎞�ԁB
								2.0f,											//!<�����A���t�@�l�B
								true,											//!<�r���{�[�h�H
								3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
								0,												//!<0�����������A1���Z�����B
								{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
							},
								GetLookPos());
							m_particletimer_charge = 0.7f;
						}
					}
				}
				if (!m_animation.IsPlay() && m_ismagic)
				{
					m_mp -= m_magic_mp[m_magicNo];
					Particle();
					g_scene->GetEnemy()->GetNearestEnemy(m_position, 0)->SetDamage(m_magic_mp[m_magicNo]);
					m_ismagic = false;
				}
			}
		}
	}
	break;
	default:
		break;
	}

}