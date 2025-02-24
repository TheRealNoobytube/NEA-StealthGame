#include "Button.h"

Button::Button(std::string text, std::string name) : Node2D(name) {
	setText(text);
	addChild(&label);
	
	
}

void Button::ready(){
	__super::ready();

	setNormalTexture(getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonNormal.png");
	setHoverTexture(getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonHover.png");
	setPressTexture(getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonPressed.png");
	currentTexture = normalTexture;

	label.scale = Vector2D(0.5, 0.5);
	label.setFontSize(24);
}

void Button::update(float delta){
	__super::update(delta);
	if (isMouseButtonReleased(SDL_BUTTON_LEFT)) {
		if (isMouseInside && pressed) {
			if (isClickedWhenLetGo) {
				onClick();
			}
			onRelease();
		}
		pressed = false;
	}


	

	
	//finds if the mouse is hovering in the bounds of the button
	Vector2D mousePos = getMousePosition();
	Vector2D renderScale = getSceneTree()->getRenderScale();

	bool xAlign = false;
	bool yAlign = false;

	//multiply by render scale because otherwise only the original bounds of the button will be checked
	if (mousePos.x >= getGlobalPosition().x * renderScale.x && mousePos.x <= (getGlobalPosition().x + size.x) * renderScale.x) {
		xAlign = true;
	}
	if (mousePos.y >= getGlobalPosition().y * renderScale.y && mousePos.y <= (getGlobalPosition().y + size.y) * renderScale.y) {
		yAlign = true;
	}


	if (isMouseInside) {
		mouseInside();

		if (!xAlign || !yAlign) {
			onMouseExit();
			isMouseInside = false;
		}


		if (isMouseButtonJustPressed(SDL_BUTTON_LEFT)) {
			if (!pressed && !isClickedWhenLetGo) {
				onClick();
			}
			pressed = true;
		}

		if (pressed) {
			currentColor = pressColor;
			currentTexture = pressedTexture;
		}
		else {
			currentColor = hoverColor;
			currentTexture = hoverTexture;
		}
	}
	else {
		if (xAlign && yAlign) {
			onMouseEnter();
			isMouseInside = true;
		}
		if (!pressed) {
			currentColor = normalColor;
			currentTexture = normalTexture;
		}
	}
	label.position.x = (size.x / 2) - (label.getTextSize().x / 2) * label.scale.x; //aligns text to the center of the button
	label.position.y = (size.y / 2) - (label.getTextSize().y / 2) * label.scale.y;

	if (useTextures) {
		currentTexture.draw(getGlobalPosition(), scale, size);
	}
	else {
		drawRect(getGlobalPosition(), size, currentColor);
	}
}



void Button::onClick() {
	this->on_click.emit();
}

void  Button::onRelease() {
	this->on_release.emit();
}

void Button::onMouseEnter() {
	on_mouse_enter.emit();
}

void Button::mouseInside() {

}

void Button::onMouseExit() {
	on_mouse_exit.emit();
}

Vector2D Button::getSize() {
	return this->size;
}

void Button::setSize(Vector2D size) {
	this->size.x = std::clamp(size.x, 1.0f, INFINITY);
	this->size.y = std::clamp(size.y, 1.0f, INFINITY);
}

void Button::setText(std::string text) {
	this->label.text = text;

}

std::string Button::getText() {
	return this->label.text;
}

void Button::setAntiAliasing(bool antiAliasing) {
	this->label.antiAliasing = true;
}
bool Button::antiAliasingEnabled() {
	return this->label.antiAliasing;
}

bool Button::isPressed() {
	return this->pressed;
}

void Button::setNormalTexture(std::string filePath) {
	normalTexture.setTexture(filePath);
}
void Button::setHoverTexture(std::string filePath) {
	hoverTexture.setTexture(filePath);
}
void Button::setPressTexture(std::string filePath) {
	pressedTexture.setTexture(filePath);
}