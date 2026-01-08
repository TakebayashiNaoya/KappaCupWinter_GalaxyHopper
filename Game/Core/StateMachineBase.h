/**
 * StateMachineBase.h
 * 純粋な状態遷移を管理する基底クラス群
 */
#pragma once
#include <cstdint>
#include <unordered_map>


namespace app
{
	namespace core
	{
		/** 前方宣言 */
		class StateMachineBase;


		/**
		 * 状態の基底クラス（インターフェース）
		 */
		class IState
		{
		public:
			IState(StateMachineBase* owner) : m_owner(owner) {}
			virtual ~IState() {}

			/** 開始時に1回だけ呼ばれます。 */
			virtual void Enter() = 0;
			/** 毎フレーム呼ばれます（メイン処理）。 */
			virtual void Update() = 0;
			/** 終了時に1回だけ呼ばれます。 */
			virtual void Exit() = 0;


		protected:
			/** 自身のオーナーであるステートマシンを取得 */
			template <typename T>
			T* GetOwnerMachine() const
			{
				T* casted = dynamic_cast<T*>(m_owner);

				/** 中身があるのにキャストしたらnullptrになる場合、型指定が間違っている */
				if (m_owner && !casted) {
					assert(false && "GetOwnerMachine: 型指定が間違っています");
				}
				return casted;
			}


		private:
			StateMachineBase* m_owner;
		};




		/********************************/


		/**
		 * ステートマシン本体
		 * 複数のステートを保持し、現在のステートを切り替えて実行します。
		 */
		class StateMachineBase
		{
		protected:
			/** 全てのステートをID付きで保存する辞書 */
			std::unordered_map<uint8_t, IState*> m_stateMap;
			/** 現在実行中のステート */
			IState* m_currentState = nullptr;
			/** 次に変更するステート */
			IState* m_nextState = nullptr;


		public:
			StateMachineBase() {};
			virtual ~StateMachineBase();

			/**
			 * 更新処理（ステートの切り替え判定と実行）
			 */
			virtual void Update();

			/** ステート変更 */
			void ChangeState();


		protected:
			/**
			 * ステートを追加するテンプレート関数
			 * 派生先のステートマシンでラップして、ステートマシン、オーナー、ステータスを渡す
			 */
			template<typename TState, typename... Args>
			void AddState(const uint8_t stateId)
			{
				auto it = m_stateMap.find(stateId);
				if (it != m_stateMap.end()) {
					delete it->second;
					K2_ASSERT(false, "IDが重複しています。");
				}
				m_stateMap[stateId] = new TState(this);
			}

			/** 指定したIDのステートを取得します。 */
			IState* FindState(const uint8_t stateId);


		protected:
			/** 現在ステートチェック */
			inline bool IsEqualCurrentState(const uint8_t state)
			{
				return m_currentState == m_stateMap[state];
			}

			/** 次のステートチェック */
			inline bool IsEqualNextState(const uint8_t state)
			{
				return m_nextState == m_stateMap[state];
			}


		protected:
			/** 変更するステートを取得します（派生先で実装） */
			virtual IState* GetChangeState() = 0;
		};
	}
}