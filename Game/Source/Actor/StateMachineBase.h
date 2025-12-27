/**
 * StateMachineBase.h
 * 状態遷移を管理する基底クラス群
 */
#pragma once
#include <unordered_map>
#include <cstdint>
#include "ActorStatus.h"


namespace app
{
	namespace actor
	{
		class StateMachineBase;


		/**
		 * 状態の基底クラス（インターフェース）
		 */
		class IState
		{
		protected:
			/** ステートの持ち主（ステートマシン） */
			StateMachineBase* m_owner = nullptr;

		public:
			IState(StateMachineBase* owner) : m_owner(owner) {}
			virtual ~IState() {}

			/** 開始時に1回だけ呼ばれます。 */
			virtual void Enter() = 0;
			/** 毎フレーム呼ばれます（メイン処理）。 */
			virtual void Update() = 0;
			/** 終了時に1回だけ呼ばれます。 */
			virtual void Exit() = 0;

			/** 持ち主を型キャストして取得する便利関数 */
			template <typename T>
			T* GetOwner()
			{
				return static_cast<T*>(m_owner);
			}
		};


		/**
		 * ステートマシン本体
		 * 複数のステートを保持し、現在のステートを切り替えて実行します。
		 */
		class StateMachineBase
		{
		public:
			/**
			 * トランスフォームを取得
			 */
			inline Transform& GetTransform() { return m_transform; }
			/**
			 * 座標を設定
			 */
			inline void SetPosition(const Vector3& position) { m_transform.m_position = position; }
			/**
			 * 回転を設定
			 */
			inline void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }
			/**
			 * 拡縮を設定
			 */
			inline void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }

			/**
			 * 上方向ベクトルの取得
			 */
			inline const Vector3& GetUpDirection() const { return m_upDirection; }
			/**
			 * 上方向ベクトルの設定
			 */
			inline void SetUpDirection(const Vector3& upDir) { m_upDirection = upDir; }

			/**
			 * 移動方向の取得
			 */
			inline const Vector3& GetMoveDirection() const { return m_moveDirection; }
			/**
			 * 移動方向の設定
			 */
			inline void SetMoveDirection(const Vector3& moveDir) { m_moveDirection = moveDir; }

			/**
			 * 移動速度の取得
			 */
			inline float GetMoveSpeed() const { return m_moveSpeed; }
			/**
			 * 移動速度の設定
			 */
			inline void SetMoveSpeed(const float moveSpeed) { m_moveSpeed = moveSpeed; }

			/**
			 * 初速ジャンプ速度の取得
			 */
			inline float GetInitialJumpSpeed() const { return m_initialJumpSpeed; }
			/**
			 * 初速ジャンプ速度の設定
			 */
			inline void SetInitialJumpSpeed(const float initialJumpSpeed) { m_initialJumpSpeed = initialJumpSpeed; }

			/**
			 * ダッシュできるかの取得
			 */
			inline bool IsDash() const { return m_isDash; }
			/**
			 * ダッシュできるかの設定
			 */
			inline void SetDash(const bool isDash) { m_isDash = isDash; }

			/**
			 * 攻撃できるかの取得
			 */
			inline bool IsAttack() const { return m_isAttack; }
			/**
			 * 攻撃できるかの設定
			 */
			inline void SetAttack(const bool isAttack) { m_isAttack = isAttack; }


		protected:
			/** 全てのステートをID付きで保存する辞書 */
			std::unordered_map<int, IState*> m_stateMap;
			/** 現在実行中のステート */
			IState* m_currentState = nullptr;
			/** 次に変更するステート */
			IState* m_nextState = nullptr;

			/** トランスフォーム */
			Transform m_transform;

			/** 上方向ベクトル */
			Vector3 m_upDirection = Vector3::Up;
			/** 移動方向 */
			Vector3 m_moveDirection = Vector3::Zero;
			/** 移動速度（現在のフレーム） */
			float m_moveSpeed = 0.0f;
			/** 初速ジャンプ速度 */
			float m_initialJumpSpeed = 0.0f;

			/** ダッシュできるか */
			bool m_isDash = false;
			/** 攻撃できるか */
			bool m_isAttack = false;

			/** 落下している時間 */
			float m_fallTimer = 0.0f;

			/** ステートの持ち主（ステートマシンを持つゲームオブジェクト） */
			IGameObject* m_owner = nullptr;


		public:
			StateMachineBase(IGameObject* owner) : m_owner(owner) {};
			virtual ~StateMachineBase();

			/**
			 * 更新処理（ステートの切り替え判定と実行）
			 * これをIGameObjectを継承した持ち主のUpdateで呼び出してください。
			 * 必要に応じてオーバーライドしてもかまいません。
			 * 例: m_playerStateMachine->Update();
			 */
			virtual void Update();

			/** ステート変更 */
			void ChangeState();

			/**
			 * アニメーション再生
			 * 継承先のステートマシンでキャラクターを指定して実装してください。
			 */
			virtual void PlayAnimation(const int animationIndex) = 0;


		protected:
			/**
			 * ステートを追加するテンプレート関数
			 * 例: AddState<IdleState>(enState_Idle);
			 */
			template<typename TState>
			void AddState(const int stateId)
			{
				/** 登録済みなら、古いものを削除しておく（メモリリーク防止） */
				auto it = m_stateMap.find(stateId);
				if (it != m_stateMap.end()) {
					delete it->second;
					K2_ASSERT(false, "IDが重複しています。");
				}

				m_stateMap[stateId] = new TState(this);
			}

			/** 指定したIDのステートを取得します。 */
			IState* FindState(const int stateId);


		public:
			/** 持ち主を型キャストして取得する便利関数 */
			template <typename T>
			T* GetOwner()
			{
				return dynamic_cast<T*>(m_owner);
			}


		protected:
			/**
			 * 現在ステートが指定したステートならtrueを返します。
			 * 現在のステートが何かによって処理を分岐したい場合に使用します。
			 * 主にChangeState内で使用します。
			 */
			inline bool IsEqualCurrentState(const int state)
			{
				return m_currentState == m_stateMap[state];
			}
		public:
			/**
			 * 次のステートが指定したステートならtrueを返します。
			 * 次のステートが何かによって処理を分岐したい場合に使用します。
			 * 主に各IStateのExit内で使用します。
			 */
			inline bool IsEqualNextState(const int state)
			{
				return m_nextState == m_stateMap[state];
			}


		protected:
			/**
			 * 変更するステートを取得します。
			 * ステートの種類や、変更する条件は各クラスで異なるため、
			 * ここは派生クラスでオーバーライドして実装してください。
			 * この関数自体はStateMachineBaseのUpdate内で呼び出されているため、
			 * 派生先のUpdateで改めて呼び出す必要はありません。
			 */
			virtual IState* GetChangeState() = 0;

			/** 歩く状態に変更できるか */
			bool CanChangeWalk() const;
			/** 走る状態に変更できるか */
			bool CanChangeDush() const;
			/** ダメージ状態に変更できるか */
			bool CanChangeDamage();
			/** 死に始める状態に変更できるか */
			bool CanChangeDying();
			/** 完全に死んだ状態に変更できるか */
			bool CanChangeDead();


		public:
			/** 地面に接地しているか */
			bool IsOnGround();

			/**
			 * ベクトル v を法線 n の接平面へ投影（接線成分を取り出す）
			 * Dot(v, n) は v と n の内積 → v の中で n 方向にどれだけ成分があるか。
			 * n * Dot(v, n) はその成分を n 方向に戻したベクトル。
			 * v - (その成分) → n方向の成分を引いて、残りを返す → 結果は n に直交する平面上のベクトル（接線）
			 */
			static Vector3 ProjectOnPlane(const Vector3& v, const Vector3& n)
			{
				return v - n * Dot(v, n);
			}



			/**
			 * 移動処理
			 * ※呼び出す前に必ずm_upDirection、m_moveDirection、m_moveSpeedを設定すること
			 * なお、m_initialJumpSpeedを設定したら、ジャンプ処理も行われます。
			 */
			void ProcessMovement();


		private:
			/**
			 * 移動速度（水平・垂直）を計算します
			 */
			void ComputeVelocity(Vector3& outHorizontalVel, Vector3& outVerticalVel);

			/**
			 * 指定した速度での移動を試みます（レイ判定・埋まり補正・壁判定込み）
			 * @param startPos  開始座標
			 * @param velocity  移動したいベクトル
			 * @param outIsWall 壁に当たって止まったか（出力）
			 * @param outNormal 当たった壁の法線（出力）
			 * @return 移動後の座標
			 */
			Vector3 ExecuteMoveCheck(const Vector3& startPos, const Vector3& velocity, bool& outIsWall, Vector3& outNormal);

			/**
			 * 壁に沿った滑りベクトルを計算します
			 */
			Vector3 ComputeSlideVector(const Vector3& velocity, const Vector3& normal);

			/**
			 * 水平移動後の座標を計算して返します
			 */
			Vector3 CalculateHorizontalMove(const Vector3& currentPos, const Vector3& velocity);

			/**
			 * 垂直移動後の座標を計算して返します
			 */
			Vector3 CalculateVerticalMove(const Vector3& currentPos, Vector3& velocity);

			/**
			 * 次の回転姿勢を計算して返します
			 */
			Quaternion CalculateRotation(const Quaternion& currentRot, const Vector3& velocity);
		};
	}
}