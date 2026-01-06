/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "ActorStatus.h"
#include "Core/ParameterManager.h"


namespace app
{
	namespace actor
	{
		PlayerStatus::PlayerStatus()
		{
			/** 外部ファイルを読み込み */
			ParameterManager::Get().LoadParameter<MasterPlayerStatusParameter>("Assets/parameter/PlayerStatus.json", [](const nlohmann::json& j, MasterPlayerStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.dashSpeed = j["dashSpeed"].get<float>();
					parameter.jumpPower = j["jumpPower"].get<float>();
				});
		}


		PlayerStatus::~PlayerStatus()
		{
			/** 使用が終わったので解放 */
			ParameterManager::Get().UnloadParameter<MasterPlayerStatusParameter>();
		}


		void PlayerStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = ParameterManager::Get().GetParameter<MasterPlayerStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_dashSpeed = parameter->dashSpeed;
			m_jumpPower = parameter->jumpPower;
		}




		/**************************************************/


		BasicEnemyStatus::BasicEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			ParameterManager::Get().LoadParameter<MasterBasicEnemyStatusParameter>("Assets/parameter/BasicEnemyStatus.json", [](const nlohmann::json& j, MasterBasicEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
				});
		}


		BasicEnemyStatus::~BasicEnemyStatus()
		{
			/** 使用が終わったので解放 */
			ParameterManager::Get().UnloadParameter<MasterBasicEnemyStatusParameter>();
		}


		void BasicEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = ParameterManager::Get().GetParameter<MasterBasicEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
		}




		/**************************************************/


		DeformEnemyStatus::DeformEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			ParameterManager::Get().LoadParameter<MasterDeformEnemyStatusParameter>("Assets/parameter/DeformEnemyStatus.json", [](const nlohmann::json& j, MasterDeformEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
					parameter.slideSpeed = j["slideSpeed"].get<float>();
				});
		}


		DeformEnemyStatus::~DeformEnemyStatus()
		{
			/** 使用が終わったので解放 */
			ParameterManager::Get().UnloadParameter<MasterDeformEnemyStatusParameter>();
		}


		void DeformEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = ParameterManager::Get().GetParameter<MasterDeformEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
			m_slideSpeed = parameter->slideSpeed;
		}




		/**************************************************/


		BossEnemyStatus::BossEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			ParameterManager::Get().LoadParameter<MasterBossEnemyStatusParameter>("Assets/parameter/BossEnemyStatus.json", [](const nlohmann::json& j, MasterBossEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
					parameter.dashSpeed = j["dashSpeed"].get<float>();
				});
		}


		BossEnemyStatus::~BossEnemyStatus()
		{
			/** 使用が終わったので解放 */
			ParameterManager::Get().UnloadParameter<MasterBossEnemyStatusParameter>();
		}


		void BossEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = ParameterManager::Get().GetParameter<MasterBossEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
			m_dashSpeed = parameter->dashSpeed;
		}
	}
}