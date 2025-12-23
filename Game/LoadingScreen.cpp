#include "stdafx.h"
#include "LoadingScreen.h"
#include "Sound/SoundManager.h"


namespace app
{
	namespace
	{
		constexpr float FULL_HD_WIDTH = 1920.0f;								/** フルHDの幅 */
		constexpr float FULL_HD_HEIGHT = 1080.0f;								/** フルHDの高さ */

		constexpr float HALF_FULL_HD_WIDTH = FULL_HD_WIDTH / 2.0f;				/** フルHDの半分の幅 */
		constexpr float HALF_FULL_HD_HEIGHT = FULL_HD_HEIGHT / 2.0f;			/** フルHDの半分の高さ */

		constexpr float CENTER_IMAGE_RATIO = 5.0f;								/** 中央画像の倍率 */

		const float CENTER_IMAGE_WIDTH = FULL_HD_WIDTH * CENTER_IMAGE_RATIO;	/** 中央画像の幅 */
		const float CENTER_IMAGE_HEIGHT = FULL_HD_HEIGHT * CENTER_IMAGE_RATIO;	/** 中央画像の高さ */

		const Vector2 PIVOT_TOP_CENTER = { 0.5f, 1.0f };						/** 上辺の中央 */
		const Vector2 PIVOT_BOTTOM_CENTER = { 0.5f, 0.0f };						/** 下辺の中央 */
		const Vector2 PIVOT_CENTER_LEFT = { 0.0f, 0.5f };						/** 左辺の中央 */
		const Vector2 PIVOT_CENTER_RIGHT = { 1.0f, 0.5f };						/** 右辺の中央 */
		const Vector2 PIVOT_CENTER = { 0.5f, 0.5f };							/** 完全な中央 */

		constexpr float CROSE_DURATION = 1.5f;									/** クローズの時間 */
		constexpr float OPEN_DURATION = 1.5f;									/** オープンの時間 */


		/**
		 * 線形補間関数(Linear Interpolation)
		 * a:開始値, b:終了値, t:割合(0.0～1.0)
		 */
		float Lerp(float a, float b, float t)
		{
			return a + (b - a) * t;
		}
	}


	LoadingScreen* LoadingScreen::m_instance = nullptr;


	void LoadingScreen::StartLoading()
	{
		if (m_instance != nullptr) {
			m_instance->m_state = enState_Closing;

			/** ロード画面が閉まり始めるタイミングで、全BGMをフェードアウトさせる */
			sound::SoundManager::StopAllBGM(CROSE_DURATION);
		}
	}


	void LoadingScreen::FinishLoading()
	{
		if (m_instance != nullptr) {
			m_instance->m_state = enState_Opening;

			/** ロード明けのアニメーション時間に合わせてフェードインさせる */
			sound::SoundManager::FadeInAllBGM(OPEN_DURATION);
		}
	}


	void LoadingScreen::SnapToLoading()
	{
		UpdateIrisTransform(0.0f);
		sound::SoundManager::StopAllBGM(0.0f);
		m_state = enState_Loading;
	}


	void LoadingScreen::SnapToOpened()
	{
		UpdateIrisTransform(1.0f);
		m_state = enState_Opened;
	}


	void LoadingScreen::ChangeState(EnState state)
	{
		if (m_instance == nullptr) {
			return;
		}

		m_instance->m_state = state;
		m_instance->m_timer = 0.0f;

		// ローディング画面レイアウトに強制変更。
		if (state == enState_Loading) {
			m_instance->SnapToLoading();
			sound::SoundManager::StopAllBGM(0.0f);
		}
		else if (state == enState_Opened) {
			m_instance->SnapToOpened();
		}
	}


	const LoadingScreen::EnState LoadingScreen::GetState()
	{
		if (m_instance != nullptr) {
			return m_instance->m_state;
		}
		return enState_None;
	}


	LoadingScreen::LoadingScreen()
	{
	}


	LoadingScreen::~LoadingScreen()
	{
		if (m_displayImages != nullptr) {
			delete[] m_displayImages;
			m_displayImages = nullptr;
		}
	}


	bool LoadingScreen::Start()
	{
		/** レイアウト初期化 */
		InitLayout();

		return true;
	}


	void LoadingScreen::Update()
	{
		switch (m_state)
		{
		case enState_Closing:
			UpdateAnimation(1.0f, 0.0f, CROSE_DURATION, enState_Loading);
			break;

		case enState_Loading:
			break;

		case enState_Opening:
			UpdateAnimation(0.0f, 1.0f, OPEN_DURATION, enState_Opened);
			break;

		case enState_Opened:
			break;

		default:
			break;
		}
	}


	void LoadingScreen::Render(RenderContext& rc)
	{
		if (m_displayImages == nullptr) {
			return;
		}

		/** 必要なときだけ各画像を描画 */
		if (m_state == enState_Closing || m_state == enState_Opening) {
			for (int i = 0; i < enImageParts_Num; ++i) {
				m_displayImages[i].Draw(rc);
			}
			return;
		}

		/** ローディング中はローディングアイコンを描画 */
		if (m_state == enState_Loading) {
			m_loadingIcon.Draw(rc);
		}
	}


	void LoadingScreen::InitLayout()
	{
		/** スプライトレンダー配列を生成 */
		m_displayImages = new SpriteRender[enImageParts_Num];


		/** 各スプライトレンダーを初期化・配置 */
		m_displayImages[enImageParts_Center].Init("Assets/Sprite/LoadingImage_Center.dds", CENTER_IMAGE_WIDTH, CENTER_IMAGE_HEIGHT);

		m_displayImages[enImageParts_Top].Init("Assets/Sprite/LoadingImage_Around.dds", FULL_HD_WIDTH, HALF_FULL_HD_HEIGHT);
		m_displayImages[enImageParts_Top].SetPivot(PIVOT_BOTTOM_CENTER);
		m_displayImages[enImageParts_Top].SetPosition({ 0.0f, HALF_FULL_HD_HEIGHT * CENTER_IMAGE_RATIO, 0.0f });

		m_displayImages[enImageParts_Bottom].Init("Assets/Sprite/LoadingImage_Around.dds", FULL_HD_WIDTH, HALF_FULL_HD_HEIGHT);
		m_displayImages[enImageParts_Bottom].SetPivot(PIVOT_TOP_CENTER);
		m_displayImages[enImageParts_Bottom].SetPosition({ 0.0f, HALF_FULL_HD_HEIGHT * CENTER_IMAGE_RATIO * -1.0f, 0.0f });

		m_displayImages[enImageParts_Left].Init("Assets/Sprite/LoadingImage_Around.dds", HALF_FULL_HD_WIDTH, FULL_HD_HEIGHT);
		m_displayImages[enImageParts_Left].SetPivot(PIVOT_CENTER_RIGHT);
		m_displayImages[enImageParts_Left].SetPosition({ HALF_FULL_HD_WIDTH * CENTER_IMAGE_RATIO * -1.0f, 0.0f, 0.0f });

		m_displayImages[enImageParts_Right].Init("Assets/Sprite/LoadingImage_Around.dds", HALF_FULL_HD_WIDTH, FULL_HD_HEIGHT);
		m_displayImages[enImageParts_Right].SetPivot(PIVOT_CENTER_LEFT);
		m_displayImages[enImageParts_Right].SetPosition({ HALF_FULL_HD_WIDTH * CENTER_IMAGE_RATIO, 0.0f, 0.0f });

		m_loadingIcon.Init("Assets/Sprite/Loading.dds", FULL_HD_WIDTH, FULL_HD_HEIGHT);


		/** 画像を更新 */
		for (int i = 0; i < enImageParts_Num; ++i) {
			m_displayImages[i].Update();
		}

		/** タイマー初期化 */
		m_timer = 0.0f;
	}


	void LoadingScreen::UpdateIrisTransform(float ratio)
	{
		/** 中央画像のサイズを設定 */
		m_displayImages[enImageParts_Center].SetScale({ ratio, ratio, 1.0f });

		/** 中央画像の大きさから周囲画像の位置を計算 */
		float currentTopPos = (CENTER_IMAGE_HEIGHT * ratio) / 2.0f;
		float currentBottomPos = currentTopPos * -1.0f;
		float currentRightPos = (CENTER_IMAGE_WIDTH * ratio) / 2.0f;
		float currentLeftPos = currentRightPos * -1.0f;

		/** 周囲画像の位置を設定 */
		m_displayImages[enImageParts_Top].SetPosition({ 0.0f, currentTopPos, 0.0f });
		m_displayImages[enImageParts_Bottom].SetPosition({ 0.0f, currentBottomPos, 0.0f });
		m_displayImages[enImageParts_Right].SetPosition({ currentRightPos, 0.0f, 0.0f });
		m_displayImages[enImageParts_Left].SetPosition({ currentLeftPos, 0.0f, 0.0f });

		/** 全パーツ更新 */
		for (int i = 0; i < enImageParts_Num; ++i) {
			m_displayImages[i].Update();
		}
	}


	void LoadingScreen::UpdateAnimation(float startRatio, float endRatio, float duration, EnState nextState)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();

		/** 進行度（0.0 ～ 1.0）を計算 */
		float timer = m_timer / duration;

		/** 1.0を超えないようにクランプ */
		if (timer > 1.0f) {
			timer = 1.0f;
		}

		/** 補間率を計算 */
		float ratio = Lerp(startRatio, endRatio, timer);

		/** 計算結果を適用 */
		UpdateIrisTransform(ratio);

		/** 時間経過で次のステートへ */
		if (timer >= 1.0f) {
			m_timer = 0.0f;
			m_state = nextState;
		}
	}




	/********************************/


	LoadingScreenObject::LoadingScreenObject()
	{
		LoadingScreen::CreateInstance();
	}


	LoadingScreenObject::~LoadingScreenObject()
	{
		LoadingScreen::Delete();
	}


	bool LoadingScreenObject::Start()
	{
		return true;
	}


	void LoadingScreenObject::Update()
	{
		LoadingScreen::GetInstance()->Update();
	}


	void LoadingScreenObject::Render(RenderContext& rc)
	{
		LoadingScreen::GetInstance()->Render(rc);
	}
}