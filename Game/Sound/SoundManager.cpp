/**
 * SoundManager.h
 * サウンドマネージャーの実装
 */
#include "stdafx.h"
#include "SoundManager.h"
#include "Source/Actor/Character/Player/Player.h"


namespace app
{
	namespace sound
	{
		namespace
		{
			/** サウンドファイルの格納ディレクトリ */
			const std::string SOUND_DIR = "Assets/sound/";
			/** サウンドファイルの拡張子 */
			const std::string EXTENSION = ".wav";

			/** リスナー名（プレイヤー） */
			const char* LISTENER_NAME = "Player";

			/** 音が聞こえる限界距離 */
			constexpr float MAX_SOUND_DISTANCE = 1500.0f;

			/** 3D音源の距離減衰を計算する */
			float Calculate3DVolume(const Vector3& listenerPos, const Vector3& soundPos)
			{
				float distance = (listenerPos - soundPos).Length();
				float rate = 1.0f - (distance / MAX_SOUND_DISTANCE);
				if (rate < 0.0f) {
					rate = 0.0f;
				}
				else if (rate > 1.0f) {
					rate = 1.0f;
				}
				return rate;
			}
		}


		/** サウンド定義 */
		const SoundManager::SoundDef SoundManager::m_soundDefs[enSoundList_Num] =
		{
			/** fileName			volume */
			{ "TitleBGM",			0.5f },
			{ "FirstStageBGM",		0.5f },
			{ "BossStageBGM",		0.5f },
			{ "Push",				1.0f },
			{ "PlayerJump",			1.0f },
			{ "PlayerFirstStep",	0.5f },
			{ "PlayerSecondStep",	0.5f },
			{ "RunStart",			2.0f },
			{ "RunLoop",			2.0f },
			{ "PlayerDamage",		1.0f },
			{ "PlayerDie",			2.0f },
			{ "PlayerDead",			1.0f },
			{ "Stomp",				1.5f },
			{ "SlidingStart",		1.0f },
			{ "SlidingLoop",		0.8f },
			{ "BossStep",			1.5f },
			{ "BossHowl",			1.0f },
			{ "BossAttack",			3.0f },
			{ "BossDamage",			1.0f },
			{ "BossDeadVoice",		2.0f },
			{ "BossDead",			3.0f },
			{ "GameClear",			1.0f },
			{ "GameOver",			1.0f },
			{ "GameOverSlip",		1.0f },
		};


		SoundManager* SoundManager::m_instance = nullptr;


		SoundManager::SoundManager()
		{
		}


		SoundManager::~SoundManager()
		{
			StopAllBGM();
		}


		void SoundManager::Init()
		{
			/** 一括ロード */
			for (int i = 0; i < enSoundList_Num; i++) {
				std::string fullPath = SOUND_DIR + m_soundDefs[i].fileName + EXTENSION;
				g_soundEngine->ResistWaveFileBank(i, fullPath.c_str());
			}
		}


		void SoundManager::Update()
		{
			if (m_instance == nullptr) {
				return;
			}

			/** プレイヤー（リスナー）座標の取得 */
			Vector3 listenerPos = Vector3::Zero;
			actor::Player* player = FindGO<actor::Player>(LISTENER_NAME);
			if (player != nullptr) {
				listenerPos = player->GetTransform().m_position;
			}


			/**
			 * 3D音源の距離減衰処理
			 */
			auto it3D = m_instance->m_pseudo3DList.begin();
			while (it3D != m_instance->m_pseudo3DList.end())
			{
				/** 疑似3D状態取得 */
				Pseudo3DState& state = *it3D;

				/** 音源が無効、または停止していたらリストから削除 */
				if (state.source == nullptr || !state.source->IsPlaying()) {
					it3D = m_instance->m_pseudo3DList.erase(it3D);
					continue;
				}
				/** 音量計算 */
				if (player != nullptr) {
					float volumeRate = Calculate3DVolume(listenerPos, state.source->GetPosition());
					state.source->SetVolume(state.baseVolume * volumeRate);
				}
				++it3D;
			}


			/**
			 * フェードアウト処理
			 */
			auto itFade = m_instance->m_fadeList.begin();
			while (itFade != m_instance->m_fadeList.end())
			{
				/** フェードアウト状態取得 */
				FadeState& state = *itFade;
				float currentVol = state.source->GetVolume();
				currentVol -= state.decreaseSpeed * g_gameTime->GetFrameDeltaTime();

				/** 音量が0以下になったらフェードアウト完了 */
				if (currentVol <= 0.0f) {
					state.source->SetVolume(0.0f);
					state.source->Stop();
					DeleteGO(state.source);

					itFade = m_instance->m_fadeList.erase(itFade);
				}
				else {
					state.source->SetVolume(currentVol);
					++itFade;
				}
			}


			/**
			 * フェードイン処理
			 */
			auto itIn = m_instance->m_fadeInList.begin();
			while (itIn != m_instance->m_fadeInList.end())
			{
				/** フェードイン状態取得 */
				FadeInState& state = *itIn;
				state.currentVolume += state.increaseSpeed * g_gameTime->GetFrameDeltaTime();

				/** 目標音量に達したらフェードイン完了 */
				if (state.currentVolume >= state.targetVolume) {
					state.source->SetVolume(state.targetVolume);
					itIn = m_instance->m_fadeInList.erase(itIn);
				}
				else {
					state.source->SetVolume(state.currentVolume);
					++itIn;
				}
			}
		}


		SoundSource* SoundManager::Play(EnSoundList soundId, bool isLoop, bool is3D, const Vector3& position)
		{
			if (!GetIsAvailable()) {
				return nullptr;
			}

			SoundManager* instance = GetInstance();

			/** ループ音（BGM等）の重複防止 */
			if (isLoop && instance->m_bgmMap.count(soundId) > 0) {
				return instance->m_bgmMap[soundId];
			}

			/** GameSoundSource(デストラクタで自動登録解除してくれるクラス) を生成 */
			GameSoundSource* soundSource = NewGO<GameSoundSource>(0);

			/**
			 * エンジンには常に「2D(false)」として初期化させる
			 * NOTE: エンジンの3D音源はドップラー効果の不具合により、爆音が発生するため使用しない
			 */
			soundSource->Init(soundId, false);

			if (is3D)
			{
				/** 疑似3Dリストに登録する */
				soundSource->SetPosition(position);

				/** リストへ登録 */
				Pseudo3DState newState;
				newState.source = soundSource;
				newState.baseVolume = m_soundDefs[soundId].volume;
				newState.isLoop = isLoop;

				/** 生成直後の一瞬の爆音を防ぐため、初期音量を計算してセットしておく */
				actor::Player* player = FindGO<actor::Player>(LISTENER_NAME);
				if (player) {
					Vector3 listenerPos = player->GetTransform().m_position;
					float volumeRate = Calculate3DVolume(listenerPos, position);
					soundSource->SetVolume(newState.baseVolume * volumeRate);
				}
				else {
					soundSource->SetVolume(0.0f);
				}

				instance->m_pseudo3DList.push_back(newState);
			}
			else {
				/** 完全2Dの場合はそのままの音量を設定 */
				soundSource->SetVolume(m_soundDefs[soundId].volume);
			}

			soundSource->Play(isLoop);

			/** BGM管理マップへの登録（ループかつ非3Dのみ） */
			if (isLoop && !is3D) {
				instance->m_bgmMap[soundId] = soundSource;
			}

			return soundSource;
		}


		void SoundManager::UnregisterPseudo3D(nsK2EngineLow::SoundSource* source)
		{
			if (!GetIsAvailable()) {
				return;
			}

			SoundManager* instance = GetInstance();

			auto it = instance->m_pseudo3DList.begin();
			while (it != instance->m_pseudo3DList.end())
			{
				if (it->source == source) {
					instance->m_pseudo3DList.erase(it);
					break;
				}
				++it;
			}
		}


		void SoundManager::StopBGM(EnSoundList soundId, float fadeTime)
		{
			if (!GetIsAvailable()) {
				return;
			}

			/** BGM管理マップから指定のBGMを検索 */
			SoundManager* instance = GetInstance();
			auto it = instance->m_bgmMap.find(soundId);

			/** 指定したBGMが見つかったら停止処理 */
			if (it != instance->m_bgmMap.end())
			{
				SoundSource* ss = it->second;
				if (ss != nullptr)
				{
					if (fadeTime > 0.0f) {
						/** フェードリストへ移動 */
						float currentVol = ss->GetVolume();
						instance->m_fadeList.push_back({ ss, currentVol / fadeTime });
					}
					else {
						/** 即停止 */
						ss->Stop();
						DeleteGO(ss);
					}
				}
				instance->m_bgmMap.erase(it);
			}
		}


		void SoundManager::StopAllBGM(float fadeTime)
		{
			if (!GetIsAvailable()) {
				return;
			}

			/** BGM管理マップの全BGMを停止処理 */
			SoundManager* instance = GetInstance();
			auto it = instance->m_bgmMap.begin();

			/** 全BGMを停止 */
			while (it != instance->m_bgmMap.end())
			{
				SoundSource* ss = it->second;
				if (ss != nullptr)
				{
					if (fadeTime > 0.0f) {
						float currentVol = ss->GetVolume();
						instance->m_fadeList.push_back({ ss, currentVol / fadeTime });
					}
					else {
						ss->Stop();
						DeleteGO(ss);
					}
				}
				it = instance->m_bgmMap.erase(it);
			}
		}


		void SoundManager::SetVolume(EnSoundList soundId, float volume)
		{
			if (!GetIsAvailable()) {
				return;
			}

			SoundManager* instance = GetInstance();

			/** BGM管理マップから指定のBGMを検索 */
			if (instance->m_bgmMap.count(soundId) > 0) {
				SoundSource* ss = instance->m_bgmMap[soundId];
				if (ss) {
					ss->SetVolume(volume);
				}
			}
		}


		void SoundManager::FadeInAllBGM(float fadeTime)
		{
			if (!GetIsAvailable()) {
				return;
			}

			SoundManager* instance = GetInstance();

			if (fadeTime <= 0.0f) {
				return;
			}

			for (auto& pair : instance->m_bgmMap)
			{
				SoundSource* ss = pair.second;
				if (ss == nullptr) {
					continue;
				}

				/** フェードインリストへ移動 */
				float targetVol = instance->m_soundDefs[pair.first].volume;
				float currentVol = ss->GetVolume();
				float speed = (targetVol - currentVol) / fadeTime;

				instance->m_fadeInList.push_back({ ss, currentVol, targetVol, speed });
			}
		}




		/********************************/


		SoundManagerObject::SoundManagerObject()
		{
			SoundManager::CreateInstance();
		}


		SoundManagerObject::~SoundManagerObject()
		{
			SoundManager::Delete();
		}


		bool SoundManagerObject::Start()
		{
			if (SoundManager::GetIsAvailable()) {
				SoundManager::GetInstance()->Init();
			}
			return true;
		}


		void SoundManagerObject::Update()
		{
			if (SoundManager::GetIsAvailable()) {
				SoundManager::GetInstance()->Update();
			}
		}
	}
}