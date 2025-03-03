#include "MainMenu.h"

MainMenu::MainMenu(std::string name) : Node2D(name) {
	addChild(titleText);
	addChild(startButton);
	addChild(settingsButton);
	addChild(aboutButton);
	addChild(quitButton);
}

void MainMenu::ready() {
	__super::ready();

	Vector2D viewportSize = getSceneTree()->getViewportSize();
	titleText->setTextWrapLength(600);
	titleText->setFontSize(50);
	titleText->scale = Vector2D(0.5, 0.5);

	//set the x position of all the ui elements to be centered in the viewport
	titleText->position.x = (viewportSize.x / 2) - (titleText->getTextSize().x / 2) * titleText->scale.x;
	titleText->position.y = 3;

	startButton->position.x = (viewportSize.x / 2) - (startButton->getSize().x / 2);
	startButton->position.y = 50;

	settingsButton->position.x = (viewportSize.x / 2) - (settingsButton->getSize().x / 2);
	settingsButton->position.y = 80;

	aboutButton->position.x = (viewportSize.x / 2) - (aboutButton->getSize().x / 2);
	aboutButton->position.y = 110;

	quitButton->position.x = (viewportSize.x / 2) - (quitButton->getSize().x / 2);
	quitButton->position.y = 140;

	//connect all the onClick methods
	startButton->on_click.connect([this]() {this->onStartButtonClick(); });
	settingsButton->on_click.connect([this]() {this->onSettingsButtonClick(); });
	aboutButton->on_click.connect([this]() {this->onAboutButtonClick(); });
	quitButton->on_click.connect([this]() {this->onQuitButtonClick(); });
}


void MainMenu::onStartButtonClick() {
	TestScene* testScene = new TestScene();
	testScene->lastScene = this;
	getSceneTree()->changeScene(testScene);
}

void MainMenu::onSettingsButtonClick() {
	SettingsMenu* settingsMenu = new SettingsMenu();
	settingsMenu->lastScene = this;
	getSceneTree()->changeScene(settingsMenu);
}

void MainMenu::onAboutButtonClick() {
	AboutMenu* aboutMenu = new AboutMenu();
	aboutMenu->lastScene = this;
	getSceneTree()->changeScene(aboutMenu);
}

void MainMenu::onQuitButtonClick() {
	SDL_Event event = { SDL_QUIT }; //pushes the quit event in order to close the application
	SDL_PushEvent(&event);
}

void MainMenu::update(float delta){
	__super::update(delta);
}