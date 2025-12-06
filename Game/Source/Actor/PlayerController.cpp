/**
 * PlayerController.cpp
 * コントローラー入力をプレイヤーの動きに変換する
 */
#include "stdafx.h"
#include "PlayerController.h"
#include "Player.h" // Playerの中身を操作するのでインクルード

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

bool PlayerController::Start()
{
	return true;
}

void PlayerController::Update()
{
	// 操作対象がいなければ何もしない
	if (m_target == nullptr) return;

	// 1. 入力を取得（ここが頭脳の仕事！）
	// XとYの入力を取得して、Z(奥)方向への移動に変換しています
	Vector3 stickL = Vector3(g_pad[0]->GetLStickXF(), 0.0f, g_pad[0]->GetLStickYF());

	// 2. カメラに合わせて移動方向を計算
	Vector3 moveDir = Vector3::Zero;
	if (stickL.LengthSq() > 0.001f) {
		// カメラの前方向・右方向を取得
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

		// 上下成分（Y）を消して、水平な移動にする
		forward.y = 0.0f;
		right.y = 0.0f;
		forward.Normalize();
		right.Normalize();

		// 入力とカメラの向きを合成
		moveDir = forward * stickL.z + right * stickL.x;
	}

	// 3. 肉体（Player）に「こっちに動け」と命令する
	// ※この関数(SetVelocity)は後でPlayerに作ります
	m_target->SetVelocity(moveDir);
}