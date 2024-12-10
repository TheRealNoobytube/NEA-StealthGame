#include "Button.h"

Button::Button(std::string name) : Node2D(name) {
	addChild(&label);
}

void Button::ready(){
	__super::ready();
	//position = Vector2D(100, 100);

	label.setFont(getSceneTree()->getBasePath() + "..\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf");
	label.text = "Button";
	label.position.x = 10;
	label.position.y = 10;
}

void Button::update(float delta){
	__super::update(delta);
	if (isMouseButtonReleased(SDL_BUTTON_LEFT)) {
		if (isMouseInside && pressed) {
			onClick();
		}
		pressed = false;
	}

	//finds if the mouse is hovering in the bounds of the button
	Vector2D mousePos = getMousePosition();
	Vector2D renderScale = getSceneTree()->getRenderScale();

	bool xAlign = false;
	bool yAlign = false;

	//multiply by render scale because otherwise only the original bounds of the button will be checked
	if (mousePos.x >= position.x * renderScale.x && mousePos.x <= (position.x + size.x) * renderScale.x) {
		xAlign = true;
	}
	if (mousePos.y >= position.y * renderScale.y && mousePos.y <= (position.y + size.y) * renderScale.y) {
		yAlign = true;
	}


	if (isMouseInside) {
		mouseInside();

		if (!xAlign || !yAlign) {
			onMouseExit();
			isMouseInside = false;
		}


		if (isMouseButtonJustPressed(SDL_BUTTON_LEFT)) {
			pressed = true;
		}

		if (pressed) {
			currentColor = pressColor;
		}
		else {
			currentColor = hoverColor;
		}
	}
	else {
		if (xAlign && yAlign) {
			onMouseEnter();
			isMouseInside = true;
		}
		currentColor = normalColor;
	}

	drawRect(position, size, currentColor);
}



void Button::onClick() {
	std::cout << "click" << "\n";
}

void Button::onMouseEnter() {
	std::cout << "Mouse entered" << "\n";
}

void Button::mouseInside() {

}

void Button::onMouseExit() {
	std::cout << "Mouse exited" << "\n";
}

void Button::setText(std::string text) {
	std::cout << "text";
	this->label.text = text;
	std::cout << "text";
}

std::string Button::getText() {
	return this->label.text;
}