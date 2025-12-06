/**
 * PlayerStatus.cpp
 * パラメータ読み込みの実装
 */
#include "stdafx.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
	/**
	 * ここでマネージャーに「読み込み」を依頼します。
	 * もし既に他の誰かが読み込んでいれば、マネージャーは読み込みをスキップしてくれます。
	 */
	ParameterManager::GetInstance()->LoadParameter<MasterPlayerStatusParameter>(
		"Assets/parameter/PlayerStatus.json", // 読み込むファイルパス
		[&](const nlohmann::json& j, MasterPlayerStatusParameter& p)
		{
			// ▼▼▼ ここが指示書（callback）の中身！ ▼▼▼

			// JSONの "walkSpeed" を探して、構造体の walkSpeed に入れる
			// 第二引数(10.0f)は、万が一JSONに書き忘れていた時のデフォルト値です
			p.walkSpeed = j.value("walkSpeed", 10.0f);

			// 走り速度
			p.runSpeed = j.value("runSpeed", 20.0f);

			// ジャンプ力
			p.jumpPower = j.value("jumpPower", 30.0f);

			// ▲▲▲ 指示書おわり ▲▲▲
		}
	);
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::Load()
{
	// マネージャーの保管庫から、完成したデータを借りてくる
	// IDは MasterPlayerStatusParameter::ID() で自動解決されます
	m_param = ParameterManager::GetInstance()->GetParameter<MasterPlayerStatusParameter>();
}