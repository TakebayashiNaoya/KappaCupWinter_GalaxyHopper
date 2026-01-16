/**
 * ParameterManager.cpp
 * パラメータ管理クラスの実装
 */
#include "stdafx.h"
#include "ParameterManager.h"


namespace app
{
	namespace core
	{
		/** 静的メンバ変数の実体を定義 */
		ParameterManager* ParameterManager::m_instance = nullptr;


		ParameterManager::ParameterManager()
		{
			m_parameterMap.clear();
		}


		ParameterManager::~ParameterManager()
		{
			/** メモリのお片付け */
			for (auto& pair : m_parameterMap) {
				auto& list = pair.second;
				for (auto* param : list) {
					delete param;
				}
				list.clear();
			}
			m_parameterMap.clear();
		}
	}
}