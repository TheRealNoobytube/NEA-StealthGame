#include "Label.h"


Label::Label(TTF_Font* font, std::string name) : Node2D(name) {
	this->font = font;
}

Label::Label(std::string text, std::string name) : Node2D(name) {
	this->text = text;
}

Label::~Label() {
	this->text = text;
	TTF_CloseFont(this->font);
	delete fontTexture;
}

void Label::setFont(std::string filepath) {
	TTF_CloseFont(this->font); //deletes the current font so we can replace it in this function
	this->font = TTF_OpenFont(filepath.c_str(), this->fontSize);
	this->fontFilePath = filepath;
	generateTextSurface(); //updates the textSize variable so you don't have to wait until next frame to get the updated size information
}


void Label::generateTextSurface() {
	std::string text = this->text; 
	if (text.empty()) { //cant render text if theres no text to render, so we set text to a single whitespace if its empty
		text = " ";
	}

	SDL_FreeSurface(this->textSurface); //deletes the current textSurface so we can replace it in this function

	//creates a surface used to generate a texture
	if (antiAliasing) {
		this->textSurface = TTF_RenderText_Blended_Wrapped(this->font, text.c_str(), { color.r, color.g, color.b, color.a }, textWrapLength);
	}
	else {
		this->textSurface = TTF_RenderText_Solid_Wrapped(this->font, text.c_str(), { color.r, color.g, color.b, color.a }, textWrapLength);
	}

	if (textSurface != nullptr) {
		textSize = Vector2D(this->textSurface->w, this->textSurface->h);
	}
}


void Label::renderText() {
	generateTextSurface();

	delete this->fontTexture; //delete the previous texture, replace it with the new one below
	this->fontTexture = new Texture(textSurface);

	Vector2D globalPos = getGlobalPosition();
	this->fontTexture->draw(globalPos.x, globalPos.y, scale.x, scale.y);

}


void Label::setTextWrapLength(int textWrapLength) {
	if (textWrapLength < this->fontSize) { //dont want a negative wrap length
		textWrapLength = this->fontSize;
	}
	if (textWrapLength > 640) { //dont want the wrap length to be unnecesarily big, takes up a lot of memory
		textWrapLength = 640;
	}

	this->textWrapLength = textWrapLength;
}

int Label::getTextWrapLength() {
	return this->textWrapLength;
}

void Label::setFontSize(int fontSize) {
	if (fontSize <= 0) { //dont want a negative font size
		fontSize = 1;
	}
	else if (fontSize > 100) { //dont want a font to be too big, takes up a lot of memory
		fontSize = 100;		   //a less memory intensive way to get a bigger font would be to change the scale values
	}

	this->fontSize = fontSize;
	setFont(this->fontFilePath);
}

int Label::getFontSize() {
	return this->fontSize;
}

Vector2D Label::getTextSize() {
	return textSize;
}


void Label::ready() {
	__super::ready();
	if (font == nullptr) {
		setFont(getSceneTree()->getBasePath() + "..\\Fonts\\opensans.ttf");
	}
	generateTextSurface();
}

void Label::update(float delta) {
	__super::update(delta);
	renderText();
}