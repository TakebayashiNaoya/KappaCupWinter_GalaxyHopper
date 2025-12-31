/**
 * StateMachineBase.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachineBase.h"
#include "Source/Actor/Character/Character.h"


namespace app
{
	namespace actor
	{
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
			 * 移動速度（水平・垂直）を算出する
			 * 変数（引数に入れた変数に再代入される）
			 * 　・水平方向の速度（Vector3&）
			 * 定数
			 * 　・移動方向ベクトル（Vector3&）
			 * 　・上方向ベクトル（Vector3&）
			 * 　・移動速度（float）
			 */
			void CalcHorizontalVelocity(
				Vector3& outHorizontalVel,
				const Vector3& moveDirection,
				const Vector3& upDirection,
				const float moveSpeed
			)
			{
				/** 水平方向の速度ベクトルを算出 */
				Vector3 tangentVelocity = ProjectOnPlane(moveDirection, upDirection);
				if (tangentVelocity.LengthSq() > 0.001f) {
					tangentVelocity.Normalize();
				}
				outHorizontalVel = tangentVelocity * moveSpeed;
				if (outHorizontalVel.LengthSq() <= MIN_MOVE_EPSILON * MIN_MOVE_EPSILON) {
					outHorizontalVel = Vector3::Zero;
				}
			}


			/**
			 * 移動速度（水平・垂直）を算出する
			 * 変数（引数に入れた変数に再代入される）
			 * 　・垂直方向の速度（Vector3&）
			 * 　・落下タイマー（float&）
			 * 定数
			 * 　・上方向ベクトル（Vector3&）
			 * 　・ジャンプ初速度（float）
			 */
			void CalcVerticalVelocity(
				Vector3& outVerticalVel,
				float& fallTimer,
				const Vector3& upDirection,
				const float initialJumpSpeed
			)
			{
				/** 垂直方向の速度ベクトルを算出 */
				fallTimer += g_gameTime->GetFrameDeltaTime();
				float jumpPower = initialJumpSpeed - (GRAVITY_POWER * fallTimer);
				outVerticalVel = upDirection * jumpPower;
			}


			/**
			 * 移動チェックを実行する
			 * 壁に当たった場合は、IsWallをtrueにし、当たった法線をoutNormalに格納する
			 * 変数（引数に入れた変数に再代入される）
			 * 　・壁に当たったかどうか（bool&）
			 * 　・当たった法線（Vector3&）
			 * 定数
			 * 　・開始位置（Vector3&）
			 * 　・移動速度（Vector3&）
			 * 　・上方向ベクトル（Vector3&）
			 */
			Vector3 ExecuteMoveCheck(
				bool& outIsWall,
				Vector3& outNormal,
				const Vector3& startPos,
				const Vector3& velocity,
				const Vector3& upDirection
			)
			{
				/** 変数の初期化 */
				Vector3 nextPos = startPos;
				outIsWall = false;
				outNormal = Vector3::Zero;

				/** 移動距離が極小なら処理しない */
				float moveDist = velocity.Length();
				if (moveDist <= MIN_MOVE_EPSILON) {
					return nextPos;
				}

				/** 移動方向を正規化 */
				Vector3 dir = velocity;
				dir.Normalize();


				/**
				 * レイの発射位置は、レイが地面に当たらないように、足元より少し上に補正、
				 * さらに壁に埋まらないよう、移動方向に向かって少し引いた位置から撃つ
				 */
				Vector3 rayOriginOffset = upDirection * WALL_CHECK_RAY_HEIGHT;
				Vector3 rayStart = startPos + rayOriginOffset - (dir * BACK_CHECK_DIST);
				/**
				 * キャラクターの体が壁に埋まらないようにするための引き撃ち処理
				 * チェック距離は、移動距離 + 引き撃ち分 + キャラの半径 + スキン幅
				 */
				float checkLength = moveDist + BACK_CHECK_DIST + CHAR_RADIUS + SKIN_WIDTH;
				Vector3 rayEnd = rayStart + (dir * checkLength);
				/** レイの衝突位置と法線を受け取る変数 */
				Vector3 hitPos, hitNormal;

				/** 衝突判定 */
				if (RayTest(rayStart, rayEnd, hitPos, hitNormal, upDirection))
				{
					/** キャラクターの体の中心からレイの衝突点までの正確な距離を算出 */
					float distFromCurrent = (hitPos - rayStart).Length() - BACK_CHECK_DIST;
					/** キャラクターの半径分を引くことで、キャラクターの表面から衝突点までの距離を算出 */
					float availableDistance = distFromCurrent - CHAR_RADIUS;

					/**
					 * availableDistanceがマイナスの場合、キャラクターの表面が埋まっているため、
					 * 壁の法線方向に、埋まっている分 + RECOVERY_BUFFERだけ押し出す
					 */
					if (availableDistance < 0.0f) {
						nextPos += hitNormal * (-availableDistance + RECOVERY_BUFFER);
						availableDistance = 0.0f;
					}

					/** キャラクターの上方向と、レイの衝突点の間の角度を算出 */
					float dot = hitNormal.Dot(upDirection);
					Clamp(dot);
					float slopeAngle = acosf(dot);

					/** 坂として判断する角度以上の傾斜であれば壁とみなす */
					if (slopeAngle > WALKABLE_SLOPE_LIMIT)
					{
						/**
						 * 横滑りの処理が必要になるため、
						 * outIsWallのフラグを立て、レイが当たったポリゴンの法線をoutNormalに入れる
						 */
						outIsWall = true;
						outNormal = hitNormal;
						/** 壁の手前まで移動させる */
						float actualMove = max(0.0f, availableDistance - SKIN_WIDTH);
						nextPos += dir * actualMove;
					}
					else
					{
						/** 登れる坂なのでそのまま進む */
						nextPos += velocity;
					}
				}
				else
				{
					/** 障害物がないためそのまま進む */
					nextPos += velocity;
				}
				/** 結果の座標を返す */
				return nextPos;
			}


			/**
			 * 壁に沿って滑るベクトルを計算する
			 * 定数
			 * 　・移動速度ベクトル（Vector3&）
			 * 　・当たった法線ベクトル（Vector3&）
			 */
			Vector3 CalcSlideVector(
				const Vector3& velocity,
				const Vector3& normal
			)
			{
				Vector3 slideVector = velocity;

				/** 法線方向への成分を取り除く（壁に沿わせる） */
				float dir = velocity.Dot(normal);
				if (dir < 0.0f) {
					/** 壁に沿ったベクトルを算出 */
					slideVector = velocity - normal * dir;
					/** 少しだけ壁から離れるようにする */
					slideVector += normal * SLIDE_ANTI_STICK;
				}

				return slideVector;
			}


			/**
			 * 水平方向の移動処理を行う
			 * 定数
			 * 　・現在位置（Vector3&）
			 * 　・移動速度（Vector3&）
			 * 　・上方向ベクトル（Vector3&）
			 */
			Vector3 CalcHorizontalMove(
				const Vector3& currentPos,
				const Vector3& velocity,
				const Vector3& upDirection
			)
			{
				if (velocity.LengthSq() <= MIN_MOVE_EPSILON) {
					return currentPos;
				}

				/**
				 * 移動を試みる
				 * もし壁に当たっていたら、横滑り処理を行う
				 */
				bool isWall = false;
				Vector3 hitNormal = Vector3::Zero;
				Vector3 nextPos = ExecuteMoveCheck(isWall, hitNormal, currentPos, velocity, upDirection);

				/** 壁に当たっていたら横滑り処理 */
				if (isWall)
				{
					/** 実際に動けた分 */
					Vector3 movedVec = nextPos - currentPos;

					/** 残りの移動力 */
					Vector3 remainingVelocity = velocity - movedVec;

					/** 壁に沿って移動した場合の座標を算出 */
					Vector3 slideVelocity = CalcSlideVector(remainingVelocity, hitNormal);

					/**
					 * 滑りベクトルでもう一度移動を試みる
					 * 再度壁に当たる可能性もあるが、その場合はそこで止まる
					 * ※二回目の衝突判定結果は無視するため、unusedFlagとunusedVectorは使わない
					 */
					bool unusedFlag = false;
					Vector3 unusedVector = Vector3::Zero;
					nextPos = ExecuteMoveCheck(unusedFlag, unusedVector, nextPos, slideVelocity, upDirection);
				}

				return nextPos;
			}


			/**
			 * 垂直方向の移動処理を行う
			 * 変数（引数に入れた変数に再代入される）
			 * 　・移動速度ベクトル（Vector3&）
			 * 　・ジャンプ初速度（float&）
			 * 　・落下タイマー（float&）
			 * 定数
			 * 　・現在位置（Vector3&）
			 * 　・上方向ベクトル（Vector3&）
			 */
			Vector3 CalcVerticalMove(
				Vector3& velocity,
				float& initialJumpSpeed,
				float& fallTimer,
				const Vector3& currentPos,
				const Vector3& upDirection
			)
			{
				Vector3 nextPos = currentPos;
				/** 足元より少し上からレイを飛ばす */
				Vector3 rayStartPos = nextPos + upDirection * VERTICAL_RAY_START_HEIGHT;
				/** 移動先より少し下方向にレイを飛ばす*/
				Vector3 rayEndPos = nextPos + velocity - (upDirection * VERTICAL_RAY_END_BUFFER);
				/** レイの衝突位置と法線を受け取る変数 */
				Vector3 hitPos, hitNormal;

				/** 衝突判定 */
				if (RayTest(rayStartPos, rayEndPos, hitPos, hitNormal, upDirection, Math::PI))
				{
					/** キャラクターの上方向とレイが当たったポリゴンの法線の間の角度を算出 */
					float dot = hitNormal.Dot(upDirection);
					Clamp(dot);
					float angle = acosf(dot);

					/** 坂として判断する角度以上の傾斜であれば壁とみなす */
					if (angle <= WALKABLE_SLOPE_LIMIT) {
						/** 着地 */
						nextPos = hitPos;
						initialJumpSpeed = 0.0f;
						fallTimer = 0.0f;
						velocity = Vector3::Zero;
					}
					else {
						/** 滑り落ちる */
						nextPos = hitPos;
						Vector3 slideVector = ProjectOnPlane(velocity, hitNormal);
						velocity = slideVector;
					}
				}
				else {
					/** レイが当たらなければ空中にいるため、そのまま落下移動する */
					nextPos += velocity;
				}

				return nextPos;
			}


			/**
			 * キャラクターの回転を計算する
			 * 定数
			 * 　・移動速度ベクトル（Vector3&）
			 * 　・上方向ベクトル（Vector3&）
			 * 　・現在の回転クォータニオン（Quaternion&）
			 */
			Quaternion CalcRotation(
				const Vector3& velocity,
				const Vector3& upDirection,
				const Quaternion& currentRotation
			)
			{
				// 2. 移動ベクトルを接平面に投影（垂直成分を除去）
				Vector3 forward = ProjectOnPlane(velocity, upDirection);

				// 3. 移動量チェック（停止時）
				if (forward.LengthSq() <= MIN_MOVE_EPSILON) {
					// 停止中：現在の体の向きを維持しつつ、UpVectorに合わせた姿勢を作る

					// 現在のモデルの前方向を取得
					Vector3 currentForward = Vector3::Front;
					currentRotation.Apply(currentForward);

					// 接平面に投影
					forward = ProjectOnPlane(currentForward, upDirection);

					// それでも長さがゼロ（＝真上/真下を向いている）なら、適当な軸（Front）を使う
					if (forward.LengthSq() <= 0.001f) {
						forward = Vector3::Front;
					}
				}

				forward.Normalize();

				// 4. 惑星アライメント用クォータニオン (World::Up -> Current::Up)
				// モデルのデフォルトの上方向(0, 1, 0)を、惑星の上方向(upDirection)に回転させる
				Quaternion planetAlignmentRot;
				planetAlignmentRot.SetRotation(Vector3::Up, upDirection);

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
				if (crossProduct.Dot(upDirection) < 0.0f) {
					rotAngle *= -1.0f;
				}

				// 8. Y軸（Up軸）周りの回転クォータニオン
				Quaternion yRot;
				yRot.SetRotation(upDirection, rotAngle);

				// 9. 「惑星アライメント」と「Y軸回転」を乗算（合成）
				Quaternion nextRot = yRot * planetAlignmentRot;

				// 即時適用して返す（Slerpなし）
				return nextRot;
			}
		}


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


		void StateMachineBase::ProcessMovement()
		{
			/** 移動方向ベクトルを正規化 */
			m_moveDirection.Normalize();
			/** 上方向ベクトルを算出して正規化 */
			m_upDirection = m_transform.m_position - Vector3::Zero;
			m_upDirection.Normalize();

			/** 移動ベクトルの水平方向を算出 */
			Vector3 horizontalVel;
			CalcHorizontalVelocity(horizontalVel, m_moveDirection, m_upDirection, m_moveSpeed);

			/** 今の座標と水平方向の移動ベクトルを加算し、水平方向に移動した座標を計算 */
			Vector3 horiMovedPos = CalcHorizontalMove(m_transform.m_position, horizontalVel, m_upDirection);

			/** さらに垂直方向の移動ベクトルを加算し、垂直方向に移動した座標を計算 */
			Vector3 horiMovedUpDir = horiMovedPos - Vector3::Zero;
			horiMovedUpDir.Normalize();
			Vector3 verticalVel;
			CalcVerticalVelocity(verticalVel, m_fallTimer, horiMovedUpDir, m_initialJumpSpeed);
			Vector3 nextPosition = CalcVerticalMove(verticalVel, m_initialJumpSpeed, m_fallTimer, horiMovedPos, horiMovedUpDir);

			/** 移動後の上方向を再計算し、回転を算出 */
			m_upDirection = nextPosition - Vector3::Zero;
			m_upDirection.Normalize();
			Quaternion nextRotation = CalcRotation(horizontalVel, m_upDirection, m_transform.m_rotation);

			/** 座標と回転を保存 */
			m_transform.m_position = nextPosition;
			m_transform.m_rotation = nextRotation;
		}
	}
}