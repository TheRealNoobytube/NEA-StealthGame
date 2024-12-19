#include "Button.h"

Button::Button(std::string text, std::string name) : Node2D(name) {
	setText(text);
	addChild(&label);
	
}

void Button::ready(){
	__super::ready();

	std::cout << "Button";

	if (currentTexture == nullptr) {
		normalTexture = new Texture(getSceneTree()->getRenderer(), getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonNormal.png");
		hoverTexture = new Texture(getSceneTree()->getRenderer(), getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonHover.png");
		pressedTexture = new Texture(getSceneTree()->getRenderer(), getSceneTree()->getBasePath() + "..\\Assets\\Button\\ButtonPressed.png");
		currentTexture = normalTexture;
	}


	//label.setFont(getSceneTree()->getBasePath() + "..\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf");



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
		currentColor = normalColor;
		currentTexture = normalTexture;
	}
	label.position.x = (size.x / 2) - (label.getTextSize().x / 2); //aligns text to the center of the button
	label.position.y = (size.y / 2) - (label.getTextSize().y / 2);

	if (useTextures) {
		currentTexture->draw(position.x, position.y, scale.x, scale.y);
	}
	else {
		drawRect(position, size, currentColor);
	}
}



void Button::onClick() {
	std::cout << "click" << "\n";
	this->on_click.emit();
}

void Button::onMouseEnter() {
	std::cout << "Mouse entered" << "\n";
}

void Button::mouseInside() {

}

void Button::onMouseExit() {
	std::cout << "Mouse exited" << "\n";
}

Vector2D Button::getSize() {
	return this->size;
}

void Button::setSize(Vector2D size) {
	if (size.x <= 0 || size.y <= 0) {
		this->size = Vector2D(1, 1);
	}
	else {
		this->size = size;
	}
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

