#include "stdafx.h"
#include "CollisionManager.h"
#include "Source/Actor/ActorStatus.h"
#include "Source/Actor/Character/Character.h"
#include "Source/Actor/Character/Enemy/BasicEnemy/BasicEnemy.h"
#include "Source/Actor/Character/Enemy/BossEnemy/BossEnemy.h"
#include "Source/Actor/Character/Enemy/DeformEnemy/DeformEnemy.h"
#include "Source/Actor/Character/Player/Player.h"
#include "Source/Actor/Character/Player/PlayerStateMachine.h"


namespace app
{
	namespace collision
	{
		namespace
		{
			//TODO: スタンプフラグは不要のため、この関数は消し、プレイヤーの無敵状態だけで判定するようにする。
			// 
			//// プレイヤーが無敵中か、プレイヤーの攻撃が先に当たっている場合、trueを返す。
			//const bool IsAttackBlocked(Player* player, const bool isStomp)
			//{
			//	if (player->GetIsInvincible()) {
			//		return true;
			//	}
			//	else if (isStomp) {
			//		return true;
			//	}
			//	return false;
			//}
		}


		CollisionHitManager* CollisionHitManager::m_instance = nullptr;


		CollisionHitManager::CollisionHitManager()
		{
			m_collisionInformationList.clear();
		}


		CollisionHitManager::~CollisionHitManager()
		{
			m_collisionInformationList.clear();
			m_collisionPairList.clear();
		}


		void CollisionHitManager::Update()
		{
			///**
			// * シーン切り替えがリクエストされている場合は、現在のフレームの衝突判定処理をスキップする
			// * これにより、削除が始まったオブジェクトへの不正アクセスを防ぐ
			// */
			//if (SceneManager::GetInstance()->GetIsSceneChangeRequested()) {
			//	m_collisionPairList.clear();
			//	return;
			//}
			///** バトル終了後は衝突判定を行わない */
			//if (BattleManager::GetIsStopCollisionManager()) {
			//	m_collisionPairList.clear();
			//	return;
			//}

			m_collisionPairList.clear();

			// ヒットするオブジェクトのペアを作る
			const uint32_t colSize = static_cast<uint32_t>(m_collisionInformationList.size());
			for (uint32_t i = 0; i < colSize; ++i) {
				for (uint32_t j = i + 1; j < colSize; ++j) {
					CollisionInformation* infoA = &m_collisionInformationList[i];
					CollisionInformation* infoB = &m_collisionInformationList[j];

					if (infoA->m_collision->IsHit(infoB->m_collision) || infoB->m_collision->IsHit(infoA->m_collision))
					{
						// CollisionPairの中に同じ組み合わせがないかチェック
						bool exists = false;
						for (const auto& pair : m_collisionPairList) {
							if ((pair.m_left == infoA && pair.m_right == infoB) || (pair.m_left == infoB && pair.m_right == infoA)) {
								exists = true;
								break;
							}
						}
						// すでに登録済みではないなら追加する
						if (!exists) {
							m_collisionPairList.push_back(CollisionPair(infoA, infoB));
						}
					}
				}
			}


			/** ヒットしたペアで衝突した時の処理をする */
			for (auto& pair : m_collisionPairList)
			{
				/** プレイヤー vs 基本エネミー */
				if (UpdateHitPlayerBasicEnemy(pair)) {
					continue;
				}

				/** プレイヤー vs 変形エネミー */
				if (UpdateHitPlayerDeformEnemy(pair)) {
					continue;
				}

				/** プレイヤー vs ボスエネミー */
				if (UpdateHitPlayerBossEnemy(pair)) {
					continue;
				}

				/** 基本エネミー vs 変形エネミー */
				if (UpdateHitBasicEnemyDeformEnemy(pair)) {
					continue;
				}

				/** 変形エネミー vs ボスエネミー */
				if (UpdateHitDeformEnemyBossEnemy(pair)) {
					continue;
				}
			}

			m_collisionPairList.clear();
		}


		void CollisionHitManager::Register(const EnCollisionType type, CollisionObject* collisionObject, IGameObject* gameObject)
		{
			CollisionInformation info(type, collisionObject, gameObject);
			m_collisionInformationList.push_back(info);
		}


		void CollisionHitManager::Unregister(CollisionObject* collisionObject)
		{
			if (m_collisionInformationList.size() == 0) {
				return;
			}

			for (auto it = m_collisionInformationList.begin(); it != m_collisionInformationList.end(); ++it)
			{
				if (it->m_collision == nullptr) {
					continue;
				}

				if (it->m_collision == collisionObject) {
					m_collisionInformationList.erase(it);
					break;
				}
			}
		}


		bool CollisionHitManager::UpdateHitPlayerBasicEnemy(CollisionPair& pair)
		{
			actor::Player* player = GetTargetObject<actor::Player>(pair, EnCollisionType::Player);
			if (player == nullptr) {
				return false;
			}

			actor::BasicEnemy* basicEnemy = GetTargetObject<actor::BasicEnemy>(pair, EnCollisionType::BasicEnemy);
			if (basicEnemy == nullptr) {
				return false;
			}


			/** プレイヤーの攻撃 */
			if (player->GetAttackHitCollider()->IsHit(basicEnemy->GetHurtCollider())) {
				/** ジャンプの初速を設定 */
				player->GetStateMachine<actor::PlayerStateMachine>()->SetInitialJumpSpeed(player->GetStatus<actor::PlayerStatus>()->GetJumpPower());
				/** 落下タイマーをリセット */
				player->GetStateMachine<actor::PlayerStateMachine>()->SetFallTimer(0.0f);
				/** エネミーにダメージを与える */
				basicEnemy->GetStatus<actor::BasicEnemyStatus>()->TakeDamage();
				/** 踏んだ時のSEを再生 */
				sound::SoundManager::Play(sound::enSoundList_Stomp);
				return true;
			}

			/** プレイヤーが無敵中の場合、エネミーの攻撃は無効にする */
			if (player->GetIsInvincible()) {
				return true;
			}

			/** エネミーの攻撃 */
			if (basicEnemy->GetHitCollider()->IsHit(player->GetHurtCollider())) {
				/** プレイヤーにダメージを与える */
				player->GetStatus<actor::PlayerStatus>()->TakeDamage();
				/** ノックバック方向を計算・設定 */
				Vector3 knockBackDir = player->GetTransform().m_position - basicEnemy->GetTransform().m_position;
				knockBackDir.Normalize();
				player->GetStateMachine<actor::PlayerStateMachine>()->SetKnockBackDirection(knockBackDir);

				basicEnemy->SetIsCoolDown(true);
				sound::SoundManager::Play(sound::enSoundList_PlayerDamage);
				return true;
			}

			return true;
		}


		bool CollisionHitManager::UpdateHitPlayerDeformEnemy(CollisionPair& pair)
		{
			return false;
		}


		bool CollisionHitManager::UpdateHitPlayerBossEnemy(CollisionPair& pair)
		{
			return false;
		}


		bool CollisionHitManager::UpdateHitBasicEnemyDeformEnemy(CollisionPair& pair)
		{
			return false;
		}


		bool CollisionHitManager::UpdateHitDeformEnemyBossEnemy(CollisionPair& pair)
		{
			return false;
		}


		CollisionObject* CollisionHitManager::CreateCollider(
			app::actor::Character* ins, const EnCollisionType type, const Vector3 size, const EnCollisionAttr index)
		{
			/** コリジョンを作成 */
			CollisionObject* collider = new CollisionObject();
			collider->CreateBox(
				ins->GetTransform().m_position,
				ins->GetTransform().m_rotation,
				size
			);

			/** コリジョンヒットマネージャーに登録 */
			m_instance->Register(type, collider, ins);

			/** RayTestで無視するかどうかを設定 */
			m_instance->SetIsTrigger(collider, index);

			return collider;
		}


		CollisionObject* CollisionHitManager::CreateCollider(
			app::actor::Character* ins, const EnCollisionType type, const float radius, const EnCollisionAttr index)
		{
			/** コリジョンを作成 */
			CollisionObject* collider = new CollisionObject();
			collider->CreateSphere(
				ins->GetTransform().m_position,
				ins->GetTransform().m_rotation,
				radius
			);

			/** コリジョンヒットマネージャーに登録 */
			m_instance->Register(type, collider, ins);

			/** RayTestで無視するかどうかを設定 */
			m_instance->SetIsTrigger(collider, index);

			return collider;
		}


		CollisionObject* CollisionHitManager::CreateCollider(
			app::actor::Character* ins, const EnCollisionType type, const float radius, const float height, const EnCollisionAttr index)
		{
			/** コリジョンを作成 */
			CollisionObject* collider = new CollisionObject();
			collider->CreateCapsule(
				ins->GetTransform().m_position,
				ins->GetTransform().m_rotation,
				radius,
				height
			);

			/** コリジョンヒットマネージャーに登録 */
			m_instance->Register(type, collider, ins);

			/** RayTestで無視するかどうかを設定 */
			m_instance->SetIsTrigger(collider, index);

			return collider;
		}


		void CollisionHitManager::UpdateCollider(
			app::actor::Character* ins, CollisionObject* collider, const float offset)
		{
			if (collider == nullptr) {
				return;
			}

			/** コライダーの座標を計算する */
			Vector3 ghostPos = ins->GetTransform().m_position + ins->GetUpDirection() * offset;

			/** コライダーの座標をモデルの座標に合わせる */
			collider->SetPosition(ghostPos);

			/** コライダーの回転をモデルの回転に合わせる */
			collider->SetRotation(ins->GetTransform().m_rotation);
		}


		CollisionObject* CollisionHitManager::DeleteCollider(CollisionObject* collider)
		{
			if (collider == nullptr) {
				return nullptr;
			}

			/** コリジョンヒットマネージャーから登録解除 */
			if (GetIsAvailable()) {
				GetInstance()->Unregister(collider);
			}

			delete collider;
			return nullptr;
		}

		void CollisionHitManager::SetIsTrigger(CollisionObject* collider, EnCollisionAttr index)
		{
			if (collider) {
				/** UserIndexの内部処理はintのため、属性のenumをintとしてセットする */
				collider->GetbtCollisionObject().setUserIndex(index);
			}
		}
	}
}