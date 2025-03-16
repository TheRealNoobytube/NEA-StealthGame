#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(std::string name) : Node2D(name){
	addChild(background);
	addChild(restartButton);
	addChild(backButton);
	addChild(gameOverText);
}



void GameOverScreen::ready() {
	background->color.a = 0;
	background->size = getSceneTree()->getViewportSize();
	background->ignoreRenderOffset = true;

	Vector2D viewportSize = getSceneTree()->getViewportSize();

	gameOverText->scale = Vector2D(0.5, 0.5);
	gameOverText->setTextWrapLength(400);
	gameOverText->setFontSize(60);
	gameOverText->position.x = (viewportSize.x / 2) - (gameOverText->getTextSize().x / 2) * gameOverText->scale.x;
	gameOverText->position.y = 40;
	gameOverText->color = Color(255, 255, 255);
	gameOverText->visible = false;

	restartButton->position.x = 20;
	restartButton->position.y = viewportSize.y * 0.75;

	backButton->position.x = viewportSize.x - backButton->getSize().x - 20;
	backButton->position.y = viewportSize.y * 0.75;

	restartButton->visible = false;
	restartButton->enabled = false;
	backButton->visible = false;
	backButton->enabled = false;

}

void GameOverScreen::physicsUpdate(float delta) {


	if (startGameOverSequence) {

		background->color.a -= 5;

		if (background->color.a <= 0) {
			startGameOverSequence = false;
			showBlackScreen = true;

			background->color = Color(0, 0, 0, 0);
		}
	}

	if (showBlackScreen) {
		background->color.a += 2;

		if (background->color.a >= 254) {
			showBlackScreen = false;
			restartButton->visible = true;
			backButton->visible = true;
			restartButton->enabled = true;
			backButton->enabled = true;
			gameOverText->visible = true;


		}
	}
}

void GameOverScreen::gameOver() {

	startGameOverSequence = true;
	background->color.a = 255;

	std::cout << "bwomp\n";

}