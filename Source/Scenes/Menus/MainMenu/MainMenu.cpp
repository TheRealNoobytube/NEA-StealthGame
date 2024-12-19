#include "MainMenu.h"

MainMenu::MainMenu(std::string name) : Node2D(name) {
	addChild(&titleText);
	addChild(&startButton);
	addChild(&settingsButton);
	addChild(&aboutButton);
	addChild(&quitButton);

}

void MainMenu::ready() {
	__super::ready();

	aboutMenuScene.lastScene = this;

	Vector2D viewportSize = getSceneTree()->getViewportSize();
	titleText.setTextWrapLength(600);
	titleText.setFontSize(26);

	//set the x position of all the ui elements to be centered in the viewport
	titleText.position.x = (viewportSize.x / 2) - (titleText.getTextSize().x / 2);
	titleText.position.y = 3;

	startButton.position.x = (viewportSize.x / 2) - (startButton.getSize().x / 2);
	startButton.position.y = 50;

	settingsButton.position.x = (viewportSize.x / 2) - (settingsButton.getSize().x / 2);
	settingsButton.position.y = 80;

	aboutButton.position.x = (viewportSize.x / 2) - (aboutButton.getSize().x / 2);
	aboutButton.position.y = 110;

	quitButton.position.x = (viewportSize.x / 2) - (quitButton.getSize().x / 2);
	quitButton.position.y = 140;

	//connect all the onClick methods
	startButton.on_click.connect([this]() {this->onStartButtonClick(); });
	settingsButton.on_click.connect([this]() {this->onSettingsButtonClick(); });
	aboutButton.on_click.connect([this]() {this->onAboutButtonClick(); });
	quitButton.on_click.connect([this]() {this->onQuitButtonClick(); });
}


void MainMenu::onStartButtonClick() {

}

void MainMenu::onSettingsButtonClick() {

}

void MainMenu::onAboutButtonClick() {
	getSceneTree()->changeScene(&aboutMenuScene);
}

void MainMenu::onQuitButtonClick() {
	SDL_Event event = { SDL_QUIT }; //pushes the quit event in order to close the application
	SDL_PushEvent(&event);
}

void MainMenu::update(float delta){
	__super::update(delta);
}