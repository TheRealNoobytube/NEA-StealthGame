#include "MainMenu.h"

MainMenu::MainMenu(std::string name) : Node2D(name) {
	addChild(&titleText);
	addChild(&startButton);
	addChild(&quitButton);
}

void MainMenu::ready() {
	__super::ready();

	titleText.setFont(getSceneTree()->getBasePath() + "..\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf");
	titleText.text = "Stealth Game";
	titleText.position.x = 250;
	titleText.position.y = 30;

	startButton.setText("Start");
	startButton.position.x = 250;
	startButton.position.y = 120;

	quitButton.setText("Quit");
	quitButton.position.x = 250;
	quitButton.position.y = 180;


}

void MainMenu::update(float delta){
	__super::update(delta);
}