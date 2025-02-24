#include "Level.h"

Level::Level(std::string name) : Node2D(name) {
	addChild(&navMesh);

	addChild(&itemLayer);
	addChild(&worldLayer);
	addChild(&enemyLayer);
	addChild(&playerLayer);
	addChild(&uiLayer);

	uiLayer.addChild(&itemsHUD);
}

void Level::ready() {
	__super::ready();

	if (currentPlayer != nullptr) {
		currentPlayer->itemsHUD = &itemsHUD;
	}

	//bake the mesh
	navMesh.bakeMesh();
}

void Level::update(float delta) {
	__super::update(delta);

	if (currentPlayer != nullptr) {

		Vector2D drawPosition = currentPlayer->getGlobalPosition();
		drawPosition = navMesh.globalToMap(drawPosition);
		drawPosition.x *= navMesh.boxSize.x;
		drawPosition.y *= navMesh.boxSize.y;


		//drawRect(drawPosition, navMesh.boxSize, Color(255, 255, 255));
	}
}