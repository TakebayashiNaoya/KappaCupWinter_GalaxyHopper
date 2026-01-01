/**
 * Spawner.cpp
 * エネミーをリスポーンさせるスポナーの実装
 */
#include "stdafx.h"
#include "Spawner.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Enemy/EnemyStateMachine.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			constexpr float RESPAWN_TIME = 5.0f;
		}

		Spawner::Spawner()
		{
		}

		Spawner::~Spawner()
		{
		}

		bool Spawner::Start()
		{
			m_deformEnemy = NewGO<DeformEnemy>(0, "DeformEnemy");
			battle::BattleManager::GetInstance()->Register(m_deformEnemy);
			m_deformEnemy->SetTransform(m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);
			return true;
		}

		void Spawner::Update()
		{
			if (battle::BattleManager::IsResultSequence()) {
				return;
			}

			/** エネミーが存在しているなら、そのエネミーが死んでいるか確認する */
			if (m_deformEnemy != nullptr)
			{
				/** 死んでいたらポインタを手放す（削除はBattleManagerが行う） */
				if (m_deformEnemy->ShouldDestroy()) {
					m_deformEnemy = nullptr;
				}
			}
			/** エネミーがいない（死んだ後）なら、リスポーンタイマーを動かす */
			else
			{
				m_respawnTimer += g_gameTime->GetFrameDeltaTime();

				if (m_respawnTimer > RESPAWN_TIME) {
					m_deformEnemy = NewGO<DeformEnemy>(0, "DeformEnemy");
					battle::BattleManager::GetInstance()->Register(m_deformEnemy);
					m_deformEnemy->SetTransform(m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);
					m_respawnTimer = 0.0f;
				}
			}
		}
	}
}