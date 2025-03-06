#pragma once
#include "Source/Nodes/Node2D/Node2D.h"

class Rectangle : public Node2D {

public:
	Rectangle(std::string name = "Rectangle");

	Vector2D size = Vector2D(10, 10);
	Color color = Color(255, 255, 255);

	void update(float delta) override;
};