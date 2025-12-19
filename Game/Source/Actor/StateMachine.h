/**
 * StateMachine.h
 * 状態遷移を管理する基底クラス群
 */
#pragma once
#include <map>

 // 前方宣言
class IGameObject;

namespace app
{
	/**
	 * 状態の基底クラス（インターフェース）
	 * 全てのステート（Idle, Walk, Jump...）はこれを継承します
	 */
	class IState
	{
	protected:
		IGameObject* m_owner = nullptr; // 持ち主（Playerなど）

	public:
		IState(IGameObject* owner) : m_owner(owner) {}
		virtual ~IState() {}

		// 開始時に1回だけ呼ばれる
		virtual void Enter() {}

		// 毎フレーム呼ばれる（メイン処理）
		virtual void Update() {}

		// 終了時に1回だけ呼ばれる
		virtual void Exit() {}

		// 次の状態へ移るべきかチェックする
		// 戻り値: trueなら遷移する。 requestStateIdに次のIDを入れる。
		virtual bool RequestState(int& requestStateId) { return false; }

		// 持ち主を型キャストして取得する便利関数
		template <typename T>
		T* GetOwner()
		{
			return static_cast<T*>(m_owner);
		}
	};

	/**
	 * ステートマシン本体
	 * 複数のステートを保持し、現在のステートを切り替えて実行する
	 */
	class StateMachineBase
	{
	protected:
		// 全てのステートをID付きで保存する辞書
		std::map<int, IState*> m_stateMap;

		// 現在実行中のステート
		IState* m_currentState = nullptr;

	public:
		virtual ~StateMachineBase();

		// 更新処理（ステートの切り替え判定と実行）
		virtual void Update();

		// ステートを追加するテンプレート関数
		// 例: AddState<IdleState>(STATE_ID_IDLE, owner);
		template<typename TState, typename TOwner>
		void AddState(const int stateId, TOwner* owner)
		{
			m_stateMap[stateId] = new TState(owner);
		}

		// 最初のステートを設定する
		void InitializeState(const int stateId);

		// 指定したIDのステートを取得する
		IState* FindState(const int stateId);
	};
}