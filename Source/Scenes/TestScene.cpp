#include "TestScene.h"

TestScene::TestScene(std::string name) : Level(name){
	addChild(&tiles);

	addChild(&body);
	addChild(&body2);

	addChild(&player);
	addChild(&enemy);

	body.addChild(&shape);
	body2.addChild(&shape2);

	this->currentPlayer = &this->player;

	Node* layerUI = new Node();
	layerUI->addChild(&backButton);
	addChild(layerUI);
}


void TestScene::ready() {

	player.position = Vector2D(100, 0);
	enemy.position = Vector2D(200, 90);

	body.position = Vector2D(40, 40);
	body2.position = Vector2D(100, 60);
	shape2.setSize(Vector2D(100, 20));

	backButton.position.x = 6;
	backButton.position.y = getSceneTree()->getViewportSize().y - backButton.getSize().y - 6;
	backButton.on_click.connect([this]() { onBackButtonPressed(); });


	//for (int i = 0; i < 8; i++) {
	//	positions.add(Vector2D(45 + i, 20));
	//	positions.add(Vector2D(45, 12 + i));
	//	positions.add(Vector2D(52, 12 + i));
	//}

	//for (int i = 0; i < 6; i++) {
	//	positions.add(Vector2D(46 + i, 12));
	//}


	/*positions.add(Vector2D(45, 21));
	positions.add(Vector2D(51, 21));
	positions.add(Vector2D(52, 21));*/

	

	for (int i = 0; i < 0; i++) {
		Enemy* newEnemy = new Enemy();
		addChild(newEnemy);

		newEnemy->position = Vector2D(rand() / 300, rand() / 300);


	}




	for (int i = 0; i < positions.getSize(); i++) {
		CollisionBody* wall = new CollisionBody();
		wall->position = Vector2D(positions.get(i).x * navMesh.boxSize.x, positions.get(i).y * navMesh.boxSize.y);
		addChild(wall);
		CollisionRect* shape = new CollisionRect();
		shape->setSize(navMesh.boxSize);
		wall->addChild(shape);
	}


	__super::ready();
}

void TestScene::onBackButtonPressed() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}