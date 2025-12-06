/**
 * StateMachine.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachine.h"

namespace app
{
	StateMachineBase::~StateMachineBase()
	{
		// メモリ解放
		for (auto& pair : m_stateMap) {
			delete pair.second;
		}
		m_stateMap.clear();
	}

	void StateMachineBase::Update()
	{
		if (m_currentState == nullptr) return;

		int requestStateId = 0;

		// 1. 現在のステートに「次の状態に行きたい？」と聞く
		if (m_currentState->RequestState(requestStateId))
		{
			// 行きたいと言われたら...

			// 2. 現在のステートを終了(Exit)
			m_currentState->Exit();

			// 3. 次のステートを探して切り替え
			IState* nextState = FindState(requestStateId);
			if (nextState) {
				m_currentState = nextState;
			}

			// 4. 新しいステートを開始(Enter)
			m_currentState->Enter();
		}

		// 5. 現在のステートの更新処理を実行
		m_currentState->Update();
	}

	void StateMachineBase::InitializeState(const int stateId)
	{
		m_currentState = FindState(stateId);
		if (m_currentState) {
			m_currentState->Enter();
		}
	}

	IState* StateMachineBase::FindState(const int stateId)
	{
		auto it = m_stateMap.find(stateId);
		if (it != m_stateMap.end()) {
			return it->second;
		}
		return nullptr;
	}
}