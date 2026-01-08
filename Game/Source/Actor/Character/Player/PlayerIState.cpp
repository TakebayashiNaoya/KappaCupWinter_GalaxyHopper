/**
 * PlayerIState.cpp
 * プレイヤーの各ステート実装
 */
#include "stdafx.h"
#include "Player.h"
#include "PlayerIState.h"
#include "PlayerStateMachine.h"


namespace app
{
	namespace actor
	{
		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			GetOwnerMachine<PlayerStateMachine>()->PlayAnimation(Player::EnPlayerAnimClip::Idle);
		}


		void PlayerIdleState::Update()
		{
		}


		void PlayerIdleState::Exit()
		{
		}




		/********************************/


		void PlayerWalkState::Enter()
		{
			/** 歩きアニメーション */
			GetOwnerMachine<PlayerStateMachine>()->PlayAnimation(Player::EnPlayerAnimClip::Walk);
		}


		void PlayerWalkState::Update()
		{
		}


		void PlayerWalkState::Exit()
		{
		}




		/********************************/


		void PlayerDashState::Enter()
		{
			/** 走りアニメーション */
			GetOwnerMachine<PlayerStateMachine>()->PlayAnimation(Player::EnPlayerAnimClip::Dash);
		}


		void PlayerDashState::Update()
		{
		}


		void PlayerDashState::Exit()
		{
		}




		/********************************/


		void PlayerJumpState::Enter()
		{
			/** ジャンプアニメーション */
			GetOwnerMachine<PlayerStateMachine>()->PlayAnimation(Player::EnPlayerAnimClip::Jump);
		}


		void PlayerJumpState::Update()
		{
		}


		void PlayerJumpState::Exit()
		{
		}




		/********************************/


		void PlayerDamageState::Enter()
		{
			/** 被弾アニメーション */
			GetOwnerMachine<PlayerStateMachine>()->PlayAnimation(Player::EnPlayerAnimClip::Damage);
			/** 入力をはじく */
			GetOwnerMachine<PlayerStateMachine>()->SetIsInputBlocked(true);
		}


		void PlayerDamageState::Update()
		{
			/** タイマーの更新 */
			m_damageTimer += g_gameTime->GetFrameDeltaTime();

			/** 時間比率の算出 */
			float timeRatio = m_damageTimer / m_status->GetKnockbackDuration();
			if (timeRatio > 1.0f) {
				timeRatio = 1.0f;
			}

			/** ノックバック速度を算出 */
			float moveSpeed = m_status->GetKnockbackPower() * (1.0f - timeRatio);
			if (m_damageTimer >= m_status->GetKnockbackDuration()) {
				moveSpeed = 0.0f;
			}

			/** ノックバック速度の適用 */
			m_stateMachine->SetMoveSpeed(moveSpeed);
		}


		void PlayerDamageState::Exit()
		{
			/** 入力を受け付ける */
			m_stateMachine->SetIsInputBlocked(false);
		}




		/********************************/


		void PlayerDyingState::Enter()
		{
			/** 死亡アニメーション */
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Die);
		}


		void PlayerDyingState::Update()
		{
		}


		void PlayerDyingState::Exit()
		{
		}




		/********************************/


		void PlayerDeadState::Enter()
		{
		}


		void PlayerDeadState::Update()
		{
		}


		void PlayerDeadState::Exit()
		{
		}
	}
}