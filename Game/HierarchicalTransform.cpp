#include "stdafx.h"
#include "HierarchicalTransform.h"

HierarchicalTransform::HierarchicalTransform()
	: m_worldMatrix(Matrix::Identity)
	, m_parent(nullptr)
{
	m_children.clear();

	/** m_localTransformの初期化 */
	m_localTransform.m_position = Vector3::Zero;
	m_localTransform.m_rotation = Quaternion::Identity;
	m_localTransform.m_scale = Vector3::One;

	/** m_worldTransformの初期化 */
	m_worldTransform.m_position = Vector3::Zero;
	m_worldTransform.m_rotation = Quaternion::Identity;
	m_worldTransform.m_scale = Vector3::One;
}

HierarchicalTransform::~HierarchicalTransform()
{
	if (m_parent) {
		m_parent->RemoveChild(this);
	}
	Release();
}

void HierarchicalTransform::UpdateTransform()
{
	if (m_parent)
	{
		/** 自分のローカル座標（親からどれだけズレているか）を行列化 */
		Matrix localPos;
		localPos.MakeTranslation(m_localTransform.m_position);

		/** 親のワールド行列と掛け合わせてワールド座標を算出 */
		Matrix pos;
		pos.Multiply(localPos, m_parent->m_worldMatrix);

		/** 平行移動成分を抽出し、自分のワールド座標に入れる */
		m_worldTransform.m_position.x = pos.m[3][0];
		m_worldTransform.m_position.y = pos.m[3][1];
		m_worldTransform.m_position.z = pos.m[3][2];

		/** 自分のスケールと親のスケールを掛け合わせて、自分のワールドスケールを算出 */
		m_worldTransform.m_scale.x = m_localTransform.m_scale.x * m_parent->m_worldTransform.m_scale.x;
		m_worldTransform.m_scale.y = m_localTransform.m_scale.y * m_parent->m_worldTransform.m_scale.y;
		m_worldTransform.m_scale.z = m_localTransform.m_scale.z * m_parent->m_worldTransform.m_scale.z;

		/** 自分の回転と親の回転を掛け合わせて、自分のワールド回転を算出 */
		m_worldTransform.m_rotation = m_parent->m_worldTransform.m_rotation * m_localTransform.m_rotation;
	}
	else
	{
		/** 親がいない場合は、ローカルの値をそのままコピー */
		m_worldTransform.m_position = m_localTransform.m_position;
		m_worldTransform.m_scale = m_localTransform.m_scale;
		m_worldTransform.m_rotation = m_localTransform.m_rotation;
	}

	/** ここまで計算したワールド座標・ワールド拡大縮小・ワールド回転を1つのワールド行列にまとめる */
	UpdateWorldMatrix();
}

void HierarchicalTransform::UpdateWorldMatrix()
{
	Matrix scal, rot, pos, world;
	/** 拡大縮小行列を作成 */
	scal.MakeScaling(m_worldTransform.m_scale);
	/** 回転行列を作成 */
	rot.MakeRotationFromQuaternion(m_worldTransform.m_rotation);
	/** 平行移動行列を作成 */
	pos.MakeTranslation(m_worldTransform.m_position);
	/** 拡大縮小→回転→平行移動の順で行列を掛け合わせる */
	world.Multiply(scal, rot);
	m_worldMatrix.Multiply(world, pos);

	/** 自分の子も更新 */
	for (HierarchicalTransform* child : m_children) {
		child->UpdateTransform();
	}
}


void HierarchicalTransform::Release()
{
	//イテレータ生成
	std::vector<HierarchicalTransform*>::iterator it = m_children.begin();
	//vectorの終わりまで回す
	while (it != m_children.end())
	{
		//子トランスフォームからの紐づけを外す
		(*it)->m_parent = nullptr;
		//子トランスフォームへの紐づけを外す
		m_children.erase(it);
		// 対象がいないなら抜ける
		if (m_children.size() == 0) {
			break;
		}
		//イテレータを進める
		++it;

	}
	//念のため？vectorの要素を全削除
	m_children.clear();
}

void HierarchicalTransform::RemoveChild(HierarchicalTransform* t)
{
	//イテレータ生成
	std::vector<HierarchicalTransform*>::iterator it = m_children.begin();
	//vectorを回す
	while (it != m_children.end())
	{
		//イテレータから子トランスフォームのポインタを受け取る
		HierarchicalTransform* child = (*it);
		//受け取った子トランスフォームがしてされた物なら
		if (child == t)
		{
			//紐づけを外す
			child->m_parent = nullptr;
			m_children.erase(it);
			//処理を終了
			return;
		}

		//イテレータを進める
		++it;
	}
}


void HierarchicalTransform::ClearChild()
{
	m_children.clear();
}

void HierarchicalTransform::AddChild(HierarchicalTransform* t)
{
	/** すでに登録されている場合は追加しない */
	if (FindChild(t)) {
		return;
	}
	m_children.push_back(t);
}

bool HierarchicalTransform::FindChild(HierarchicalTransform* t)
{
	for (auto* child : m_children) {
		if (child == t) {
			return true;
		}
	}
	return false;
}

void HierarchicalTransform::SetParent(HierarchicalTransform* p)
{
	if (m_parent) {
		return;
	}
	m_parent = p;
	m_parent->AddChild(this);
}
