/**
 * CollisionManager.h
 * 当たり判定管理クラス
 */
#pragma once


namespace app
{
	/** 前方宣言 */
	namespace actor { class Actor; }


	namespace collision
	{
		/**
		 * 判定を検証するペアの中身を区別するための列挙型
		 */
		enum class EnCollisionType : uint8_t
		{
			None = 0,
			Player,
			BasicEnemy,
			DeformEnemy,
			BossEnemy,
			Environment,
			//
			Num,
		};


		/**
		 * 当たり判定情報をまとめる構造体
		 */
		struct CollisionInformation
		{
			EnCollisionType m_type = EnCollisionType::None;
			CollisionObject* m_collision = nullptr;
			IGameObject* m_object = nullptr;
			//
			CollisionInformation(const EnCollisionType type, CollisionObject* collision, IGameObject* object) : m_type(type), m_collision(collision), m_object(object) {}
		};


		/**
		 * 当たり判定ペアをまとめる構造体
		 */
		struct CollisionPair
		{
			CollisionInformation* m_left = nullptr;
			CollisionInformation* m_right = nullptr;
			//
			CollisionPair(CollisionInformation* left, CollisionInformation* right) : m_left(left), m_right(right) {}
		};




		/********************************/


		/**
		 * 当たり判定管理クラス
		 */
		class CollisionHitManager
		{
			/**
			 * コライダーを生成し、コリジョンヒットマネージャーに登録する
			 */
		public:
			/**
			 * ボックス型
			 * ・コライダーの持ち主
			 * ・当たり判定の種類
			 * ・Vector3(幅,高さ,奥行)
			 * ・コリジョン属性
			 */
			CollisionObject* CreateCollider(
				app::actor::Actor* ins,
				const EnCollisionType type,
				const Vector3 size,
				const EnCollisionAttr index
			);

			/**
			 * 球型
			 * ・コライダーの持ち主
			 * ・当たり判定の種類
			 * ・半径
			 * ・コリジョン属性
			 */
			CollisionObject* CreateCollider(
				app::actor::Actor* ins,
				const EnCollisionType type,
				const float radius,
				const EnCollisionAttr index
			);

			/**
			 * カプセル型
			 * ・コライダーの持ち主
			 * ・当たり判定の種類
			 * ・半径
			 * ・高さ
			 * ・コリジョン属性
			 */
			CollisionObject* CreateCollider(
				app::actor::Actor* ins,
				const EnCollisionType type,
				const float radius,
				const float height,
				const EnCollisionAttr index
			);

			/** コライダーの座標と回転を更新する */
			void UpdateCollider(
				app::actor::Actor* ins,			/** コライダーの持ち主		*/
				CollisionObject* collider,		/** 行進するコライダー		*/
				const float offset = 0.0f		/** Up方向の補正値			*/
			);

			/** 登録解除を行い、コライダーをdelete、nullptrする */
			static CollisionObject* DeleteCollider(CollisionObject* collision);

			/** コライダーに属性IDを設定します。（RayTestで無視させるために使用） */
			void SetIsTrigger(CollisionObject* collider, EnCollisionAttr index);


		private:
			/** 当たり判定オブジェクトのリスト */
			std::vector<CollisionInformation> m_collisionInformationList;
			/** 当たり判定のペア */
			std::vector<CollisionPair> m_collisionPairList;


		private:
			CollisionHitManager();
			~CollisionHitManager();


		public:
			void Update();


		public:
			/** 当たり判定オブジェクトを登録する */
			void Register(const EnCollisionType type, CollisionObject* collisionObject, IGameObject* gameObject);
			/** 当たり判定オブジェクトの登録を解除する */
			void Unregister(CollisionObject* collisionObject);


		private:
			/**
			 * NOTE:
			 * 　ペアが該当する組み合わせ（例: プレイヤー＆基本エネミー）の場合は処理を実行し、trueを返す
			 * 　それ以外はfalseを返し、Update関数内の次の判定に移る
			 */

			 /** Player & BasicEnemy の衝突処理 */
			bool UpdateHitPlayerBasicEnemy(CollisionPair& pair);

			/** Player & DeformEnemy の衝突処理 */
			bool UpdateHitPlayerDeformEnemy(CollisionPair& pair);

			/** Player & BossEnemy の衝突処理 */
			bool UpdateHitPlayerBossEnemy(CollisionPair& pair);

			/** BasicEnemy & DeformEnemy の衝突処理 */
			bool UpdateHitBasicEnemyDeformEnemy(CollisionPair& pair);

			/** DeformEnemy & BossEnemy の衝突処理 */
			bool UpdateHitDeformEnemyBossEnemy(CollisionPair& pair);

			/** 指定したクラスを取得する */
			template <typename T>
			T* GetTargetObject(CollisionPair& pair, const EnCollisionType type)
			{
				if (pair.m_left->m_type == type) {
					return static_cast<T*>(pair.m_left->m_object);
				}
				else if (pair.m_right->m_type == type) {
					return static_cast<T*>(pair.m_right->m_object);
				}
				return nullptr;
			}


			/**
			 * シングルトン関連
			 */
		private:
			static CollisionHitManager* m_instance;


		public:
			static CollisionHitManager* CreateInstance()
			{
				if (m_instance == nullptr) {
					m_instance = new CollisionHitManager();
				}
				return m_instance;
			}
			static CollisionHitManager* GetInstance()
			{
				return m_instance;
			}
			static bool GetIsAvailable()
			{
				return m_instance != nullptr;
			}
			static void Delete()
			{
				if (m_instance != nullptr) {
					delete m_instance;
					m_instance = nullptr;
				}
			}
		};




		/********************************/


		/**
		 * 当たり判定管理クラスを更新したりするためのゲームオブジェクト。
		 */
		class CollisionManagerObject : public IGameObject
		{
		public:
			CollisionManagerObject();
			~CollisionManagerObject();


		private:
			bool Start() override final;
			void Update() override final;
			/** 描画はしない */
			void Render(RenderContext& renderContext) override final {}
		};
	}
}