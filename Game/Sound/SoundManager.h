/**
 * SoundManager.h
 * サウンドマネージャー
 */
#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>

 /** エンジンのクラスを前方宣言 */
namespace nsK2EngineLow {
	class SoundSource;
}


namespace app
{
	namespace sound
	{
		/** サウンドリスト */
		enum EnSoundList :uint8_t
		{
			enSoundList_TitleBGM,
			enSoundList_FirstStageBGM,
			enSoundList_BossStageBGM,
			enSoundList_PushSE,
			enSoundList_PlayerJumpSE,
			enSoundList_PlayerStep1SE,
			enSoundList_PlayerStep2SE,
			enSoundList_PlayerRunStart,
			enSoundList_PlayerRunLoop,
			enSoundList_PlayerDamage,
			enSoundList_PlayerDie,
			enSoundList_PlayerDead,
			enSoundList_Stomp,
			enSoundList_SlidingStart,
			enSoundList_SlidingLoop,
			enSoundList_BossStep,
			enSoundList_BossHowl,
			enSoundList_BossAttack,
			enSoundList_BossDamage,
			enSoundList_BossDeadVoice,
			enSoundList_BossDead,
			enSoundList_GameClear,
			enSoundList_GameOver,
			enSoundList_GameOverSlip,
			//
			enSoundList_Num
		};




		/********************************/


		/**
		 * サウンド管理クラス
		 * エンジンの3D機能を使わず、自前で距離減衰を計算する
		 */
		class SoundManager
		{
		public:
			/**
			 * 指定した音を再生する
			 * BGM: Play(ID,true,false);
			 * 2DSE: Play(ID);
			 * 3DSE: Play(ID,false,true,position);
			 * ループ3DSE: Play(ID,true,true,position);
			 */
			static nsK2EngineLow::SoundSource* Play(
				EnSoundList soundId,
				bool isLoop = false,
				bool is3D = false,
				const Vector3& position = Vector3::Zero
			);

			/**
			 * 指定したIDのBGMを停止する
			 */
			static void StopBGM(EnSoundList soundId, float fadeTime = 0.0f);

			/**
			 * 再生中のBGMをすべて停止する
			 */
			static void StopAllBGM(float fadeTime = 0.0f);

			/**
			 * 指定したIDのBGMの音量を設定する
			 */
			static void SetVolume(EnSoundList soundId, float volume);

			/**
			 * 全てのBGMをフェードインさせる
			 */
			static void FadeInAllBGM(float fadeTime);

			/**
			 * 疑似3Dリストから音源を登録解除する。
			 * ※SoundSourceが削除される直前に必ず呼ぶ必要がある
			 */
			static void UnregisterPseudo3D(nsK2EngineLow::SoundSource* source);


		private:
			/** サウンド定義構造体 */
			struct SoundDef
			{
				const char* fileName;	/** ファイル名	*/
				float volume;			/** 音量		*/
			};

			/** 疑似3Dサウンド（距離減衰させる音）の管理構造体 */
			struct Pseudo3DState
			{
				nsK2EngineLow::SoundSource* source;	/** 音源           */
				float baseVolume;					/** 元の音量       */
				bool isLoop;						/** ループさせるか */
			};

			/** フェードアウト情報を管理する構造体 */
			struct FadeState
			{
				nsK2EngineLow::SoundSource* source; /** 操作する音源  */
				float decreaseSpeed;                /** 1秒で下げる量 */
			};

			/** フェードイン情報を管理する構造体 */
			struct FadeInState
			{
				nsK2EngineLow::SoundSource* source;	/** 操作する音源  */
				float currentVolume;				/** 現在の音量	  */
				float targetVolume;					/** 目標音量	  */
				float increaseSpeed;				/** 1秒で上げる量 */
			};


			static const SoundDef m_soundDefs[enSoundList_Num];				/** サウンド定義リスト	 */
			std::map<EnSoundList, nsK2EngineLow::SoundSource*> m_bgmMap;	/** 再生中BGMリスト		 */
			std::list<Pseudo3DState> m_pseudo3DList;						/** 疑似3Dサウンドリスト */
			std::list<FadeState> m_fadeList;								/** フェードアウト待ち	 */
			std::list<FadeInState> m_fadeInList;							/** フェードイン待ち	 */


		private:
			SoundManager();
			~SoundManager();


		public:
			/** 初期化処理 */
			void Init();
			/** サウンドマネージャーオブジェクトで呼び出すためpublic */
			void Update();


			/**
			 * シングルトン関連
			 */
		private:
			static SoundManager* m_instance;

		public:
			static SoundManager* CreateInstance()
			{
				if (m_instance == nullptr) {
					m_instance = new SoundManager();
				}
				return m_instance;
			}
			static SoundManager* GetInstance()
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
		 * SoundSourceを継承した自作クラス
		 * エンジン側のファイルを汚さずに、削除時の通知機能を追加する
		 */
		class GameSoundSource : public nsK2EngineLow::SoundSource
		{
		public:
			/** 自分が消える時にマネージャーへ連絡する */
			~GameSoundSource()
			{
				SoundManager::UnregisterPseudo3D(this);
			};
		};




		/********************************/


		/**
		 *  サウンドマネージャーを動かすためのゲームオブジェクト
		 */
		class SoundManagerObject : public IGameObject
		{
		public:
			SoundManagerObject();
			~SoundManagerObject();


		private:
			bool Start() override;
			void Update() override;
		};
	}
}