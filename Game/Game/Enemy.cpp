#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Scene.h"

Enemy::Enemy()
{
	m_position = { 0.0f,0.0f,0.0f };
	m_rotation = CQuaternion::Identity;
	m_scale = { 0.6f,0.6f,0.6f };
	m_radius = 0.5f;
	m_dead = false;

	m_filename = NULL;
	m_name = NULL;
	m_hp = 0;
	m_maxhp = 0;
	m_angle = 0.0f;
	m_attack_timer = 0.0f;

	m_characterController.Init(m_radius, 1.0f, m_position);

	m_random.Init((unsigned int)time(NULL));

	m_particle = nullptr;
}

Enemy::~Enemy()
{
}

void Enemy::Start(EneDat enedat, bool isBattle)
{
	m_filename = enedat.s_filename;
	m_name = enedat.s_name;
	m_hp = enedat.s_hp;
	m_maxhp = enedat.s_hp;
	m_position = enedat.s_pos;
	m_look_pos = enedat.s_look_pos;
	m_scale = enedat.s_scale;
	m_isBattle = isBattle;
	m_animationStat = AnimationStand;
	m_property = enedat.s_property;

	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", m_filename);

	SkinModelDataResources().Load(m_skinModelData, filePath, &m_animation);
	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&g_defaultLight);//�f�t�H���g���C�g��ݒ�B

	m_characterController.SetPosition(m_position);

	m_animation.SetAnimationLoopFlag(AnimationAttack, false);
	m_animation.SetAnimationLoopFlag(AnimationStand, false);
	m_animation.SetAnimationLoopFlag(Animationmagic, false);
	m_animation.SetAnimationLoopFlag(AnimationDamage, false);
}

void Enemy::Update()
{
	if (m_particle != nullptr && m_particletimer <= 0.0f)
	{
		DeleteGO(m_particle);
		m_particle = nullptr;
	}

	if (m_particletimer > 0.0f)
	{
		m_particletimer -= 1.0f / 60.0f;
	}

	if (m_position.y < 0.0f)
	{
		m_hp = 0;
	}

	if (m_dead)
	{
		m_characterController.RemoveRigidBoby();
		DeleteGO(this);
	}

	Move();
	m_skinModel.Update(m_position, m_rotation, m_scale);//���[���h�s��̍X�V�B
}

void Enemy::Move()
{
	CVector3 move = m_characterController.GetMoveSpeed();

	Player* player = g_scene->GetPlayer();

	if (m_isBattle && player != nullptr)
	{
		m_animation.Update(1.0 / 60.0f);

		CVector3 moveXZ = player->GetPos();
		moveXZ.Subtract(m_position);
		moveXZ.y = 0.0f;

		if (m_look_pos.y * m_scale.y / 1.25f < moveXZ.Length())
		{
			moveXZ.Normalize();
			moveXZ.Scale(2.0f);

			move.x = moveXZ.x;
			move.z = moveXZ.z;

			if (m_animationStat != AnimationWalk)
			{
				m_animationStat = AnimationWalk;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
			}
		}
		else
		{
			m_attack_timer += DELTA_TIME;

			move.Scale({ 0.0f,1.0f,0.0f });
			
			if (2.0f < m_attack_timer)
			{
				m_attack_timer = 0.0f;
				m_animationStat = AnimationAttack;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
				g_scene->GetPlayer()->SetDamage(100);
				Particle();
			}
			else if (m_animationStat != AnimationStand)
			{
				m_animationStat = AnimationStand;
				m_animation.PlayAnimation(m_animationStat, 0.3f);//�A�j���[�V�����̍Đ�
			}
		}
		//AxisZ��moveXZ�̂Ȃ��p�����߂�
		m_angle = moveXZ.AngleBetween(CVector3::AxisZ);

		if (moveXZ.x < 0.0f)
		{
			m_angle *= -1.0f;
		}
	}

	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	m_characterController.SetMoveSpeed(move);
	//�L�����N�^�[�R���g���[���[�����s�B
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();


	m_rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(m_angle));
}

void Enemy::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext,g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}

void Enemy::Delete()
{
	m_dead = true;
}

void Enemy::Particle() {
	if (m_particle != nullptr)
	{
		return;
	}
	if (m_animationStat == NORMAL)
	{
		return;
	}

	CVector3 target = g_scene->GetPlayer()->GetLookPos();

	switch (m_property) {
	case FIRE:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/burn.png",		//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.8f,											//!<�����B�P�ʂ͕b�B
			0.8f,											//!<�������ԁB�P�ʂ͕b�B
			17.0f,											//!<�p�[�e�B�N���̕��B
			17.0f,											//!<�p�[�e�B�N���̍����B
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
			{ 0.0f, 0.0f, 1.0f },								//!<�����x�B
			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f,											//!<�p�[�e�B�N���̕��B
			10.0f,											//!<�p�[�e�B�N���̍����B
			{ 1.0f, 1.0f, 0.0f },							//!<�����ʒu�̃����_�����B
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
			target);
		m_particletimer = 0.4f;
		break;
	case AQUA:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/aqua.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },								//!<�����x�B
			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f,											//!<�p�[�e�B�N���̕��B
			10.0f,											//!<�p�[�e�B�N���̍����B
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
			target);
		m_particletimer = 0.4f;
		break;
	case WIND:
		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/paticle/wind.tga",						//!<�e�N�X�`���̃t�@�Cw���p�X�B
			{ 1.0f, 0.0f, 0.0f },							//!<�����x�B

			0.4f,											//!<�����B�P�ʂ͕b�B
			0.4f,											//!<�������ԁB�P�ʂ͕b�B
			10.0f,											//!<�p�[�e�B�N���̕��B
			10.0f,											//!<�p�[�e�B�N���̍����B
			{ 1.0f, 1.0f, 0.0f },							//!<�����ʒu�̃����_�����B
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
			target);
		m_particletimer = 0.4f;
		break;
	}
}
