/**
 * StateMachineBase.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachineBase.h"


namespace app
{
	namespace core
	{
		StateMachineBase::~StateMachineBase()
		{
			/** メモリ解放 */
			for (auto& pair : m_stateMap) {
				delete pair.second;
			}
			m_stateMap.clear();
		}


		void StateMachineBase::Update()
		{
			/** ステートの切り替え */
			ChangeState();
			/** 現在のステートの更新 */
			if (m_currentState) {
				m_currentState->Update();
			}
		}


		void StateMachineBase::ChangeState()
		{
			/** 切り替え先のステートを取得 */
			m_nextState = GetChangeState();

			if (m_nextState != nullptr && m_currentState != m_nextState) {
				/** 今のステートを終了 */
				if (m_currentState) m_currentState->Exit();
				/** 新しいステートに変更 */
				m_currentState = m_nextState;
				/** 新しいステートを開始 */
				m_currentState->Enter();
				/** 次のステートを無にする */
				m_nextState = nullptr;
			}
		}


		IState* StateMachineBase::FindState(const uint8_t stateId)
		{
			auto it = m_stateMap.find(stateId);
			if (it != m_stateMap.end()) {
				return it->second;
			}
			return nullptr;
		}
	}
}