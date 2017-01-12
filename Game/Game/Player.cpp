#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player *g_play;
CRandom random;

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

	m_hp	= 100;
	m_maxhp = 100;
	m_mp	= 100;
	m_maxmp = 100;
	random.Init((unsigned int) + time(NULL));
	m_magicNo = 0;
	m_ismagic = false;
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
	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}
	if (KeyInput().GetPad(0).IsTrigger(enButtonRB2))
	{
		m_magicNo++;
	}
	if (m_magicNo > WIND) {
		m_magicNo = FIER;
	}
	CVector3 m_oldpos;
	m_oldpos = m_position;

	//if (m_ismagic == true&&m_oldpos != m_position) {//���@���ړ��Ȃǂł��Ȃ��悤�ɂ���

	//	m_position = m_oldpos;

	//}

	if (m_ismagic == false) {
		if (KeyInput().GetPad(0).IsTrigger(enButtonA))
		{

			m_animationStat = Animationmagic;
			m_animation.PlayAnimation(m_animationStat, 0.3f);
			m_ismagic = true;
		}
		
	}

		if (m_animation.IsPlay() == false &&m_ismagic==true){

			paticle();
			m_ismagic = false;
		}
	
	
	Move();

	m_animation.Update(2.0 / 60.0f);

	//���[���h�s��̍X�V�B
	m_skinModel.Update(m_position,m_rotation, m_scale);
	
}


void Player::Move()
{
	//�L�����N�^�[�̈ړ����x������B
	CVector3 move = m_characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 10.0f;
	move.z = -Pad(0).GetLStickYF() * 10.0f;

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//�����x�N�g��
	moveXZ.y = 0.0f;

	float    LenXZ = moveXZ.Length();

	if (LenXZ > 0.0f)
	{
		if (m_animationStat != AnimationWalk&&m_ismagic == false)
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
		move.x = LenXZ * sin(CMath::DegToRad(m_angle));
		move.z = LenXZ * cos(CMath::DegToRad(m_angle));

		if (m_particle != nullptr)
		{
			DeleteGO(m_particle);//�p�[�e�B�N���̏���
			m_particle = nullptr;
		}
	}
	else
	{
		
		if (m_animationStat != AnimationStand&&m_ismagic==false)
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
	if (KeyInput().GetPad(0).IsPress(enButtonLB3) && m_characterController.IsOnGround())
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

void Player::paticle() {
	switch (m_magicNo) {
	case FIER:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.8f,											//!<�����B�P�ʂ͕b�B
			0.8f,											//!<�������ԁB�P�ʂ͕b�B
			7.0f,											//!<�p�[�e�B�N���̕��B
			7.0f,											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
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
			m_position);
		break;
	case SUNDER:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/Sunder2.tga",				//!<�e�N�X�`���̃t�@�Cw���p�X�B
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
			m_position);
		break;
	case ICE:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/ice.tga",//!<�e�N�X�`���̃t�@�Cw���p�X�B
			{ 0.0f, 0.0f, 1.0f },								//!<�����x�B
			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			4.0f,											//!<�p�[�e�B�N���̕��B
			4.0f,											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f, 0.5f, 0.5f },//0.25,0.5,0.75,1U��V�̈ʒu
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
			m_position);
		break;
	case AQUA:
			//�p�[�e�B�N���̐���
			m_particle = NewGO<CParticleEmitter>(0);
			m_particle->Init(random, g_gameCamera->GetCamera(),
			{
				"Assets/paticle/aqua.png",				//!<�e�N�X�`���̃t�@�Cw���p�X�B
				{ 0.0f, 0.0f, 0.0f },								//!<�����x�B
				0.4f,											//!<�����B�P�ʂ͕b�B
				0.4f,											//!<�������ԁB�P�ʂ͕b�B
				8.0f,											//!<�p�[�e�B�N���̕��B
				7.0f,											//!<�p�[�e�B�N���̍����B
				{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
				{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
				{ 0.0f, 0.0f, 0.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
				{
					{ 0.0f, 0.0f, 0.25f,0.25f },//0.25,0.5,0.75,1U��V�̈ʒu
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
				m_position);
			break;
	case WIND:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<�e�N�X�`���̃t�@�Cw���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			4.0f,											//!<�p�[�e�B�N���̕��B
			4.0f,											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
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
		m_position);
		break;
	}
}
