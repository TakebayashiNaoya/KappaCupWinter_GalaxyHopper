/**
 * PlayerController.h
 * プレイヤーを操作する「頭脳」クラス
 */
#pragma once

 // 操作対象（肉体）を知っておく必要がある
class Player;

class PlayerController : public IGameObject
{
public:
	PlayerController();
	~PlayerController();

	bool Start() override;
	void Update() override;

	// 操作する対象をセットする関数
	void SetTarget(Player* target) { m_target = target; }

private:
	// 操作対象のプレイヤー（肉体）
	Player* m_target = nullptr;
};