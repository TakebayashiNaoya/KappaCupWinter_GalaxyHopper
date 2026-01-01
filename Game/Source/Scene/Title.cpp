/**
 * Title.cpp
 * タイトルシーンの実装
 */
#include "stdafx.h"
#include "Title.h"
#include "LoadingScreen.h"
#include "SceneManager.h"
#include "Source/Actor/Character/Player/TitlePlayer.h"
#include "Source/Actor/Planet/TitlePlanet.h"
#include "Camera/TitleCamera.h"
#include "UI/UITitle.h"


namespace app
{
	namespace scene
	{
		Title::Title()
		{
		}


		Title::~Title()
		{
			sound::SoundManager::StopBGM(sound::enSoundList_TitleBGM, 1.0f);
			DeleteGO(m_titlePlayer);
			DeleteGO(m_titleCamera);
			DeleteGO(m_titlePlanet);
			DeleteGO(m_uiTitle);
			DeleteGO(m_skyCube);
		}


		bool Title::Start()
		{
			/** 各種オブジェクト生成 */
			m_titlePlayer = NewGO<actor::TitlePlayer>(0, "TitlePlayer");
			m_titlePlanet = NewGO<actor::TitlePlanet>(0, "TitlePlanet");
			m_titleCamera = NewGO<camera::TitleCamera>(0, "TitleCamera");
			m_uiTitle = NewGO<ui::UITitle>(0, "UITitle");
			InitSky();

			/** ロード画面をアイリスインさせる */
			LoadingScreen::FinishLoading();
			/** タイトルBGM再生 */
			sound::SoundManager::Play(sound::enSoundList_TitleBGM, true);

			return true;
		}


		void Title::Update()
		{
			/** Aボタンが押されたらインゲームへ移行 */
			if (g_pad[0]->IsTrigger(enButtonA)) {
				sound::SoundManager::Play(sound::enSoundList_PushSE);
				/** ロードオープン中にボタンを押したら、ロード完了へ */
				if (LoadingScreen::GetState() == LoadingScreen::EnState::Opening) {
					LoadingScreen::ChangeState(LoadingScreen::EnState::Opened);
				}
				/** ロード完了時にボタンを押したら、ロード開始へ */
				else if (LoadingScreen::GetState() == LoadingScreen::EnState::Opened) {
					LoadingScreen::StartLoading();
				}
			}

			/** Loading画面になったらシーン切り替えをリクエスト */
			if (LoadingScreen::GetState() == LoadingScreen::EnState::Loading) {
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