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
		RocketStatus::RocketStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterRocketStatusParameter>("Assets/parameter/RocketStatus.json", [](const nlohmann::json& j, core::MasterRocketStatusParameter& parameter)
				{
					parameter.interactRange = j["interactRange"].get<float>();
				});
		}


		RocketStatus::~RocketStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterRocketStatusParameter>();
		}


		void RocketStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterRocketStatusParameter>();
			m_interactRange = parameter->interactRange;
		}




		/**************************************************/


		TreasureStatus::TreasureStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterTreasureStatusParameter>("Assets/parameter/TreasureStatus.json", [](const nlohmann::json& j, core::MasterTreasureStatusParameter& parameter)
				{
					parameter.interactRange = j["interactRange"].get<float>();
				});
		}


		TreasureStatus::~TreasureStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterTreasureStatusParameter>();
		}


		void TreasureStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterTreasureStatusParameter>();
			m_interactRange = parameter->interactRange;
		}




		/**************************************************/


		PlayerStatus::PlayerStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterPlayerStatusParameter>("Assets/parameter/PlayerStatus.json", [](const nlohmann::json& j, core::MasterPlayerStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.dashSpeed = j["dashSpeed"].get<float>();
					parameter.jumpPower = j["jumpPower"].get<float>();
					parameter.knockbackPower = j["knockbackPower"].get<float>();
					parameter.knockbackDuration = j["knockbackDuration"].get<float>();
				});
		}


		PlayerStatus::~PlayerStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterPlayerStatusParameter>();
		}


		void PlayerStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterPlayerStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_dashSpeed = parameter->dashSpeed;
			m_jumpPower = parameter->jumpPower;
			m_knockbackPower = parameter->knockbackPower;
			m_knockbackDuration = parameter->knockbackDuration;
		}




		/**************************************************/


		BasicEnemyStatus::BasicEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterBasicEnemyStatusParameter>("Assets/parameter/BasicEnemyStatus.json", [](const nlohmann::json& j, core::MasterBasicEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
					parameter.searchRange = j["searchRange"].get<float>();
				});
		}


		BasicEnemyStatus::~BasicEnemyStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterBasicEnemyStatusParameter>();
		}


		void BasicEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterBasicEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
			m_searchRange = parameter->searchRange;
		}




		/**************************************************/


		DeformEnemyStatus::DeformEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterDeformEnemyStatusParameter>("Assets/parameter/DeformEnemyStatus.json", [](const nlohmann::json& j, core::MasterDeformEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
					parameter.searchRange = j["searchRange"].get<float>();
					parameter.slideSpeed = j["slideSpeed"].get<float>();
				});
		}


		DeformEnemyStatus::~DeformEnemyStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterDeformEnemyStatusParameter>();
		}


		void DeformEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterDeformEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
			m_searchRange = parameter->searchRange;
			m_slideSpeed = parameter->slideSpeed;
		}




		/**************************************************/


		BossEnemyStatus::BossEnemyStatus()
		{
			/** 外部ファイルを読み込み */
			core::ParameterManager::Get().LoadParameter<core::MasterBossEnemyStatusParameter>("Assets/parameter/BossEnemyStatus.json", [](const nlohmann::json& j, core::MasterBossEnemyStatusParameter& parameter)
				{
					parameter.maxHp = j["maxHp"].get<int>();
					parameter.walkSpeed = j["walkSpeed"].get<float>();
					parameter.hurtRadius = j["hurtRadius"].get<float>();
					parameter.modelScale = j["modelScale"].get<float>();
					parameter.colliderOffset = j["colliderOffset"].get<float>();
					parameter.hitRadius = j["hitRadius"].get<float>();
					parameter.searchRange = j["searchRange"].get<float>();
					parameter.dashSpeed = j["dashSpeed"].get<float>();
				});
		}


		BossEnemyStatus::~BossEnemyStatus()
		{
			/** 使用が終わったので解放 */
			core::ParameterManager::Get().UnloadParameter<core::MasterBossEnemyStatusParameter>();
		}


		void BossEnemyStatus::Setup()
		{
			/** 読み込んだパラメーター取得 */
			const auto* parameter = core::ParameterManager::Get().GetParameter<core::MasterBossEnemyStatusParameter>();
			m_maxHp = parameter->maxHp;
			m_walkSpeed = parameter->walkSpeed;
			m_hurtRadius = parameter->hurtRadius;
			m_modelScale = parameter->modelScale;
			m_colliderOffset = parameter->colliderOffset;
			m_hitRadius = parameter->hitRadius;
			m_searchRange = parameter->searchRange;
			m_dashSpeed = parameter->dashSpeed;
		}
	}
}