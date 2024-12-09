#include "Button.h"

void Button::ready(){
	position = Vector2D(100, 100);
}

void Button::update(float delta){
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