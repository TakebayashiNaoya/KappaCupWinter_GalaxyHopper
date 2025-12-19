/**
 * StateMachine.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachine.h"
#include "Character.h"

namespace
{
	/** 物理挙動に関する定数 */
	constexpr float GRAVITY_POWER = 9.8f * 10;				/** 重力						   */
	constexpr float	WALKABLE_SLOPE_LIMIT = Math::PI * 0.4f; /** 登れる角度の限界			   */
	constexpr float	CHAR_RADIUS = 15.0f;					/** キャラクターの半径（体の厚み） */
	constexpr float	SKIN_WIDTH = 1.0f;						/** 壁との接触時の余白			   */
	constexpr float	RECOVERY_BUFFER = 1.0f;					/** 埋まりからの押し出し補正量	   */
	constexpr float	SLIDE_ANTI_STICK = 0.1f;				/** 壁への張り付き防止用オフセット */

	/** レイキャスト・判定に関する定数 */
	constexpr float BACK_CHECK_DIST = 5.0f;					/** 埋まり防止の引き撃ち距離						*/
	constexpr float WALL_CHECK_RAY_HEIGHT = 30.0f;			/** 水平移動チェック時のレイの高さ（腰の高さ想定）	*/
	constexpr float VERTICAL_RAY_START_HEIGHT = 30.0f;		/** 垂直移動チェック時の開始位置の高さ				*/
	constexpr float VERTICAL_RAY_END_BUFFER = 5.0f;			/** 垂直レイの終端バッファ						    */
	constexpr float GROUND_CHECK_START_OFFSET = 5.0f;		/** 接地判定レイの開始オフセット					*/
	constexpr float GROUND_CONTACT_THRESHOLD = 2.0f;		/** 接地とみなす地面との距離						*/

	/** 計算・閾値に関する定数 */
	constexpr float MIN_MOVE_EPSILON = 0.01f;				/** 移動とみなす最小の長さ	*/
	constexpr float DOT_CLAMP_MAX = 1.0f;					/** 内積のクランプ最大値	*/
	constexpr float DOT_CLAMP_MIN = -1.0f;					/** 内積のクランプ最小値	*/


	/**
	 * 内積値のクランプ関数
	 */
	void Clamp(float& dot)
	{
		if (dot > DOT_CLAMP_MAX) {
			dot = DOT_CLAMP_MAX;
		}
		if (dot < DOT_CLAMP_MIN) {
			dot = DOT_CLAMP_MIN;
		}
	}


	/**
	 * レイキャストのコールバッククラス
	 */
	struct MyRayResultCallback : public btCollisionWorld::RayResultCallback
	{
		Vector3 hitPos;					/** rayが当たった位置。									*/
		Vector3 hitNormal;				/** rayが当たったポリゴンの法線。						*/
		Vector3 rayStart;				/** rayの開始位置。										*/
		Vector3 rayEnd;					/** rayの終了位置。										*/
		Vector3 upDirection;			/** 上方向ベクトル。									*/
		bool	isHit = false;			/** 当たったかどうか。									*/
		float	dist = FLT_MAX;			/** 当たった距離の最小値。								*/
		float	maxHitAngle = Math::PI;	/** 検知する最大角度（デフォルトは180度＝すべて検知）	*/

		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			/** 地面以外に当たった場合は無視します。 */
			if (rayResult.m_collisionObject->getCollisionFlags() != enCollisionAttr_Ground) {
				return 1.0f;
			}

			/**
			 * ポインタキャストで法線の取得します。
			 * NOTE: 無理やり型を変換してコピーするため、安全ではない書き方なので注意してください。
			 */
			Vector3 hitNormalTmp = *(Vector3*)&rayResult.m_hitNormalLocal;

			// 安全な書き方（メンバーごとのコピー）
			//btVector3& btVec = rayResult.m_hitNormalLocal;
			//Vector3 hitNormalTmp;
			//hitNormalTmp.x = btVec.x();
			//hitNormalTmp.y = btVec.y();
			//hitNormalTmp.z = btVec.z();

			float dot = hitNormalTmp.Dot(upDirection);
			Clamp(dot);

			/** 角度計算 */
			float angle = acosf(dot);
			angle = fabsf(angle);

			/** 変数(maxHitAngle)と比較します。 */
			if (angle < maxHitAngle)
			{
				isHit = true;
				Vector3 hitPosTmp;
				hitPosTmp.Lerp(rayResult.m_hitFraction, rayStart, rayEnd);
				Vector3 vDist = hitPosTmp - rayStart;
				float distTmp = vDist.Length();

				/** 最小距離の更新。 */
				if (dist > distTmp) {
					hitPos = hitPosTmp;
					hitNormal = hitNormalTmp;
					dist = distTmp;
				}
			}
			return rayResult.m_hitFraction;
		}
	};

	/**
	 * 指定した開始点から終了点までレイを飛ばし、最小距離かつ条件を満たす衝突点を検出します。
	 * 内部で `MyRayResultCallback` を使い、`upDirection` と法線のなす角が `maxAngle` 以下のもののみをヒットとして扱います。
	 * また、開始点と終了点がほぼ同一の場合は処理を行わず false を返します。
	 */
	bool RayTest(
		const Vector3& rayStart,	/** レイの開始位置 */
		const Vector3& rayEnd,		/** レイの終了位置 */
		Vector3& hitPosition,		/** ヒットした位置の出力先 */
		Vector3& outNormal,			/** ヒットした法線の出力先 */
		const Vector3& upDirection,	/** 上方向ベクトル */
		float maxAngle = Math::PI	/** 検知する最大角度 (デフォルトは180度＝すべて検知) */
	)
	{
		if ((rayStart - rayEnd).LengthSq() <= MIN_MOVE_EPSILON) {
			return false;
		}

		MyRayResultCallback rayCallback;
		rayCallback.rayStart = rayStart;
		rayCallback.rayEnd = rayEnd;
		rayCallback.upDirection = upDirection;
		rayCallback.maxHitAngle = maxAngle;

		PhysicsWorld::GetInstance()->RayTest(rayStart, rayEnd, &rayCallback);
		if (rayCallback.isHit) {
			hitPosition = rayCallback.hitPos;
			outNormal = rayCallback.hitNormal;
			return true;
		}
		return false;
	}
}


namespace app
{
	namespace actor
	{
		StateMachineBase::~StateMachineBase()
		{
			/** メモリ解放 */
			for (auto& pair : m_stateMap) {
				/** マップに登録されているステートを削除 */
				delete pair.second;
			}
			/** 入れ物自体を消去 */
			m_stateMap.clear();
		}


		void StateMachineBase::Update()
		{
			/** ステートの切り替え */
			ChangeState();
			/** 現在のステートの更新 */
			m_currentState->Update();
		}


		void StateMachineBase::ChangeState()
		{
			/** 切り替え先のステートを取得 */
			m_nextState = GetChangeState();
			/**
			 * ステートが切り替わった時（m_nextStateがnullptrじゃない時）かつ、
			 * 今のステートと次のステートが同じではないとき
			 */
			if (m_nextState != nullptr && m_currentState != m_nextState) {
				/** 今のステートを終了 */
				m_currentState->Exit();
				/** 新しいステートに変更 */
				m_currentState = m_nextState;
				/** 新しいステートを開始 */
				m_currentState->Enter();
				/** 次のステートを無にする */
				m_nextState = nullptr;
			}
		}


		IState* StateMachineBase::FindState(const int stateId)
		{
			/** 指定したIDのステートが存在すればそのステートのポインタを返し、なければnullptrを返す */
			auto it = m_stateMap.find(stateId);
			if (it != m_stateMap.end()) {
				return it->second;
			}
			return nullptr;
		}


		bool StateMachineBase::CanChangeWalk() const
		{
			if (m_moveDirection.Length() > MIN_MOVE_EPSILON) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDush() const
		{
			if (m_isDash && m_moveDirection.Length() > MIN_MOVE_EPSILON) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDamage()
		{
			Character* character = GetOwner<Character>();
			bool isDamage = character->GetStatus()->IsDamage();
			if (isDamage) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDying()
		{
			/** HPが0ならtrueを返します。 */
			Character* character = GetOwner<Character>();
			const uint8_t m_currentHp = character->GetStatus()->GetHp();
			if (m_currentHp == 0) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDead()
		{
			/** HPが0かつ、アニメーションが終了している場合にtrueを返します。 */
			Character* character = GetOwner<Character>();
			const uint8_t m_currentHp = character->GetStatus()->GetHp();
			const bool isPlayingAnimation = character->GetModelRender()->IsPlayingAnimation();
			if (m_currentHp == 0 && isPlayingAnimation == false) {
				return true;
			}
			return false;
		}


		bool StateMachineBase::IsOnGround()
		{
			/**
			 * 移動処理でhitPositionをm_positionに代入しており、レイの判定が不安定になるため、
			 * rayStartをm_positionより少し上にする。
			 */
			Vector3 rayStart = m_position + m_upDirection * GROUND_CHECK_START_OFFSET;
			Vector3 rayEnd = Vector3::Zero;
			Vector3 hitPosition = Vector3::Zero;

			if (PhysicsWorld::GetInstance()->RayTest(rayStart, rayEnd, hitPosition)) {
				Vector3 DistanceToGround = m_position - hitPosition;
				if (DistanceToGround.Length() < GROUND_CONTACT_THRESHOLD) {
					return true;
				}
				return false;
			}
			return false;
		}


		void StateMachineBase::Move()
		{
			/** 水平方向の速度 */
			Vector3 horizontalVelocity = m_moveDirection * m_moveSpeed;

			/** 垂直方向の速度 */
			m_fallTimer += g_gameTime->GetFrameDeltaTime();
			float jumpPower = m_initialJumpSpeed - (GRAVITY_POWER * m_fallTimer);
			Vector3 verticalVelocity = m_upDirection * jumpPower;


			/**
			 * 水平移動処理
			 */
			if (horizontalVelocity.LengthSq() > MIN_MOVE_EPSILON)
			{
				/**
				 * 壁にぶつからずに移動できるかを試みます
				 */
				Vector3 currentPos = m_position;				/** 現在の座標を保存しておきます */
				Vector3 attemptVelocity = horizontalVelocity;	/** 壁にぶつかった場合に、壁までのベクトルを格納する変数 */
				bool needSlide = false;							/** 横滑りが必要かどうかのフラグ */
				float moveDist = attemptVelocity.Length();

				/** 水平移動の方向ベクトルを保存 */
				Vector3 horizontalDirection = attemptVelocity;
				horizontalDirection.Normalize();

				/** 足元からレイを飛ばすと段差に引っかかるので、少し高い位置（腰など）から飛ばす */
				Vector3 rayOriginOffset = m_upDirection * WALL_CHECK_RAY_HEIGHT;
				/**
				 * startPos：現在地から少し「後ろ」に引いた座標。
				 * NOTE：すでに壁に少しめり込んでいた場合、現在地から飛ばすと壁の裏側から飛ばすことになり、検知できないため。
				 */
				Vector3 startPos = currentPos + rayOriginOffset - (horizontalDirection * BACK_CHECK_DIST);
				/*
				 * checkLength：レイの長さ。
				 * 式：引き撃ち分 + 移動したい距離 + 体の半径 + 余白
				 * NOTE：中心が壁に到達する前に止めたいので、「体の半径分」余分に先読みする必要があります。
				 */
				float checkLength = BACK_CHECK_DIST + moveDist + CHAR_RADIUS + SKIN_WIDTH;
				/** endPos：レイの終点 */
				Vector3 endPos = startPos + (horizontalDirection * checkLength);
				/** rayが当たった座標を受け取る変数と、rayが当たったポリゴンの法線を受け取る変数を用意 */
				Vector3 hitPos, hitNormal;

				if (RayTest(startPos, endPos, hitPos, hitNormal, m_upDirection))
				{
					/**
					 * 壁までの距離を算出。
					 * distFromCurrent: 「本来の現在地（中心）」から「壁の表面」までの距離
					 * 計算式：(レイの全長 - 引き撃ち分)
					 */
					float distFromCurrent = (hitPos - startPos).Length() - BACK_CHECK_DIST;
					/**
					 * availableDistance: 「実際に進める距離」
					 * 計算式: 壁までの距離 - 体の半径
					 * NOTE：体の表面が壁に触れるところで止めるため。
					 */
					float availableDistance = distFromCurrent - CHAR_RADIUS;

					/**
					 * 埋まったとき（体の表面の座標が壁の裏側になったとき）に、押し出す処理。
					 * 法線方向に、埋まっている分と、少し余分に押し出す。
					 */
					if (availableDistance < 0.0f) {
						float penetrationDepth = -availableDistance;
						currentPos += hitNormal * (penetrationDepth + RECOVERY_BUFFER);
						availableDistance = 0.0f;
					}

					/** upとrayが当たったポリゴンの法線との角度をクランプ・計算する */
					float dot = hitNormal.Dot(m_upDirection);
					Clamp(dot);
					float slopeAngle = acosf(dot);

					/** 角度が登れる角度よりも急なら「壁」とみなす */
					if (slopeAngle > WALKABLE_SLOPE_LIMIT)
					{
						/** 壁の手前まで移動 */
						float actualMove = max(0.0f, availableDistance - SKIN_WIDTH);
						Vector3 moveVec = horizontalDirection * actualMove;
						currentPos += moveVec;

						/** 本来の移動ベクトルから、実際に移動した分を引き、移動できなかった分を計算する */
						Vector3 currentRemaining = attemptVelocity - moveVec;

						/** 移動できなかった分を、法線方向に投影して引き算を行う */
						float d = currentRemaining.Dot(hitNormal);
						if (d < 0.0f) {
							attemptVelocity = currentRemaining - hitNormal * d;
							/** 張り付き防止に少しだけ法線方向に移動させる */
							attemptVelocity += hitNormal * SLIDE_ANTI_STICK;
						}
						else {
							attemptVelocity = currentRemaining;
						}

						/** 滑り移動を行うフラグを立てる */
						needSlide = true;
					}
					else {
						/** 登れるのでそのまま進んで終了 */
						currentPos += attemptVelocity;
						needSlide = false;
					}
				}
				else {
					/** 障害物がないので、そのまま進んで終了 */
					currentPos += attemptVelocity;
					needSlide = false;
				}



				/**
				 * 直前の移動で滑り処理が必要になった場合、滑り先のチェックを行う
				 * 途中までは直前の処理と同じ
				 */
				if (needSlide && attemptVelocity.LengthSq() > MIN_MOVE_EPSILON)
				{
					moveDist = attemptVelocity.Length();
					Vector3 attemptDirection = attemptVelocity;
					attemptDirection.Normalize();

					Vector3 rayOriginOffset = m_upDirection * WALL_CHECK_RAY_HEIGHT;
					Vector3 startPos = currentPos + rayOriginOffset - (attemptDirection * BACK_CHECK_DIST);
					float checkLength = BACK_CHECK_DIST + moveDist + CHAR_RADIUS + SKIN_WIDTH;
					Vector3 endPos = startPos + (attemptDirection * checkLength);
					Vector3 hitPos, hitNormal;

					if (RayTest(startPos, endPos, hitPos, hitNormal, m_upDirection))
					{
						float distFromCurrent = (hitPos - startPos).Length() - BACK_CHECK_DIST;
						float availableDistance = distFromCurrent - CHAR_RADIUS;

						if (availableDistance < 0.0f) {
							float penetrationDepth = -availableDistance;
							currentPos += hitNormal * (penetrationDepth + RECOVERY_BUFFER);
							availableDistance = 0.0f;
						}

						float dot = hitNormal.Dot(m_upDirection);
						Clamp(dot);
						float slopeAngle = acosf(dot);

						if (slopeAngle > WALKABLE_SLOPE_LIMIT) {
							/** 壁の手前まで移動して停止 */
							float actualMove = max(0.0f, availableDistance - SKIN_WIDTH);
							currentPos += attemptDirection * actualMove;
						}
						else {
							/** 坂とみなし、登る */
							currentPos += attemptVelocity;
						}
					}
					else {
						/** 障害物がないので、そのままスライド移動完了 */
						currentPos += attemptVelocity;
					}
				}
				/** 最終位置を確定 */
				m_position = currentPos;
			}


			/**
			 * 垂直移動処理
			 */
			Vector3 rayStartPos = m_position + m_upDirection * VERTICAL_RAY_START_HEIGHT;
			Vector3 rayEndPos = m_position + verticalVelocity - (m_upDirection * VERTICAL_RAY_END_BUFFER);
			Vector3 hitPos, hitNormal;

			if (RayTest(rayStartPos, rayEndPos, hitPos, hitNormal, m_upDirection, Math::PI))
			{
				float dot = hitNormal.Dot(m_upDirection);
				Clamp(dot);
				float angle = acosf(dot);

				if (angle <= WALKABLE_SLOPE_LIMIT) {
					m_position = hitPos;
					/** 着地したので、ジャンプ関連の変数をリセット */
					m_initialJumpSpeed = 0.0f;
					m_fallTimer = 0.0f;
					verticalVelocity = Vector3::Zero;
				}
				else {
					m_position = hitPos;
					Vector3 slideVector = verticalVelocity - hitNormal * verticalVelocity.Dot(hitNormal);
					verticalVelocity = slideVector;
				}
			}
			else {
				m_position += verticalVelocity;
			}

			/** 微小な移動量なら、強制的にゼロにする */
			if (horizontalVelocity.Length() <= MIN_MOVE_EPSILON) {
				horizontalVelocity = Vector3::Zero;
			}
		}
	}
}