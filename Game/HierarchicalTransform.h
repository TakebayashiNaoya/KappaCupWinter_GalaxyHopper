#pragma once
#include "Transform.h"

class HierarchicalTransform : public Noncopyable
{
	/** public変数 */
public:
	Transform m_localTransform;
	//自身のパラメータ

	Transform m_worldTransform;
	/** 親トランスフォームを考慮したパラメータ */

	/** private変数 */
	/** 基本的に関数以外から弄る必要なし */
private:

	Matrix m_rotationMatrix;
	Matrix m_worldMatrix;

	HierarchicalTransform* m_parent;
	std::vector<HierarchicalTransform*> m_children;


	/** public関数 */
public:
	HierarchicalTransform();
	~HierarchicalTransform();

	/** 更新処理 */
	void UpdateTransform();
	/** ワールド行列更新、UpdateTransformの方で呼ばれるので呼び出す必要なし */
	void UpdateWorldMatrix();

	/** 全ての子トランスフォームとの紐づけを外す */
	void Release();

	/** 特定の子トランスフォームとの紐づけを外す */
	void RemoveChild(HierarchicalTransform* t);
	/** すべてのトランスフォームとの紐づけを外す */
	void ClearChild();
	void AddChild(HierarchicalTransform* t)
	{
		// 同じのは追加しない
		if (FindChild(t)) {
			return;
		}
		m_children.push_back(t);
	}
	bool FindChild(HierarchicalTransform* t)
	{
		for (auto* child : m_children)
		{
			if (child == t) {
				return true;
			}
		}
		return false;
	}

	/** 親トランスフォームを設定 */
	void SetParent(HierarchicalTransform* p)
	{
		if (m_parent) {
			return;
		}
		m_parent = p;
		m_parent->AddChild(this);
	}

	/** 親トランスフォームがあるか */
	bool HasParent() const
	{
		return m_parent != nullptr;
	}
	/** 親を解除 */
	void ClearParent()
	{
		m_parent = nullptr;
	}
};