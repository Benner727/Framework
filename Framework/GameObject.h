#pragma once

#include "MathHelper.h"

class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };

private:
	Vector2 mPrevPos;
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	bool mActive;

	GameObject* mParent;

public:
	GameObject(const Vector2& pos = VEC2_ZERO);
	virtual ~GameObject();

	Vector2 PrevPos();
	void Pos(const Vector2& pos);
	const Vector2& Pos(SPACE space = world);

	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Scale(const Vector2& scale);
	const Vector2& Scale(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(GameObject* parent);
	GameObject* Parent();

	void Translate(const Vector2& vec, SPACE space = world);
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();
};