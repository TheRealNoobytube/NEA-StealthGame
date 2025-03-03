#include "TestScene.h"

TestScene::TestScene(std::string name) : Level(name){
	worldLayer->addChild(tiles);
	worldLayer->addChild(body);
	worldLayer->addChild(body2);

	body->addChild(shape);
	body2->addChild(shape2);

	shape->visible = true;
	shape2->visible = true;


	uiLayer->addChild(backButton);
	itemLayer->addChild(item);
	itemLayer->addChild(item2);
	itemLayer->addChild(pistol);

	pistol->position = Vector2D(20, 0);

	item2->position = Vector2D(40, 40);

	playerLayer->addChild(player);
	this->currentPlayer = this->player;

	for (int i = 0; i < 1; i++) {
		Enemy* newEnemy = new Enemy();
		enemyLayer->addChild(newEnemy);
		newEnemy->position = Vector2D(rand() / 300, rand() / 300);
	}
}

TestScene::~TestScene() {

}

void TestScene::ready() {

	player->position = Vector2D(100, 0);
	//enemy.position = Vector2D(200, 90);

	body->position = Vector2D(40, 40);
	body2->position = Vector2D(100, 60);
	shape2->setSize(Vector2D(100, 20));

	backButton->position.x = 3;
	backButton->position.y = 3;
	backButton->on_click.connect([this]() { onBackButtonPressed(); });


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

	






	for (int i = 0; i < positions.getSize(); i++) {
		CollisionBody* wall = new CollisionBody();
		wall->position = Vector2D(positions.get(i).x * navMesh->boxSize.x, positions.get(i).y * navMesh->boxSize.y);
		addChild(wall);
		CollisionRect* shape = new CollisionRect();
		shape->setSize(navMesh->boxSize);
		shape->visible = true;
		wall->addChild(shape);
	}


	__super::ready();
}

void TestScene::onBackButtonPressed() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}