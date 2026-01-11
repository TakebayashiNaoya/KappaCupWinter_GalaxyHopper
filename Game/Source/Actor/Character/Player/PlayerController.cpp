/**
 * PlayerController.cpp
 * コントローラー入力をプレイヤーの動きに変換する
 */
#include "stdafx.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerStateMachine.h"
#include "Source/Actor/ActorStatus.h"


namespace app
{
	namespace actor
	{
		namespace
		{
			/**
			* ベクトル vector を法線 normal の接平面へ投影（接線成分を取り出す）
			* Dot(vector, normal) は vector と normal の内積 → vector の中で n 方向にどれだけ成分があるか。
			* normal * Dot(vector, normal) はその成分を normal 方向に戻したベクトル。
			* vector - (その成分) → n方向の成分を引いて、残りを返す → 結果は n に直交する平面上のベクトル（接線）
			*/
			static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& normal)
			{
				return vector - normal * Dot(vector, normal);
			}

			/**
			 * 移動方向を計算する
			 */
			const Vector3 CalcMoveDirection(PlayerStateMachine* targetStateMachine)
			{
				/** スティックの入力を取得 */
				Vector3 stickL = Vector3::Zero;
				stickL.x = g_pad[0]->GetLStickXF();
				stickL.y = g_pad[0]->GetLStickYF();

				/** 入力がなければゼロベクトルを返す */
				if (stickL.x <= 0.01f && stickL.y <= 0.01f) {
					return Vector3::Zero;
				}

				/** カメラの向きから正面を取得 */
				Vector3 forward = Vector3::Zero;
				forward = g_camera3D->GetForward();
				forward = ProjectOnPlane(forward, targetStateMachine->GetUpDirection());
				forward.Normalize();

				/** カメラの向きから右を取得 */
				Vector3 right = Vector3::Zero;
				right = g_camera3D->GetRight();
				right = ProjectOnPlane(right, targetStateMachine->GetUpDirection());
				right.Normalize();

				/** 移動方向を算出 */
				Vector3 direction = forward * stickL.y + right * stickL.x;
				direction.Normalize();

				return direction;
			}
		}


		PlayerController::PlayerController()
		{
		}


		PlayerController::~PlayerController()
		{
		}


		bool PlayerController::Start()
		{
			m_stateMachine = m_ownerPlayer->GetStateMachine<PlayerStateMachine>();
			m_playerStatus = m_ownerPlayer->GetStatus<PlayerStatus>();
			return true;
		}


		void PlayerController::Update()
		{
			if (m_ownerPlayer == nullptr) {
				return;
			}

			/** 入力がブロックされていたら何もしない */
			if (m_stateMachine->IsInputBlocked()) {
				return;
			}

			/** 着地時にAボタンを押した瞬間、ジャンプ初速を設定する */
			if (m_stateMachine->IsOnGround() && g_pad[0]->IsTrigger(enButtonA)) {
				m_stateMachine->SetInitialJumpSpeed(m_playerStatus->GetJumpPower());
			}

			/** Bボタンを押している間ダッシュ */
			m_stateMachine->SetIsDash(g_pad[0]->IsPress(enButtonB));

			/** Lスティック入力があれば移動方向を設定する */
			m_stateMachine->SetMoveDirection(CalcMoveDirection(m_stateMachine));
		}

	}
}