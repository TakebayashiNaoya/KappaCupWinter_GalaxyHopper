/**
 * ParameterManager.h
 * パラメータ管理クラスの定義
 */
#pragma once
#include "../json/json.hpp"
#include "../Util/CRC32.h" 
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

 /**
  * パラメータ定義用マクロ（参考コードと同じもの）
  * これを使うと、クラス名から自動的にIDを作ってくれます
  */
#define appParameter(name)\
public:\
 static constexpr uint32_t ID() { return Hash32(#name); }

  /** 全てのパラメータの親玉 */
struct IMasterParameter {};

/** プレイヤーのステータス */
struct MasterPlayerStatusParameter : public IMasterParameter
{
	appParameter(MasterPlayerStatusParameter);
	//
	int maxHp;
	float walkSpeed;
	float hurtRadius;
	float modelScale;
	float colliderOffset;
	float dashSpeed;
	float jumpPower;
	float knockbackPower;
	float knockbackDuration;
};

struct MasterBasicEnemyStatusParameter : public IMasterParameter
{
	appParameter(MasterBasicEnemyStatusParameter);
	//
	int maxHp;
	float walkSpeed;
	float hurtRadius;
	float modelScale;
	float colliderOffset;
	float hitRadius;
	float searchRange;
};

struct MasterDeformEnemyStatusParameter : public IMasterParameter
{
	appParameter(MasterDeformEnemyStatusParameter);
	//
	int maxHp;
	float walkSpeed;
	float hurtRadius;
	float modelScale;
	float colliderOffset;
	float hitRadius;
	float searchRange;
	float slideSpeed;
};

struct MasterBossEnemyStatusParameter : public IMasterParameter
{
	appParameter(MasterBossEnemyStatusParameter);
	//
	int maxHp;
	float walkSpeed;
	float hurtRadius;
	float modelScale;
	float colliderOffset;
	float hitRadius;
	float searchRange;
	float dashSpeed;
};


/** defineの使用終了 */
#undef appParameter


/** パラメータ管理クラス */
class ParameterManager
{
private:
	/** データを保存する場所：{ID: [データリスト] } */
	std::map<uint32_t, std::vector<IMasterParameter*>> m_parameterMap;

private:
	/** コンストラクタ（外部からの生成禁止） */
	ParameterManager();
	/** デストラクタ（外部からの破棄禁止） */
	~ParameterManager();

public:
	/**
	 * JSONを読み込む関数
	 * テンプレート関数なのでヘッダーに実装を書きます
	 */
	template <typename T>
	void LoadParameter(const std::string& filePath, std::function<void(const nlohmann::json&, T&)> callback)
	{
		/** ファイル読み込み */
		std::ifstream file(filePath);
		if (!file.is_open()) return;

		nlohmann::json jsonObject;
		file >> jsonObject;

		/** データを格納するリストを確保 */
		auto& list = m_parameterMap[T::ID()];

		/** JSON配列を回してデータを生成 */
		if (jsonObject.is_array()) {
			for (const auto& j : jsonObject) {
				T* param = new T();
				callback(j, *param);
				list.push_back(param);
			}
		}
		else {
			/** 配列じゃない場合（単体データの場合）もケアしておく */
			T* param = new T();
			callback(jsonObject, *param);
			list.push_back(param);
		}
	}

	/**
	 * パラメーター解放
	 */
	template <typename T>
	void UnloadParameter()
	{
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			auto& parameters = it->second;
			for (auto* p : parameters) {
				delete p;
			}
			m_parameterMap.erase(it);
		}
	}

	/**
	 * データを取得する関数
	 */
	template <typename T>
	const T* GetParameter(uint8_t index = 0) const
	{
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			if (index < it->second.size()) {
				return static_cast<T*>(it->second[index]);
			}
		}
		return nullptr;
	}

	/**
	 * シングルトン関連（参考コードの作法に準拠）
	 */
private:
	static ParameterManager* m_instance;

public:
	/** インスタンス生成 */
	static void CreateInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new ParameterManager();
		}
	}
	/** インスタンス取得 */
	static ParameterManager* GetInstance()
	{
		return m_instance;
	}
	/** インスタンス破棄 */
	static void DeleteInstance()
	{
		if (m_instance != nullptr) {
			delete m_instance;
			m_instance = nullptr;
		}
	}
	/** 有効確認 */
	static bool IsAvailable()
	{
		return m_instance != nullptr;
	}
	/** 簡略アクセス用 */
	static ParameterManager& Get()
	{
		return *m_instance;
	}
};