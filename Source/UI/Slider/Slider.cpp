#include "Slider.h"

Slider::Slider(std::string name) : Node2D(name){
	addChild(&sliderButton);
	sliderButton.isClickedWhenLetGo = false;
	sliderButton.setSize(Vector2D(10, 10));
	sliderButton.position.x -= sliderButton.getSize().x / 2;
}


void Slider::ready() {
	__super::ready();
	sliderBackground = Texture();
	sliderProgress = Texture();

	sliderBackground.setTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderBarBackground.png");
	sliderProgress.setTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderBar.png");

	//custom button textures for the slider
	sliderButton.setNormalTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderButtonNormal.png");
	sliderButton.setHoverTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderButtonHover.png");
	sliderButton.setPressTexture(getSceneTree()->getBasePath() + "../Assets/Slider/SliderButtonPressed.png");

	float sliderSize = ((value - min) / (max - min)) * size.x; //interpolation done to get the slider progress size from the current value
	sliderButton.position.x = sliderSize - (sliderButton.getSize().x / 2);
}

void Slider::update(float delta) {
	__super::update(delta);

	//even when the mouse is outside of the Button, as long as the left mouse button is still down, the Button is still considered pressed
	//makes adjusting the slider more comfortable and less finicky as otherwise youll constantly fight with the slider
	//to get the value you want unless you move the slider very slowly to make sure the mouse never leaves the Button

	if (sliderButton.isPressed()) {
		//divide by the render scale to adjust for the size of the viewport
		float mousePosX = getMousePosition().x / getSceneTree()->getRenderScale().x;

		float halfSliderButtonWidth = sliderButton.getSize().x / 2; //minus this from any position calculations, 
																    //keeps the mouse position centered onto the Button
		float lowerBound = -halfSliderButtonWidth;
		float upperBound = size.x - halfSliderButtonWidth;

		//minus by global position of entire slider to get the position of the mouse local to the slider button
		//also minus by half of the slider button's size, helps keep mouse centered on the button
		sliderButton.position.x = mousePosX - getGlobalPosition().x - halfSliderButtonWidth;

		//linear interpolation to find value from slider button position
		value = min + ((sliderButton.position.x - lowerBound) * ((max - min) / (upperBound - lowerBound)));

		//make sure the value and position of the Button doesnt go out of bounds of the Slider
		sliderButton.position.x = std::clamp(sliderButton.position.x, lowerBound, upperBound);
		value = std::clamp(value, min, max);
	}

	float sliderSize = ((value - min) / (max - min)) * size.x; //interpolation done to get the slider's physical size from the current value

	//background of the slider bar, will always be the same size
	sliderBackground.draw(position, scale);
	//progress bar part of the slider bar, changes based on the current value
	sliderProgress.draw(position, scale, Vector2D(sliderSize, 0), Vector2D(0, 0), Vector2D(sliderSize, size.y));
	//draw order is important: background is always drawn before the progress bar
}


void Slider::setValue(float value) {
	this->value = std::clamp(value, min, max); // makes it so value is within the range set by min and max
}

float Slider::getValue() {
	return value;
}

void Slider::setMin(float min) {
	this->min = min;
}

void Slider::setMax(float max) {
	this->max = max;
}

void Slider::setSize(Vector2D size) {
	this->size.x = std::clamp(size.x, 1.0f, INFINITY);
	this->size.y = std::clamp(size.y, 1.0f, INFINITY);
}

Vector2D Slider::getSize() {
	return this->size;
}