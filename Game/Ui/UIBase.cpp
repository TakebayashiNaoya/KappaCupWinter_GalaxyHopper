/**
 * UIBase.cpp
 * UIの基本的な処理をするクラス群
 */
#include "stdafx.h"
#include "UIBase.h"
#include "SpriteAnimation.h"


namespace app
{
	namespace ui
	{
		UIBase::UIBase()
		{
			m_spriteAnimationList.clear();
		}


		UIBase::~UIBase()
		{
			for (auto* spriteAnimation : m_spriteAnimationList) {
				delete spriteAnimation;
				spriteAnimation = nullptr;
			}
			m_spriteAnimationList.clear();
		}


		void UIBase::AddSpriteAnimation(SpriteAnimationBase* animation)
		{
			m_spriteAnimationList.push_back(animation);
		}


		void UIBase::PlaySpriteAnimations()
		{
			for (auto* animation : m_spriteAnimationList) {
				animation->Play();
			}
		}


		void UIBase::StopSpriteAnimations()
		{
			for (auto* animation : m_spriteAnimationList) {
				animation->Stop();
			}
		}




		/************************************/


		UIImage::UIImage()
		{
		}


		UIImage::~UIImage()
		{
		}

		bool UIImage::Start()
		{
			return true;
		}


		void UIImage::Update()
		{
		}


		void UIImage::Render(RenderContext& rc)
		{
			m_spriteRender.Draw(rc);
		}


		void UIImage::Initialize(const char* assetPath, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
		{
			m_transform.m_localTransform.m_position = position;
			m_transform.m_localTransform.m_scale = scale;
			m_transform.m_localTransform.m_rotation = rotation;

			m_spriteRender.Init(assetPath, width, height);
			m_spriteRender.SetPosition(position);
			m_spriteRender.SetScale(scale);
			m_spriteRender.SetRotation(rotation);
			m_spriteRender.Update();
		}




		/************************************/


		UIText::UIText()
		{
		}


		UIText::~UIText()
		{
		}


		bool UIText::Start()
		{
			return true;
		}


		void UIText::Update()
		{
			///** トランスフォーム更新 */
			//m_transform.UpdateTransform();

			///** フォントレンダーにワールド座標などを反映 */
			//m_fontRender.SetPosition(m_transform.m_worldTransform.m_position);
			//m_fontRender.SetScale(m_transform.m_worldTransform.m_scale.x); // FontRenderのSetScaleはfloatを受け取る仕様のため
			//m_fontRender.SetRotation(m_transform.m_worldTransform.m_rotation.y); // 必要に応じて軸を調整（FontRenderの仕様に合わせる）

			///** スプライトアニメーション更新 */
			//for (auto* animation : m_spriteAnimationList) {
			//	animation->Update();
			//}
		}


		void UIText::Render(RenderContext& rc)
		{
			m_fontRender.Draw(rc);
		}


		void UIText::Initialize(const wchar_t* text, const Vector3& position, const float scale, const Vector4& color, const Quaternion& rotation)
		{
			m_transform.m_localTransform.m_position = position;
			/** UIのスケール管理を統一するためVector3に入れるが、FontRenderはfloatスケールを使う */
			m_transform.m_localTransform.m_scale = Vector3(scale, scale, scale);
			m_transform.m_localTransform.m_rotation = rotation;

			m_transform.UpdateTransform();

			m_fontRender.SetText(text);
			m_fontRender.SetColor(color);
			m_fontRender.SetPosition(position);
			m_fontRender.SetScale(scale);
		}


		void UIText::SetText(const wchar_t* format, ...)
		{
			va_list args;
			__crt_va_start(args, format);

			wchar_t wcsbuf[256];
			vswprintf_s(wcsbuf, 256, format, args);

			__crt_va_end(args);

			m_fontRender.SetText(wcsbuf);
		}




		/********************************/


		UIDigit::UIDigit()
		{
		}


		UIDigit::~UIDigit()
		{
		}


		bool UIDigit::Start()
		{
			return true;
		}


		void UIDigit::Update()
		{
			/** 数字が変わっていたら更新 */
			if (m_number != m_requestNumber) {
				m_number = m_requestNumber;
				for (int i = 0; i < m_digit; ++i) {
					UpdateNumber(i + 1, m_number);
				}
			}

			/** トランスフォーム更新とスプライトレンダー更新 */
			m_transform.UpdateTransform();
			for (int i = 0; i < m_renderList.size(); ++i) {
				auto* spriteRender = m_renderList[i];
				UpdatePosition(i);
				spriteRender->SetScale(m_transform.m_worldTransform.m_scale);
				spriteRender->SetRotation(m_transform.m_worldTransform.m_rotation);
				spriteRender->Update();
			}

			/** スプライトアニメーション更新 */
			for (auto* animation : m_spriteAnimationList) {
				animation->Update();
			}
		}


		void UIDigit::Render(RenderContext& rc)
		{
			/** スプライトレンダー描画 */
			for (SpriteRender* spriteRender : m_renderList) {
				spriteRender->Draw(rc);
			}
		}


		void UIDigit::Initialize(const char* assetPath, const int digit, const int number, const float widht, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
		{
			m_assetPath = assetPath;
			m_digit = digit;
			m_number = number;
			m_width = widht;
			m_height = height;

			m_transform.m_localTransform.m_position = position;
			m_transform.m_localTransform.m_scale = scale;
			m_transform.m_localTransform.m_rotation = rotation;

			/** 先に必要な数のスプライトを生成 */
			m_renderList.clear();
			for (int i = 0; i < digit; i++) {
				// 箱（スプライト）を作ってリストに入れる
				SpriteRender* render = new SpriteRender();
				m_renderList.push_back(render);
			}

			/** 各桁の数字を更新 */
			for (int i = 0; i < digit; i++) {
				UpdateNumber(i + 1, m_number);	/** 桁なので＋１する */
			}
		}


		void UIDigit::UpdateNumber(const int targetDigit, const int number)
		{
			/** targetDigitが1以上でなければ警告する */
			K2_ASSERT(targetDigit >= 1, "桁指定が間違えています。\n");

			const int targetRenderIndex = targetDigit - 1;

			/** リストの範囲外なら何もしない */
			if (targetRenderIndex >= m_renderList.size()) {
				return;
			}

			// すでにリストにあるものを取り出すだけにする
			SpriteRender* nextRender = m_renderList[targetRenderIndex];

			/** 対象の桁の数字 */
			const int targetDigitNumber = GetDigit(targetDigit);

			/** 後で書き換えるため、パスを0.ddsにしておく */
			std::string assetNname = m_assetPath + "/0.dds";

			/**
			 * パスの後ろから5番目の文字を数字の部分を桁の数字で変える
			 * '0'は文字コードで48なので、'0' + 数字で文字に変換できる
			 */
			assetNname[assetNname.size() - 5] = '0' + targetDigitNumber;

			/** スプライトレンダーを初期化 */
			nextRender->Init(assetNname.c_str(), m_width, m_height);
		}


		void UIDigit::UpdatePosition(const int index)
		{
			SpriteRender* render = m_renderList[index];
			Vector3 position = m_transform.m_worldTransform.m_position;
			position.x -= m_width * index;
			render->SetPosition(position);
		}


		int UIDigit::GetDigit(int digit)
		{
			/** NOTE: targetDigitは1以上の値になっている */
			K2_ASSERT(digit >= 1, "桁指定が間違えています。\n");

			/**
			 * 指定した桁の数字を取得
			 * NOTE: 123の2桁目を取得したい場合
			 *		 digitは2なので、1を引いて1にする
			 *		 10の1乗(digit乗)でm_numberを割ると12になる
			 *		 12を10で割った余りを取ると2になるのでこれを返す
			 */
			digit -= 1;
			int divisor = static_cast<int>(pow(10, digit));
			return (m_number / divisor) % 10;
		}




		/************************************/


		UICanvas::UICanvas()
		{
			m_uiList.clear();
		}


		UICanvas::~UICanvas()
		{
			for (auto* ui : m_uiList) {
				/** トランスフォームの親子関係を解除 */
				m_transform.RemoveChild(&ui->m_transform);
				/** キャンバス上にあるUIを削除 */
				delete ui;
				ui = nullptr;
			}
			m_uiList.clear();
		}


		bool UICanvas::Start()
		{
			return true;
		}


		void UICanvas::Update()
		{
			m_transform.UpdateTransform();

			for (auto* ui : m_uiList) {
				ui->Update();
			}
		}


		void UICanvas::Render(RenderContext& rc)
		{
			for (auto* ui : m_uiList) {
				ui->Render(rc);
			}
		}
	}
}