/**
 * ActorTypes.h
 * アクター関連の定義
 */
#pragma once

enum enPlayerCondition : uint8_t
{
	enPlayerCondition_Dead,		// 死亡。
	enPlayerCondition_Danger,	// 危険。
	enPlayerCondition_Caution,	// 注意。
	enPlayerCondition_Fine,		// 全快。
	enPlayerCondition_Num,
};


/**
 * プレイヤーのアニメーションクリップ
 */
enum class EnPlayerAnimClip : uint8_t
{
	Idle,		/** 待機		*/
	Walk,		/** 歩き		*/
	Dash,		/** 走り		*/
	Jump,		/** ジャンプ	*/
	Damage,		/** 被弾		*/
	Dying,		/** 死亡		*/
	Num,
};