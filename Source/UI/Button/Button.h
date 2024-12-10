#pragma once

#include "SDL_ttf.h"
#include "../../Nodes/Node2D/Node2D.h"
#include "../../Application/Texture.h"
#include "../Label/Label.h"

class Button : public Node2D {
private:
	Label label;
	Vector2D size = Vector2D(100, 40);
	Color normalColor = Color(53, 68, 127);
	Color pressColor = Color(33, 48, 107);
	Color hoverColor = Color(73, 88, 147);

	Color currentColor = normalColor;

	bool isMouseInside = false;
	bool pressed = false;

public:
	Button(std::string name = "Button");

	void ready() override;
	void update(float delta) override;

	void onClick();
	void onMouseEnter();
	void mouseInside();
	void onMouseExit();

	void setText(std::string text);
	std::string getText();
};