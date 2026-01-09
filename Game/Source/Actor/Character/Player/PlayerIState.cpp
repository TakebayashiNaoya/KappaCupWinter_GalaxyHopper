/**
 * PlayerIState.cpp
 * プレイヤーの各ステート実装
 */
#include "stdafx.h"
#include "Player.h"
#include "PlayerIState.h"
#include "PlayerStateMachine.h"


 /** ステートマシンを取得するマクロ */
#define machine GetStateMachine<PlayerStateMachine>()


namespace app
{
	namespace actor
	{
		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			machine->PlayAnimation(Player::EnPlayerAnimClip::Idle);
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
			machine->PlayAnimation(Player::EnPlayerAnimClip::Walk);
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
			machine->PlayAnimation(Player::EnPlayerAnimClip::Dash);
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
			machine->PlayAnimation(Player::EnPlayerAnimClip::Jump);
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
			machine->PlayAnimation(Player::EnPlayerAnimClip::Damage);
			/** 入力をはじく */
			machine->SetIsInputBlocked(true);
			/** タイマーリセット */
			m_damageTimer = 0.0f;

			machine->SetMoveDirection(machine->GetKnockBackDirection());
		}


		void PlayerDamageState::Update()
		{
			/** タイマーの更新 */
			m_damageTimer += g_gameTime->GetFrameDeltaTime();

			/** 時間比率の算出 */
			float timeRatio = m_damageTimer / machine->GetStatus()->GetKnockbackDuration();
			if (timeRatio > 1.0f) {
				timeRatio = 1.0f;
			}

			/** ノックバック速度を算出 */
			float moveSpeed = machine->GetStatus()->GetKnockbackPower() * (1.0f - timeRatio);
			if (m_damageTimer >= machine->GetStatus()->GetKnockbackDuration()) {
				moveSpeed = 0.0f;
			}

			/** ノックバック速度の適用 */
			machine->SetMoveSpeed(moveSpeed);
		}


		void PlayerDamageState::Exit()
		{
			/** 入力を受け付ける */
			machine->SetIsInputBlocked(false);
			/** 念のためノックバックの向きを初期化 */
			machine->SetKnockBackDirection(Vector3::Zero);
		}




		/********************************/


		void PlayerDyingState::Enter()
		{
			/** 死亡アニメーション */
			machine->PlayAnimation(Player::EnPlayerAnimClip::Die);
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