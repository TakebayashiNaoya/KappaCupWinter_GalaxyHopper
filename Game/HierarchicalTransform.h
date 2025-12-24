#pragma once
#include "Transform.h"

class HierarchicalTransform : public Noncopyable
{
public:
	/** 自身のトランスフォーム */
	Transform m_localTransform;
	/** 親トランスフォームを考慮したパラメータ */
	Transform m_worldTransform;


private:
	/** 親トランスフォームを考慮したワールド行列 */
	Matrix m_worldMatrix;
	/** 親トランスフォーム */
	HierarchicalTransform* m_parent;
	/** 子トランスフォーム群 */
	std::vector<HierarchicalTransform*> m_children;


public:
	HierarchicalTransform();
	~HierarchicalTransform();


public:
	/**
	 * 親がいる場合は、親のトランスフォームと自身のトランスフォームを掛け合わせ、自身のワールドトランスフォームを更新する
	 * 親がいない場合は、自身のローカルトランスフォームをそのままワールドトランスフォームにコピーする
	 */
	void UpdateTransform();

	/** すべての子トランスフォームとの紐づけを外す */
	void Release();

	/** 特定の子トランスフォームとの紐づけを外す */
	void RemoveChild(HierarchicalTransform* t);

	/** すべての子トランスフォームとの紐づけを外す */
	void ClearChild();

	/** 引数に入れたトランスフォームを自身の子トランスフォームに追加する */
	void AddChild(HierarchicalTransform* t);

	/** 引数に入れた子トランスフォームが存在する場合はtrueを返す */
	bool FindChild(HierarchicalTransform* t);

	/** 引数に入れたトランスフォームを親にする */
	void SetParent(HierarchicalTransform* p);

	/** 親トランスフォームがある場合はtrueを返す */
	bool HasParent() const
	{
		return m_parent != nullptr;
	}
	/** 親を解除 */
	void ClearParent()
	{
		m_parent = nullptr;
	}


private:
	/** ワールド行列更新、UpdateTransformの方で呼ばれるので呼び出す必要なし */
	void UpdateWorldMatrix();
};