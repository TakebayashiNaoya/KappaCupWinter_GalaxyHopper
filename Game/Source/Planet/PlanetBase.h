/**
 * PlanetBase.h
 * 惑星の基底クラス
 */
#pragma once
#include "Source/Actor/Actor.h" 


class PlanetBase : public Actor
{
protected:
	/** モデル、座標、静的物理オブジェクトの初期化を行います。*/
	void InitModel(const std::string filePath);
	/** モデルの当たり判定 */
	PhysicsStaticObject physicsStaticObject;


public:
	PlanetBase();
	~PlanetBase();


protected:
	virtual void Update() override {};
	virtual void Render(RenderContext& rc) override final;
};