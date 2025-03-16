#include "ProgressBar.h"

ProgressBar::ProgressBar(std::string name) : Node2D(name) {

}


void ProgressBar::ready() {
	__super::ready();

	if (background.getTexture() == nullptr) {
		background.setTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderBarBackground.png");
	}
	if (progress.getTexture() == nullptr) {
		progress.setTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderBar.png");
	}
	
	
}

void ProgressBar::update(float delta) {
	__super::update(delta);

	if (visible) {
		float sliderSize = ((value - min) / (max - min)) * size.x; //interpolation done to get the slider's physical size from the current value

		//background of the slider bar, will always be the same size
		background.draw(position, scale);
		//progress bar part of the slider bar, changes based on the current value
		progress.draw(position, scale, Vector2D(sliderSize, 0), Vector2D(0, 0), Vector2D(sliderSize, size.y));
		//draw order is important: background is always drawn before the progress bar
	}

}


void ProgressBar::setValue(float value) {
	this->value = std::clamp(value, min, max); // makes it so value is within the range set by min and max
}

float ProgressBar::getValue() {
	return value;
}

void ProgressBar::setMin(float min) {
	this->min = min;
}

void ProgressBar::setMax(float max) {
	this->max = max;
}

void ProgressBar::setSize(Vector2D size) {
	this->size.x = std::clamp(size.x, 1.0f, INFINITY);
	this->size.y = std::clamp(size.y, 1.0f, INFINITY);
}

Vector2D ProgressBar::getSize() {
	return this->size;
}