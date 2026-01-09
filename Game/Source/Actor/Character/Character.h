/**
 * Character.h
 * キャラクターとなる要素をもったクラス
 */
#pragma once
#include "Source/Actor/Actor.h"
#include "Source/Actor/ActorStatus.h"


namespace app
{
	namespace actor
	{
		class Character : public Actor
		{
		public:
			/**
			 * やられ判定を取得
			 */
			inline CollisionObject* GetHurtCollider() const { return m_hurtCollider; }
			/**
			 * 体の当たり判定を取得
			 */
			inline CollisionObject* GetHitCollider() const { return m_hitCollider; }
			/**
			 * 一時的な攻撃判定を取得
			 */
			inline CollisionObject* GetAttackHitCollider() const { return m_attackHitCollider; }


		protected:
			/** アニメーションクリップのリスト */
			std::vector<AnimationClip*> m_animationClipList;

			/** やられ判定 */
			CollisionObject* m_hurtCollider = nullptr;
			/** 体の当たり判定 */
			CollisionObject* m_hitCollider = nullptr;
			/** 一時的な攻撃判定 */
			CollisionObject* m_attackHitCollider = nullptr;


		public:
			Character();
			~Character();


		protected:
			virtual bool Start() override;
			virtual void Update() override;
			virtual void Render(RenderContext& rc) override {};


		protected:
			/**
			 * アニメーションファイルのオプションを管理する構造体。
			 * 継承先の.cppで定義すること。
			 */
			struct AnimationOption
			{
				std::string fileName;	/** ファイルパス */
				bool is_loop = false;	/** リピートするかどうか（true = する、false = しない） */
			};


			/**
			 * モデルとアニメーションの初期化を行う。
			 */
			void InitModel(
				const uint8_t count,			/** アニメーションクリップの数 */
				const AnimationOption* option,	/** アニメーションクリップのオプション配列 */
				const std::string path,			/** モデルファイルのパス */
				const float scale				/** モデルの拡大率 */
			);
		};
	}
}