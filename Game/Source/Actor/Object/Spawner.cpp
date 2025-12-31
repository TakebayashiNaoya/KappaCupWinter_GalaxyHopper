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
			if (battle::BattleManager::GetIsBattleFinish()) {
				return;
			}

			// エネミーが生きているかチェック
			if (m_deformEnemy != nullptr)
			{
				// 死んでいたら、ポインタを手放す（削除はBattleManagerがやってくれる）
				if (m_deformEnemy->GetStateMachine<DeformEnemyStateMachine>()->IsEqualCurrentState(DeformEnemyStateMachine::enDeformEnemyState_Dead)) {
					m_deformEnemy = nullptr;
				}
			}
			// エネミーがいない（死んだ後）なら、リスポーンタイマーを動かす
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