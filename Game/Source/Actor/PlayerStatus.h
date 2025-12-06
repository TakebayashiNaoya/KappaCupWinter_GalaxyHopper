/**
 * PlayerStatus.h
 * プレイヤーのパラメータ定義
 */
#pragma once

 /** パラメータの親玉である IMasterParameter を知るためにインクルード */
#include "Core/ParameterManager.h"

/**
 * プレイヤーの基本パラメータ（データの箱）
 * JSONファイルの内容と対になります
 * structにするのは、メンバ変数をpublicにしてマネージャーからアクセスしやすくするためです
 */
struct MasterPlayerStatusParameter : public IMasterParameter
{
	/** IDを自動生成する魔法のマクロ */
	appParameter(MasterPlayerStatusParameter);

	/** 歩く速度 */
	float walkSpeed = 0.0f;
	/** 走る速度 */
	float runSpeed = 0.0f;
	/** ジャンプ力 */
	float jumpPower = 0.0f;
};

/**
 * パラメータを利用するためのアクセサクラス
 * Playerクラスはこのクラスを持ちます
 */
class PlayerStatus
{
private:
	/**
	 * 読み込んだデータへのポインタ
	 * constにしているのは、ゲーム中に勝手に書き換わらないようにするためです
	 */
	const MasterPlayerStatusParameter* m_param = nullptr;

public:
	PlayerStatus();
	~PlayerStatus();

	/** データの取得（ParameterManagerからポインタをもらう） */
	void Load();

	/** 各値のゲッター（安全装置付き） */
	float GetWalkSpeed() const { return m_param ? m_param->walkSpeed : 0.0f; }
	float GetRunSpeed() const { return m_param ? m_param->runSpeed : 0.0f; }
	float GetJumpPower() const { return m_param ? m_param->jumpPower : 0.0f; }
};