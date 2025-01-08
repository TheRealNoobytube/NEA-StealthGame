#pragma once
#include "CollisionShape.h"


class CollisionRect : public CollisionShape {
public:
	CollisionRect(std::string name = "CollisionRect");

	void ready() override;
	void update(float delta) override;

	CollisionBody* detectCollisions(CollisionBody* body);
	bool rect_rectIsColliding(CollisionRect* shape);
	bool visible = true;

	void setSize(Vector2D size);
	Vector2D getSize();

private:
	Vector2D size = Vector2D(10, 10);


};