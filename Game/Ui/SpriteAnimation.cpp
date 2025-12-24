/**
 * SpriteAnimation.cpp
 * SpriteRenderをアニメーションさせる機能群
 */
#include "stdafx.h"
#include "SpriteAnimation.h"


namespace app
{
	namespace ui
	{
		template <typename T>
		void SpriteAnimationBase::UpdateCore(std::vector<T> targetList, const std::function<void(const float, const T&, const T&)> func)
		{
			const float deltaTime = g_gameTime->GetFrameDeltaTime();
			m_elapsedTime += deltaTime;

			/** 現在のターゲットインデックスに基づいて、初期値と目標値を取得 */
			T valueStart = targetList[m_targetIndex];
			T valueEnd = targetList[m_targetIndex + 1];

			/** 何秒かけて変化させるかの取得 */
			float targetTime = m_targetTimeList[m_targetIndex];

			/** 現時点で何％変化しているかを算出 */
			const float computePercent = m_elapsedTime / targetTime;

			/** 初期値、目標値、変化率を渡してfuncで値を計算し、計算結果をレンダーに反映する */
			func(computePercent, valueStart, valueEnd);
			m_render->Update();

			/** 今の時間が指定した時間を超えたら、次のアニメーションに移行する */
			if (m_elapsedTime >= targetTime) {
				m_targetIndex++;
				m_elapsedTime = 0.0f;

				/** 最後のアニメーションまで到達したら完了フラグを立てる */
				if (m_targetIndex == m_targetTimeList.size()) {
					m_isCompleted = true;
					m_targetIndex = 0;
				}
			}

		}


		bool SpriteAnimationBase::CanUpdate()
		{
			// 繰り返し実行するか
			if (!m_isLoop && m_isCompleted)
			{
				return false;
			}
			// 再生するかがtrueじゃなければ実行しない
			if (!m_isPlay)
			{
				return false;
			}
			return true;
		}


		void ScaleSpriteAnimation::Update()
		{
			if (!CanUpdate()) {
				return;
			}
			UpdateCore<Vector2>(m_targetScaleList, [&](const float percent, const Vector2& startValue, const Vector2& endValue)
				{
					Vector2 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
					m_render->SetScale(Vector3(value.x, value.y, 0.0f));
				});
		}




		/*********************************************/


		void ColorSpriteAnimation::Update()
		{
			if (!CanUpdate()) {
				return;
			}
			UpdateCore<Vector4>(m_targetColorList, [&](const float percent, const Vector4& startValue, const Vector4& endValue)
				{
					Vector4 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
					m_render->SetMulColor(value);
				});
		}




		/***********************************************/


		void TranslateSpriteAnimation::Update()
		{
			if (!CanUpdate()) {
				return;
			}
			UpdateCore<Vector3>(m_targetTranslateList, [&](const float percent, const Vector3& startValue, const Vector3& endValue)
				{
					Vector3 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
					m_render->SetPosition(value);
				});
		}




		/***********************************************/


		void TranslateOffsetSpriteAnimation::Update()
		{
			if (!CanUpdate()) {
				return;
			}
			UpdateCore<Vector3>(m_targetOffsetList, [&](const float percent, const Vector3& startValue, const Vector3& endValue)
				{
					Vector3 value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
					Vector3 computePosition = m_ownerTransform->m_position + value; // オフセット位置を足す
					m_render->SetPosition(computePosition);
				});
		}




		/*************************************************/


		void RotationSpriteAnimation::Update()
		{
			if (!CanUpdate()) {
				return;
			}
			UpdateCore<Quaternion>(m_targetRotationList, [&](const float percent, const Quaternion& startValue, const Quaternion& endValue)
				{
					Quaternion value = nsK2EngineLow::Math::Lerp(percent, startValue, endValue);
					m_render->SetRotation(value);
				});
		}
	}
}