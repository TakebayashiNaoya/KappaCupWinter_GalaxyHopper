#include "stdafx.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Source/Collision/CollisionManager.h"

// アニメーション設定
const Character::AnimationOption Player::PLAYER_ANIMATION_OPTIONS[] = {
   {"Player/idle",	true},
   {"Player/walk",	true},
   {"Player/run",	true},
   {"Player/down",	true},
   {"Player/dead",	false},
};

namespace
{
	const std::string MODEL_PATH = "Player/rabbit";
	constexpr float MODEL_SCALE = 200.0f;

	// コライダー設定などはまだJSONにしていないので定数のまま
	constexpr float HURT_COLLIDER_RADIUS = 30.0f;
	constexpr float HURT_COLLIDER_HEIGHT = 60.0f;
	constexpr float COLLIDER_OFFSET = 50.0f;

	constexpr float INITIAL_KNOCK_BACK_SPEED = 10.0f;
	constexpr float KNOCK_BACK_DAMPING = 10.0f;
	constexpr float INVINCIBLE_TIME = 5.0f;
	constexpr int LIFE = 3;
}

Player::Player()
{
	// ★追加: パラメータの読み込み
	m_status = new PlayerStatus();
	m_status->Load();

	// ステートマシンの生成
	m_stateMachine = std::make_unique<app::player::PlayerStateMachine>(this);
}

Player::~Player()
{
	// ★追加: パラメータの破棄
	delete m_status;

	// コライダーの削除
	m_hurtCollider = CollisionHitManager::DeleteCollider(m_hurtCollider);
	m_attackCollider = CollisionHitManager::DeleteCollider(m_attackCollider);
}

bool Player::Start()
{
	// モデルとアニメーションを初期化
	InitModel(enAnimationClip_Num, PLAYER_ANIMATION_OPTIONS, MODEL_PATH, MODEL_SCALE);
	InitLife(LIFE);

	// 初期ステートを設定
	m_stateMachine->InitializeState(enPlayerState_Idle);

	// やられ判定のコライダーを作成
	if (CollisionHitManager::IsAvailable()) {
		m_hurtCollider = CollisionHitManager::GetInstance()->CreateCollider(
			this,
			enCollisionType_Player,
			HURT_COLLIDER_RADIUS,
			true
		);
	}

	// アニメーションイベント登録
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	return true;
}

void Player::Update()
{
	// ポーズ中または戦闘終了時は更新しない
	if (BattleManager::GetIsBattleFinish()) {
		StopLoopSound();
		return;
	}

	// 「惑星の中心→キャラ」のベクトルを更新
	UpdateUpDirection();
	m_xzAdditionalRot = Quaternion::Identity;

	// ★ステートマシンの更新（ここでMoveUpdate等が呼ばれる）
	if (m_stateMachine) {
		m_stateMachine->Update();
	}

	// ★重要: コントローラーからの命令は1フレーム限りなのでリセットする
	m_velocity = Vector3::Zero;

	// コライダーの更新
	if (CollisionHitManager::IsAvailable()) {
		CollisionHitManager::GetInstance()->UpdateCollider(this, m_hurtCollider, COLLIDER_OFFSET);
	}

	// 無敵時間の更新
	InvincibleTimer();

	// モデルの更新
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	if (m_life <= 0) {
		SetIsDying(true);
	}
}

void Player::Render(RenderContext& rc)
{
	// 無敵時間中は点滅
	if (m_isInvincible) {
		m_isBlinking = !m_isBlinking;
		if (m_isBlinking) {
			m_modelRender.Draw(rc);
		}
	}
	else {
		m_modelRender.Draw(rc);
	}
}

// 移動更新
void Player::MoveUpdate(const float speed)
{
	// ★変更: m_velocity（コントローラーからの入力）を使って移動
	// m_velocityは既にカメラ方向などを考慮済み
	Vector3 moveVec = m_velocity;

	// 入力がある場合のみ移動処理
	if (moveVec.LengthSq() > 0.001f) {
		moveVec.Normalize();

		// 水平方向の移動（速度は引数で指定）
		m_moveSpeed += moveVec * speed;

		// キャラクターの向きを変更（進行方向に向く）
		// 重力方向を考慮した回転計算
		Vector3 up = m_upDirection;
		Vector3 right = Vector3::Zero;
		right.Cross(up, moveVec); // 右方向
		right.Normalize();
		Quaternion rot;
		// 簡易的な回転（実際はCalcCameraRotation等と組み合わせる）
		m_rotation.SetRotation(Vector3::Front, moveVec);
	}

	// 垂直方向（重力・ジャンプ）を加算
	m_moveSpeed += CalcVerticalVelocity();

	// 最終的な移動
	ComputePosition();
}

// カメラ回転（Controller化で少し役割が変わりますが、一旦維持）
void Player::CalcCameraRotation()
{
	// m_velocity を基準に計算するように変更
	if (m_velocity.LengthSq() <= 0.001f) {
		return;
	}

	Vector3 forwardDirection = m_velocity;
	forwardDirection.Normalize();
	Vector3 upDirection = m_upDirection;

	Vector3 xzDirection;
	xzDirection.Cross(upDirection, forwardDirection);
	xzDirection.Normalize();

	float dotResult = m_upDirection.Dot(m_beforeUpDirection);
	dotResult = Math::Clamp(dotResult, -1.0f, 1.0f);
	float m_rotationAngle = acosf(dotResult);

	Vector3 m_rotationDirection = Vector3::Zero;
	m_rotationDirection.Cross(m_beforeUpDirection, m_upDirection);

	if (m_rotationDirection.Dot(xzDirection) < 0.0f) {
		m_rotationAngle *= -1.0f;
	}

	m_xzAdditionalRot.SetRotation(xzDirection, m_rotationAngle);
}

// ノックバック方向計算
void Player::ComputeKnockBackDirection(const Vector3& enemyPos)
{
	Vector3 directionToEnemy = enemyPos - m_position;
	directionToEnemy.Normalize();
	Vector3 attackedDirection = ProjectOnPlane(directionToEnemy, m_upDirection);
	m_knockBackDirection = attackedDirection * -1.0f;
	m_knockBackDirection.Normalize();
}

// ノックバック処理
void Player::KnockedBack()
{
	m_knockBackTimer += g_gameTime->GetFrameDeltaTime();
	float knockedBackSpeed = INITIAL_KNOCK_BACK_SPEED - (KNOCK_BACK_DAMPING * m_knockBackTimer);

	if (knockedBackSpeed < 0.0f)
	{
		m_isAttacked = false;
		return;
	}

	m_moveSpeed += m_knockBackDirection * knockedBackSpeed;
	m_moveSpeed += CalcVerticalVelocity();
	ComputePosition();
}

// 踏みつけジャンプ
void Player::StompJump()
{
	m_moveSpeed = Vector3::Zero;

	// ★変更: JSONからジャンプ力を取ることも可能だが、ここは特殊アクションなので
	// 必要なら STOMP_JUMP_POWER もJSONに入れると良い
	m_initialJumpSpeed = 30.0f; // 仮

	m_fallTimer = 0.0f;
}

// 無敵タイマー
void Player::InvincibleTimer()
{
	if (!m_isInvincible) return;

	m_invincibleTimer += g_gameTime->GetFrameDeltaTime();
	if (m_invincibleTimer >= INVINCIBLE_TIME) {
		m_isInvincible = false;
		m_invincibleTimer = 0.0f;
	}
}

// アニメーションイベント
void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"first_step") == 0) {
		SoundManager::Play(enSoundList_PlayerStep1SE);
	}
	else if (wcscmp(eventName, L"second_step") == 0) {
		SoundManager::Play(enSoundList_PlayerStep2SE, false, true, m_position);
	}
	else if (wcscmp(eventName, L"die") == 0) {
		SoundManager::Play(enSoundList_PlayerDie);
	}
	else if (wcscmp(eventName, L"dead") == 0) {
		SoundManager::Play(enSoundList_PlayerDead);
	}
}