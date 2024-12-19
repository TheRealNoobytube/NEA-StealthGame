#pragma once

#include "SDL_ttf.h"
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Application/Texture.h"
#include "Source/UI/Label/Label.h"
#include <functional>

class Button : public Node2D {
private:
	Label label;
	Vector2D size = Vector2D(60, 20);
	Color normalColor = Color(53, 68, 127);
	Color pressColor = Color(33, 48, 107);
	Color hoverColor = Color(73, 88, 147);
	Color currentColor = normalColor;

	Texture* normalTexture;
	Texture* hoverTexture;
	Texture* pressedTexture;
	Texture* currentTexture = nullptr;

	bool useTextures = true;
	bool isMouseInside = false;
	bool pressed = false;


public:
	Button(std::string text = " ", std::string name = "Button");

	Signal<> on_click;

	void ready() override;
	void update(float delta) override;

	void onClick();
	void onMouseEnter();
	void mouseInside();
	void onMouseExit();

	Vector2D getSize();
	void setSize(Vector2D size);

	void setText(std::string text);
	std::string getText();
	void setAntiAliasing(bool antiAliasing);
	bool antiAliasingEnabled();
};