#pragma once

#include "SDL_ttf.h"
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Application/Texture.h"
#include "Source/UI/Label/Label.h"
#include <functional>

class Button : public Node2D {
private:
	Label* label = new Label();
	Vector2D size = Vector2D(60, 20);
	Color normalColor = Color(53, 68, 127);
	Color pressColor = Color(33, 48, 107);
	Color hoverColor = Color(73, 88, 147);
	Color currentColor = normalColor;

	Texture normalTexture = Texture();
	Texture hoverTexture = Texture();
	Texture pressedTexture = Texture();
	Texture currentTexture;

	bool useTextures = true;
	bool isMouseInside = false;
	bool pressed = false;

public:
	bool visible = true;
	bool enabled = true;

	bool isClickedWhenLetGo = true;

	Button(std::string text = " ", std::string name = "Button");

	Signal<> on_click;
	Signal<> on_release;
	Signal<> on_mouse_enter;
	Signal<> on_mouse_exit;

	void ready() override;
	void update(float delta) override;

	void onClick();
	void onRelease();
	void onMouseEnter();
	void mouseInside();
	void onMouseExit();

	Vector2D getSize();
	void setSize(Vector2D size);

	void setText(std::string text);
	std::string getText();
	void setAntiAliasing(bool antiAliasing);
	bool antiAliasingEnabled();
	bool isPressed();

	void setNormalTexture(std::string filePath);
	void setHoverTexture(std::string filePath);
	void setPressTexture(std::string filePath);
};