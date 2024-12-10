#include "Label.h"


Label::Label(std::string filepath, std::string name) : Node2D(name) {
	if (!filepath.empty()) {
		setFont(filepath);
	}
	
}

Label::Label(TTF_Font* font, std::string name) : Node2D(name) {
	this->font = font;
}

Label::~Label(){
	TTF_CloseFont(this->font);
	delete fontTexture;
	
}

void Label::setFont(std::string filepath) {
	TTF_CloseFont(this->font); //deletes the current font so we can replace it in this function

	this->font = TTF_OpenFont(filepath.c_str(), this->fontSize);
}

void Label::renderText() {
	std::string text = this->text;
	if (text.empty()) {
		text = " ";
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(this->font, text.c_str(), { color.r, color.g, color.b, color.a }, textWrapLength);

	delete this->fontTexture; //delete the previous texture, replace it with the new one below
	this->fontTexture = new Texture(getSceneTree()->getRenderer(), textSurface);

	SDL_FreeSurface(textSurface); // dont need textSurface anymore, won't be used anywhere 
	textSurface = nullptr; //so we deallocate it from memory to prevent a memory leak
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


void Label::ready() {
	__super::ready();
}

void Label::update(float delta) {
	__super::update(delta);
	renderText();
	Vector2D globalPos = getGlobalPosition();
	this->fontTexture->draw(globalPos.x, globalPos.y, scale.x, scale.y);
	getGlobalPosition();
}