/**
 * StateMachineBase.h
 * 状態遷移を管理する基底クラス群
 */
#pragma once
#include <unordered_map>
#include <cstdint>
#include "Source/Actor/Actor.h"


namespace app
{
	namespace actor
	{
		/** 前方宣言 */
		class StateMachineBase;
		class Actor;


		/**
		 * 状態の基底クラス（インターフェース）
		 */
		class IState
		{
		protected:
			/** ステートの持ち主（ステートマシン） */
			StateMachineBase* m_owner = nullptr;

		public:
			IState(StateMachineBase* owner) : m_owner(owner) {}
			virtual ~IState() {}

			/** 開始時に1回だけ呼ばれます。 */
			virtual void Enter() = 0;
			/** 毎フレーム呼ばれます（メイン処理）。 */
			virtual void Update() = 0;
			/** 終了時に1回だけ呼ばれます。 */
			virtual void Exit() = 0;
		};




		/********************************/


		/**
		 * ステートマシン本体
		 * 複数のステートを保持し、現在のステートを切り替えて実行します。
		 */
		class StateMachineBase
		{
		public:
			/**
			 * アニメーション再生処理のテンプレート関数
			 * 例: m_stateMachine->PlayAnimation(EnPlayerAnimClip::Idle);
			 */
			template <typename TEnum>
			void PlayAnimation(TEnum animId)
			{
				m_owner->GetModelRender()->PlayAnimation(static_cast<int>(animId));
			}


		protected:
			/** ステートの持ち主（ステートマシンを持つActor） */
			Actor* m_owner = nullptr;
			/** 全てのステートをID付きで保存する辞書 */
			std::unordered_map<uint8_t, IState*> m_stateMap;
			/** 現在実行中のステート */
			IState* m_currentState = nullptr;
			/** 次に変更するステート */
			IState* m_nextState = nullptr;


		public:
			StateMachineBase(Actor* owner);
			virtual ~StateMachineBase();

			/**
			 * 更新処理（ステートの切り替え判定と実行）
			 * これをIGameObjectを継承した持ち主のUpdateで呼び出してください。
			 * 必要に応じてオーバーライドしてもかまいません。
			 * 例: m_playerStateMachine->Update();
			 */
			virtual void Update();

			/** ステート変更 */
			void ChangeState();


		protected:
			/**
			 * ステートを追加するテンプレート関数
			 */
			template<typename TState, typename... Args>
			void AddState(const uint8_t stateId, Args... args)
			{
				auto it = m_stateMap.find(stateId);
				if (it != m_stateMap.end()) {
					delete it->second;
					K2_ASSERT(false, "IDが重複しています。");
				}
				m_stateMap[stateId] = new TState(args...);
			}

			/** 指定したIDのステートを取得します。 */
			IState* FindState(const uint8_t stateId);


		protected:
			/**
			 * 現在ステートが指定したステートならtrueを返します。
			 * 現在のステートが何かによって処理を分岐したい場合に使用します。
			 * 主にChangeState内で使用します。
			 */
			inline bool IsEqualCurrentState(const uint8_t state)
			{
				return m_currentState == m_stateMap[state];
			}

			/**
			 * 次のステートが指定したステートならtrueを返します。
			 * 次のステートが何かによって処理を分岐したい場合に使用します。
			 * 主に各IStateのExit内で使用します。
			 */
			inline bool IsEqualNextState(const uint8_t state)
			{
				return m_nextState == m_stateMap[state];
			}


		protected:
			/**
			 * 変更するステートを取得します。
			 * ステートの種類や、変更する条件は各クラスで異なるため、
			 * ここは派生クラスでオーバーライドして実装してください。
			 * この関数自体はStateMachineBaseのUpdate内で呼び出されているため、
			 * 派生先のUpdateで改めて呼び出す必要はありません。
			 */
			virtual IState* GetChangeState() = 0;
		};
	}
}