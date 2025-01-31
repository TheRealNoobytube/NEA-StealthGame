#include "TestScene.h"

TestScene::TestScene(std::string name) : Level(name){
	addChild(&navMesh);
	addChild(&body);
	addChild(&body2);
	addChild(&body4);
	addChild(&buttonBody);
	addChild(&backButton);
	addChild(&player);
	addChild(&enemy);

	body.addChild(&shape);
	body2.addChild(&shape2);
	body4.addChild(&shape4);
	buttonBody.addChild(&shape3);

	this->currentPlayer = &this->player;
}


void TestScene::ready() {

	player.position = Vector2D(170, 90);
	enemy.position = Vector2D(70, 30);

	body.position = Vector2D(40, 40);
	body2.position = Vector2D(100, 60);
	shape2.setSize(Vector2D(100, 20));
	shape3.setSize(Vector2D(60, 20));

	shape3.visible = false;

	backButton.position.x = 6;
	backButton.position.y = getSceneTree()->getViewportSize().y - backButton.getSize().y - 6;

	shape3.position.x = 6;
	shape3.position.y = getSceneTree()->getViewportSize().y - shape3.getSize().y - 6;

	backButton.on_click.connect([this]() { onBackButtonPressed(); });


	body4.position = Vector2D(20, 60);
	shape4.setSize(Vector2D(100, 100));



	


	__super::ready();
}

void TestScene::onBackButtonPressed() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}