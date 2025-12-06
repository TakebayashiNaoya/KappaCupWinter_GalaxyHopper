/// <summary>
/// プレイヤーを管理するクラス。
/// </summary>
#pragma once
#include "Source/Actor/Character/Character.h"
#include "PlayerStatus.h" // ★追加: パラメータ管理

namespace app {
	namespace player {
		class PlayerStateMachine;
	}
}

class Player : public Character
{
public:
	Player();
	~Player();

	/// <summary>
	/// アニメーションのクリップを表す列挙型
	/// </summary>
	enum EnAnimationClip
	{
		enAnimationClip_Idle,		// 待機
		enAnimationClip_Walk,		// 歩き
		enAnimationClip_Run,		// 走り
		enAnimationClip_Down,		// ダウン
		enAnimationClip_Dead,		// 死亡
		enAnimationClip_Num,
	};

	// ----------------------------------------------------------
	// ★追加: 外部（コントローラー）から操作を受け取るための関数
	// ----------------------------------------------------------
	void SetVelocity(const Vector3& velocity) { m_velocity = velocity; }

	// ----------------------------------------------------------
	// ★追加: ステータスとステートマシンへのアクセス
	// ----------------------------------------------------------
	PlayerStatus* GetPlayerStatus() const { return m_status; }
	app::player::PlayerStateMachine* GetStateMachine() const { return m_stateMachine.get(); }


	/// <summary>
	/// 毎フレームのXZ軸回転角度を取得
	/// </summary>
	const Quaternion& GetAdditionalRot() const { return m_xzAdditionalRot; }

	/// <summary>
	/// 無敵中かどうかを取得・設定
	/// </summary>
	const bool GetIsInvincible() const { return m_isInvincible; }
	void SetIsInvincible(const bool isInvincible) { m_isInvincible = isInvincible; }

	/// <summary>
	/// ノックバックタイマーをリセット
	/// </summary>
	void ResetKnockBackTimer() { m_knockBackTimer = 0.0f; }

	/// <summary>
	/// カメラの回転角度を計算
	/// </summary>
	void CalcCameraRotation();

	/// <summary>
	/// 移動更新（速度はJSONから、方向はControllerから受け取る）
	/// </summary>
	/// <param name="speed">移動速度</param>
	void MoveUpdate(const float speed);

	/// <summary>
	/// ノックバック方向を計算
	/// </summary>
	void ComputeKnockBackDirection(const Vector3& enemyPos);

	/// <summary>
	/// ノックバック処理
	/// </summary>
	void KnockedBack();

	/// <summary>
	/// 踏みつけジャンプ
	/// </summary>
	void StompJump();

	/// <summary>
	/// アニメーションイベント
	/// </summary>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) override final;

protected:
	// ★削除: 入力処理（ComputeMoveDirection）はControllerに移譲したため不要

protected:
	Quaternion	m_xzAdditionalRot;	// 毎フレームのXZ軸回転角度

private:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	/// <summary>
	/// 無敵タイマー更新
	/// </summary>
	void InvincibleTimer();

private:
	// ★追加: パラメータ管理クラス
	PlayerStatus* m_status = nullptr;

	// ★追加: コントローラーから渡される移動ベクトル
	Vector3 m_velocity = Vector3::Zero;

	// ステートマシン
	std::unique_ptr<app::player::PlayerStateMachine> m_stateMachine;

	// ダメージ関連
	Vector3 m_knockBackDirection = Vector3::Zero;
	float	m_knockBackTimer = 0.0f;
	bool	m_isBlinking = false;
	bool	m_isInvincible = false;
	float   m_invincibleTimer = 0.0f;

	// アニメーション設定
	static const Character::AnimationOption PLAYER_ANIMATION_OPTIONS[];
};