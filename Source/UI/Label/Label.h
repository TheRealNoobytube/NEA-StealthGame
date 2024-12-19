#pragma once
#include "SDL_ttf.h"
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Application/Texture.h"

class Label : public Node2D {
private:
	TTF_Font* font = nullptr;
	SDL_Surface* textSurface = nullptr;
	Texture* fontTexture = nullptr;
	std::string fontFilePath;

	
	int fontSize = 14;
	int textWrapLength = 200;
	Vector2D textSize = Vector2D(0,0);

public:
	Color color = Color(0, 0, 0, 255);
	std::string text;
	bool antiAliasing = true;
	
	Label(std::string text = " ", std::string name = "Label");
	Label(TTF_Font* font, std::string name = "Label");
	~Label();

	void setFont(std::string filepath);
	void generateTextSurface();
	void renderText();

	void setTextWrapLength(int textWrapLength);
	int getTextWrapLength();

	void setFontSize(int fontSize);
	int getFontSize();

	Vector2D getTextSize();

	void ready() override;
	void update(float delta) override;


};