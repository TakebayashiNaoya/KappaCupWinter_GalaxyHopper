/**
 * PlayerIState.cpp
 * プレイヤーの各ステート実装
 */
#include "stdafx.h"
#include "PlayerIState.h"
#include "Player.h"
#include "PlayerStateMachine.h"


namespace app
{
	namespace actor
	{
		/** ステートマシン、プレイヤー、ステータスをキャッシュ */
		PlayerStateBase::PlayerStateBase(PlayerStateMachine* machine, Player* player, PlayerStatus* status)
			: m_stateMachine(machine)
			, m_player(player)
			, m_status(status)
		{
		}




		/********************************/


		void PlayerIdleState::Enter()
		{
			/** 待機アニメーション */
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Idle);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Walk);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Dash);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Jump);
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
			m_stateMachine->PlayAnimation(Player::EnPlayerAnimClip::Damage);
			/** 入力をはじく */
			m_stateMachine->SetIsInputBlocked(true);
		}


		void PlayerDamageState::Update()
		{
			// 定数の定義（ヘッダーや定数ファイルにあると想定）
			const float KNOCKBACK_INITIAL_SPEED = 15.0f; // 初速
			const float DAMAGE_DURATION = 1.0;      // ダメージ状態の継続時間（秒）

			/** タイマーの更新 */
			m_damageTimer += g_gameTime->GetFrameDeltaTime();

			/** 時間比率の算出 */
			float timeRatio = m_damageTimer / DAMAGE_DURATION;
			if (timeRatio > 1.0f) {
				timeRatio = 1.0f;
			}

			/** ノックバック速度を算出 */
			float moveSpeed = KNOCKBACK_INITIAL_SPEED * (1.0f - timeRatio);
			if (m_damageTimer >= DAMAGE_DURATION) {
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