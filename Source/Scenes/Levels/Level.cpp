#include "Level.h"

Level::Level(std::string name) : Node2D(name) {
	addChild(&navMesh);
}

void Level::ready() {
	__super::ready();

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