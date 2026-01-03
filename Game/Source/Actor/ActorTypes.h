/**
 * ActorTypes.h
 * アクター関連の定義
 */
#pragma once


 /**
  * プレイヤーの体力状態
  */
enum enPlayerCondition : uint8_t
{
	enPlayerCondition_Dead,		// 死亡。
	enPlayerCondition_Danger,	// 危険。
	enPlayerCondition_Caution,	// 注意。
	enPlayerCondition_Fine,		// 全快。
	enPlayerCondition_Num,
};











