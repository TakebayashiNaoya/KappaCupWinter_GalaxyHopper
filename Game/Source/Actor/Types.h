/// <summary>
/// 各キャラクターのステートを定義するヘッダー。
/// </summary>
#pragma once

enum enPlayerCondition {
	enPlayerCondition_Dead,		// 死亡。
	enPlayerCondition_Danger,	// 危険。
	enPlayerCondition_Caution,	// 注意。
	enPlayerCondition_Fine,		// 全快。
	enPlayerCondition_Num,
};