#pragma once
#include "SDL_ttf.h"
#include "../../Nodes/Node2D/Node2D.h"
#include "../../Application/Texture.h"

class Label : public Node2D {
private:
	TTF_Font* font = nullptr;
	Texture* fontTexture = nullptr;
	std::string fontFilePath;

	int fontSize = 20;
	int textWrapLength = 200;

public:
	Color color = Color(0, 0, 0, 255);
	std::string text;
	
	Label(std::string filepath = "", std::string name = "Label");
	Label(TTF_Font* font, std::string name = "Label");
	~Label();

	void setFont(std::string filepath);
	void renderText();

	void setTextWrapLength(int textWrapLength);
	int getTextWrapLength();

	void setFontSize(int fontSize);
	int getFontSize();

	void ready() override;
	void update(float delta) override;


};