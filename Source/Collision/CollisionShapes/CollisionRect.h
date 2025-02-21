#pragma once
#include "CollisionShape.h"

class CollisionRect : public CollisionShape {
public:
	CollisionRect(std::string name = "CollisionRect");

	void ready() override;
	void update(float delta) override;

	CollisionData detectCollisions(CollisionBody* body) override;
	bool point_rectIsColliding(Vector2D point);
	CollisionData rect_rectIsColliding(CollisionRect* shape);


	Color testColor = Color(255, 0, 0);
	bool visible = true;

	void setSize(Vector2D size);
	Vector2D getSize();

private:
	Vector2D size = Vector2D(10, 10);


};