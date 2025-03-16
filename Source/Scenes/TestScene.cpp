#include "TestScene.h"

TestScene::TestScene(std::string name) : Level(name){
	//uiLayer->addChild(backButton);
	playerLayer->addChild(player);
	this->currentPlayer = this->player;


}


void TestScene::ready() {

	backButton->position.x = getSceneTree()->getViewportSize().x - backButton->getSize().x - 3;
	backButton->position.y = 3;
	backButton->on_click.connect([this]() { onBackButtonPressed(); });

	gameOverScreen->backButton->on_click.connect([this]() { onBackButtonPressed(); });
	gameOverScreen->restartButton->on_click.connect([this]() { restartLevel(); });

	__super::ready();
}

void TestScene::onBackButtonPressed() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}

void TestScene::onGameOver() {
	__super::onGameOver();
	backButton->enabled = false;
	backButton->visible = false;

}

void TestScene::restartLevel() {
	queueFree();

	TestScene* newLevel = new TestScene();
	getSceneTree()->changeScene(newLevel);


}