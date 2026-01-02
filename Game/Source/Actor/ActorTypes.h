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


/**
 * プレイヤーのアニメーションクリップ
 */
enum class EnPlayerAnimClip : uint8_t
{
	Idle,	/** 待機	 */
	Walk,	/** 歩き	 */
	Dash,	/** 走り	 */
	Jump,	/** ジャンプ */
	Damage,	/** 被弾	 */
	Die,	/** 死亡	 */
	Num,
};


/**
 * 基本エネミーのアニメーションクリップ
 */
enum class EnBasicEnemyAnimClip : uint8_t
{
	Idle,	/** 待機 */
	Walk,	/** 歩き */
	Dash,	/** 走り */
	Num,
};


/**
 * 変形エネミーのアニメーションクリップ
 */
enum class EnDeformEnemyAnimClip : uint8_t
{
	Idle,	/** 待機 */
	Walk,	/** 歩き */
	Dash,	/** 走り */
	Die,	/** 死亡 */
	Num,
};


/**
 * ボスエネミーのアニメーションクリップ
 */
enum class EnBossEnemyAnimClip : uint8_t
{
	Idle,	/** 待機 */
	Walk,	/** 歩き */
	Dash,	/** 走り */
	Attack,	/** 攻撃 */
	Damage,	/** 被弾 */
	Die,	/** 死亡 */
	Num,
};