/**
 * StateMachineBase.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachineBase.h"
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
			bool isDamage = character->GetStatus<CharacterStatus>()->IsDamage();
			if (isDamage) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDying()
		{
			/** HPが0ならtrueを返します。 */
			Character* character = GetOwner<Character>();
			const uint8_t m_currentHp = character->GetStatus<CharacterStatus>()->GetHp();
			if (m_currentHp <= 0) {
				return true;
			}
			return false;
		}

		bool StateMachineBase::CanChangeDead()
		{
			/** HPが0かつ、アニメーションが終了している場合にtrueを返します。 */
			Character* character = GetOwner<Character>();
			const uint8_t m_currentHp = character->GetStatus<CharacterStatus>()->GetHp();
			const bool isPlayingAnimation = character->GetModelRender()->IsPlayingAnimation();
			if (m_currentHp <= 0 && isPlayingAnimation == false) {
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
			Vector3 rayStart = m_transform.m_position + m_upDirection * GROUND_CHECK_START_OFFSET;
			Vector3 rayEnd = Vector3::Zero;
			Vector3 hitPosition = Vector3::Zero;

			if (PhysicsWorld::GetInstance()->RayTest(rayStart, rayEnd, hitPosition)) {
				Vector3 DistanceToGround = m_transform.m_position - hitPosition;
				if (DistanceToGround.Length() < GROUND_CONTACT_THRESHOLD) {
					return true;
				}
				return false;
			}
			return false;
		}


		void StateMachineBase::ComputeVelocity(Vector3& outHorizontalVel, Vector3& outVerticalVel)
		{
			// 1. 水平方向
			// 球体対応：移動ベクトルを接平面に沿わせる
			Vector3 tangentVelocity = ProjectOnPlane(m_moveDirection, m_upDirection);
			if (tangentVelocity.LengthSq() > 0.001f) {
				tangentVelocity.Normalize();
			}
			outHorizontalVel = tangentVelocity * m_moveSpeed;
			if (outHorizontalVel.LengthSq() <= MIN_MOVE_EPSILON * MIN_MOVE_EPSILON) {
				outHorizontalVel = Vector3::Zero;
			}

			// 2. 垂直方向
			m_fallTimer += g_gameTime->GetFrameDeltaTime();
			float jumpPower = m_initialJumpSpeed - (GRAVITY_POWER * m_fallTimer);
			outVerticalVel = m_upDirection * jumpPower;
		}


		Vector3 StateMachineBase::ExecuteMoveCheck(const Vector3& startPos, const Vector3& velocity, bool& outIsWall, Vector3& outNormal)
		{
			Vector3 nextPos = startPos;
			outIsWall = false;
			outNormal = Vector3::Zero;

			float moveDist = velocity.Length();
			if (moveDist <= MIN_MOVE_EPSILON) {
				return nextPos;
			}

			Vector3 dir = velocity;
			dir.Normalize();

			// レイの設定
			Vector3 rayOriginOffset = m_upDirection * WALL_CHECK_RAY_HEIGHT;
			Vector3 rayStart = startPos + rayOriginOffset - (dir * BACK_CHECK_DIST);
			float checkLength = BACK_CHECK_DIST + moveDist + CHAR_RADIUS + SKIN_WIDTH;
			Vector3 rayEnd = rayStart + (dir * checkLength);
			Vector3 hitPos, hitNormal;

			// 衝突判定
			if (RayTest(rayStart, rayEnd, hitPos, hitNormal, m_upDirection))
			{
				float distFromCurrent = (hitPos - rayStart).Length() - BACK_CHECK_DIST;
				float availableDistance = distFromCurrent - CHAR_RADIUS;

				// 1. 埋まり補正
				if (availableDistance < 0.0f) {
					nextPos += hitNormal * (-availableDistance + RECOVERY_BUFFER);
					availableDistance = 0.0f;
				}

				// 2. 坂道・壁判定
				float dot = hitNormal.Dot(m_upDirection);
				Clamp(dot);
				float slopeAngle = acosf(dot);

				if (slopeAngle > WALKABLE_SLOPE_LIMIT)
				{
					// 壁なので手前で停止
					outIsWall = true;
					outNormal = hitNormal;
					float actualMove = max(0.0f, availableDistance - SKIN_WIDTH);
					nextPos += dir * actualMove;
				}
				else
				{
					// 登れる坂なのでそのまま進む
					nextPos += velocity;
				}
			}
			else
			{
				// 障害物なし
				nextPos += velocity;
			}

			return nextPos;
		}


		Vector3 StateMachineBase::ComputeSlideVector(const Vector3& velocity, const Vector3& normal)
		{
			Vector3 slideVector = velocity;

			// 法線方向への成分を取り除く（壁に沿わせる）
			float d = velocity.Dot(normal);
			if (d < 0.0f) {
				slideVector = velocity - normal * d;
				// 張り付き防止
				slideVector += normal * SLIDE_ANTI_STICK;
			}

			return slideVector;
		}


		Vector3 StateMachineBase::CalculateHorizontalMove(const Vector3& currentPos, const Vector3& velocity)
		{
			if (velocity.LengthSq() <= MIN_MOVE_EPSILON) {
				return currentPos;
			}

			// 1. 最初の移動試行
			bool isWall = false;
			Vector3 hitNormal = Vector3::Zero;
			Vector3 nextPos = ExecuteMoveCheck(currentPos, velocity, isWall, hitNormal);

			// 壁に当たっていたら「横滑り」処理
			if (isWall)
			{
				// 実際に動けた分
				Vector3 movedVec = nextPos - currentPos;

				// 残りの移動力
				Vector3 remainingVelocity = velocity - movedVec;

				// 残りを壁に沿って滑らせる
				Vector3 slideVelocity = ComputeSlideVector(remainingVelocity, hitNormal);

				// 2. 滑りベクトルでもう一度移動試行
				bool isWall2 = false;
				Vector3 hitNormal2 = Vector3::Zero;
				nextPos = ExecuteMoveCheck(nextPos, slideVelocity, isWall2, hitNormal2);
			}

			return nextPos;
		}


		Vector3 StateMachineBase::CalculateVerticalMove(const Vector3& currentPos, Vector3& velocity)
		{
			Vector3 nextPos = currentPos;
			Vector3 rayStartPos = nextPos + m_upDirection * VERTICAL_RAY_START_HEIGHT;
			Vector3 rayEndPos = nextPos + velocity - (m_upDirection * VERTICAL_RAY_END_BUFFER);
			Vector3 hitPos, hitNormal;

			if (RayTest(rayStartPos, rayEndPos, hitPos, hitNormal, m_upDirection, Math::PI))
			{
				float dot = hitNormal.Dot(m_upDirection);
				Clamp(dot);
				float angle = acosf(dot);

				if (angle <= WALKABLE_SLOPE_LIMIT) {
					// 着地
					nextPos = hitPos;
					m_initialJumpSpeed = 0.0f;
					m_fallTimer = 0.0f;
					velocity = Vector3::Zero; // 垂直速度をリセット
				}
				else {
					// 滑り落ちる
					nextPos = hitPos;
					Vector3 slideVector = velocity - hitNormal * velocity.Dot(hitNormal);
					velocity = slideVector;
				}
			}
			else {
				// 空中
				nextPos += velocity;
			}

			return nextPos;
		}


		Quaternion StateMachineBase::CalculateRotation(const Quaternion& currentRot, const Vector3& velocity)
		{
			// 1. 上方向ベクトルを正規化
			Vector3 upDir = m_upDirection;
			upDir.Normalize();

			// 2. 移動ベクトルを接平面に投影（垂直成分を除去）
			Vector3 forward = ProjectOnPlane(velocity, upDir);

			// 3. 移動量チェック（停止時）
			if (forward.LengthSq() <= MIN_MOVE_EPSILON * MIN_MOVE_EPSILON) {
				// 停止中：現在の体の向きを維持しつつ、UpVectorに合わせた姿勢を作る

				// 現在のモデルの前方向を取得
				Vector3 currentForward = Vector3::Front;
				m_transform.m_rotation.Apply(currentForward);

				// 接平面に投影
				forward = ProjectOnPlane(currentForward, upDir);

				// それでも長さがゼロ（＝真上/真下を向いている）なら、適当な軸（Front）を使う
				if (forward.LengthSq() <= 0.001f) {
					forward = Vector3::Front;
				}
			}

			forward.Normalize();

			// 4. 惑星アライメント用クォータニオン (World::Up -> Current::Up)
			// モデルのデフォルトの上方向(0, 1, 0)を、惑星の上方向(upDirection)に回転させる
			Quaternion planetAlignmentRot;
			planetAlignmentRot.SetRotation(Vector3::Up, upDir);

			// 5. 惑星にアライメントされた状態で、モデルの前方向（Vector3::Front）がどこに向いているかを求める
			Vector3 projectedDefaultForward = Vector3::Front;
			planetAlignmentRot.Apply(projectedDefaultForward); // これが惑星に沿った状態での「前」
			projectedDefaultForward.Normalize();

			// 6. 惑星に沿った状態のデフォルトの前方向から、ターゲットの方向への回転角度を求める
			float dotResult = projectedDefaultForward.Dot(forward);

			// クランプ
			Clamp(dotResult);

			float rotAngle = acosf(dotResult);

			// 7. 回転の向き（符号）を外積で判定
			Vector3 crossProduct;
			crossProduct.Cross(projectedDefaultForward, forward);
			if (crossProduct.Dot(upDir) < 0.0f) {
				rotAngle *= -1.0f;
			}

			// 8. Y軸（Up軸）周りの回転クォータニオン
			Quaternion yRot;
			yRot.SetRotation(upDir, rotAngle);

			// 9. 「惑星アライメント」と「Y軸回転」を乗算（合成）
			Quaternion nextRot = yRot * planetAlignmentRot;

			// 即時適用して返す（Slerpなし）
			return nextRot;
		}


		void StateMachineBase::ProcessMovement()
		{
			/** 移動ベクトルを水平方向と垂直方向に分ける */
			Vector3 horizontalVel, verticalVel;
			ComputeVelocity(horizontalVel, verticalVel);

			/** 一旦今の座標を保存 */
			Vector3 nextPosition = m_transform.m_position;

			/** 今の座標と水平方向の移動ベクトルを加算し、水平方向に移動した座標を計算 */
			nextPosition = CalculateHorizontalMove(nextPosition, horizontalVel);

			/** さらに垂直方向の移動ベクトルを加算し、垂直方向に移動した座標を計算 */
			nextPosition = CalculateVerticalMove(nextPosition, verticalVel);

			/** 移動後のモデルに使用する回転を計算 */
			Quaternion nextRotation = CalculateRotation(m_transform.m_rotation, horizontalVel);

			/** 座標と回転を保存 */
			m_transform.m_position = nextPosition;
			m_transform.m_rotation = nextRotation;
		}
	}
}