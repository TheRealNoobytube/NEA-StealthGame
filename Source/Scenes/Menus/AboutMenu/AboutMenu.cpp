#include "AboutMenu.h"

AboutMenu::AboutMenu( std::string name) : Node2D(name){
	addChild(&aboutText);
	addChild(&backButton);
}

void AboutMenu::ready() {
	Vector2D viewportSize = getSceneTree()->getViewportSize();

	aboutText.position.x = (viewportSize.x / 2) - (aboutText.getTextSize().x / 2) + 60;
	aboutText.position.y = 2;

	aboutText.color = Color(10, 255, 255);

	backButton.position.x = (viewportSize.x / 2) - (backButton.getSize().x / 2);
	backButton.position.y = viewportSize.y - 60;

	backButton.on_click.connect([this]() { this->onBackButtonClick(); });


	const int frames = 4;
	SDL_Rect spriteClip[frames];

	std::string file = getSceneTree()->getBasePath() + "..\\Assets\\majima.gif";

	animation = IMG_LoadAnimation(file.c_str());

	std::cout << "" << animation->count;


	frame = new Texture(getSceneTree()->getRenderer(), animation->frames[0]);
	

}

int i = 0;
int currentFrame = 0;

void AboutMenu::update(float delta) {
	i++;
	if (i >= *animation->delays) {
		currentFrame = (currentFrame + 1) % animation->count;

		frame->setTexture(animation->frames[currentFrame]);
		i = 0;

	}

	frame->draw(position.x, position.y, scale.x / 3, scale.y / 3);
}

void AboutMenu::onBackButtonClick() {
	getSceneTree()->changeScene(lastScene);
}