/**
 * StateMachineBase.cpp
 * ステートマシンの実装
 */
#include "stdafx.h"
#include "StateMachineBase.h"
#include "Source/Actor/Actor.h"


namespace app
{
	namespace actor
	{
		StateMachineBase::StateMachineBase(Actor* owner)
			: m_owner(owner)
		{
		};


		StateMachineBase::~StateMachineBase()
		{
			/** メモリ解放 */
			for (auto& pair : m_stateMap) {
				/** マップに登録されているステートを削除 */
				delete pair.second;
			}
			/** 入れ物自体を消去 */
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
			/**
			 * ステートが切り替わった時（m_nextStateがnullptrじゃない時）かつ、
			 * 今のステートと次のステートが同じではないとき
			 */
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
			/** 指定したIDのステートが存在すればそのステートのポインタを返し、なければnullptrを返す */
			auto it = m_stateMap.find(stateId);
			if (it != m_stateMap.end()) {
				return it->second;
			}
			return nullptr;
		}
	}
}