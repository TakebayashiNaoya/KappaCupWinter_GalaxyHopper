#include "stdafx.h"
#include "Title.h"
#include "LoadingScreen.h"


namespace app
{
	namespace scene
	{
		Title::Title()
		{
			//m_titlePlayer = NewGO<TitlePlayer>(0, "TitlePlayer");
			//m_titleCamera = NewGO<TitleCamera>(0, "TitleCamera");
			//m_titleStage = NewGO<TitlePlanet>(0, "TitlePlanet");
			//m_uiTitle = NewGO<UITitle>(0, "UITitle");
		}


		Title::~Title()
		{
			//SoundManager::StopBGM(enSoundList_TitleBGM, 1.0f);
			//DeleteGO(m_titlePlayer);
			//DeleteGO(m_titleCamera);
			//DeleteGO(m_titleStage);
			//DeleteGO(m_uiTitle);
			//DeleteGO(m_skyCube);
		}


		bool Title::Start()
		{
			InitSky();

			LoadingScreen::FinishLoading();

			sound::SoundManager::Play(sound::enSoundList_TitleBGM, true);
			sound::SoundManager::SetVolume(sound::enSoundList_FirstStageBGM, 0.0f);

			return true;
		}


		void Title::Update()
		{
			/** Aボタンが押されたらインゲームへ移行 */
			if (g_pad[0]->IsTrigger(enButtonA)) {
				sound::SoundManager::Play(sound::enSoundList_PushSE);
				/** ロードオープン中にボタンを押したら、ロード完了へ */
				if (LoadingScreen::GetState() == LoadingScreen::enState_Opening) {
					LoadingScreen::ChangeState(LoadingScreen::enState_Opened);
				}
				/** ロード完了時にボタンを押したら、ロード開始へ */
				else if (LoadingScreen::GetState() == LoadingScreen::enState_Opened) {
					LoadingScreen::StartLoading();
				}
			}

			/** Loading画面になったらシーン切り替えをリクエスト */
			if (LoadingScreen::GetState() == LoadingScreen::enState_Loading) {
				SceneManager::GetInstance()->ChangeScene(SceneID::FirstStage);
			}
		}


		void Title::InitSky()
		{
			/** 現在の空を破棄 */
			DeleteGO(m_skyCube);

			m_skyCube = NewGO<SkyCube>(0, "skycube");
			m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

			/** 環境光の計算のためのIBLテクスチャをセットする */
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
		}
	}
}