/**
 * PlanetBase.h
 * 惑星の基底クラス
 */
#pragma once
#include "Source/Actor/Actor.h" 


class PlanetBase : public Actor
{
protected:
	/** モデルの初期化を行います。 */
	void InitModel(const std::string filePath);
	/** モデルの当たり判定。 */
	PhysicsStaticObject physicsStaticObject;


protected:
	/** Updateは派生先でoverrideして使用。 */
	virtual void Update() override {};


public:
	PlanetBase() {};
	virtual ~PlanetBase() {};


private:
	/** Startは派生先で使用しないためfinal。 */
	virtual bool Start() override final { return true; };
	/** Renderは共通処理のため派生先でoverrideしない。 */
	virtual void Render(RenderContext& rc) override final;
};