/**
 * ActorTypes.h
 * アクター用の定数やEnum定義
 */
#pragma once

 /**
  * プレイヤーのアニメーションの種類
  */
enum class PlayerAnimationType
{
	Idle,		// 待機
	Walk,		// 歩き
	Run,		// 走り
	Down,		// ダウン
	Dead,		// 死亡
	Num,
};