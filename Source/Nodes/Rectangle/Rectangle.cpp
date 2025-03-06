#include "Rectangle.h"

Rectangle::Rectangle(std::string name) : Node2D(name){

}

void Rectangle::update(float delta) {
	__super::update(delta);

	drawRect(position, size, color);
}