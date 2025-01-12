#include "NavigationMesh.h"

NavigationMesh::NavigationMesh(std::string name) : Node2D(name) {

}


void NavigationMesh::ready() {
	__super::ready();
}
void NavigationMesh::update(float delta) {
	__super::update(delta);

	int ratioX = size.x / boxSize.x;
	int ratioY = size.y / boxSize.y;

	for (int i = 0; i < map.getSize(); i++) {
		NavigationNode node = map.get(i);
		drawRect(node.position, boxSize, node.color);
	}
}


void NavigationMesh::bakeMesh() {
	if (!map.isEmpty()) {
		map.clear();
	}

	int ratioX = size.x / boxSize.x;
	int ratioY = size.y / boxSize.y;

	CollisionBody* tempBody = new CollisionBody();
	tempBody->mask = bakingCollisionLayer;
	addChild(tempBody);

	for (int y = 0; y < ratioY; y++) {
		for (int x = 0; x < ratioX; x++) {
			Vector2D navigationNodePosition = Vector2D(x * boxSize.x, y * boxSize.y);

			CollisionRect* tempRect = new CollisionRect();
			tempRect->setSize(boxSize);
			tempRect->position = navigationNodePosition;
			tempBody->addChild(tempRect);

			List<CollisionBody*> bodies = tempBody->requestCollisions();

			if (bodies.isEmpty()) {
				NavigationNode node;
				node.position = navigationNodePosition;
				map.add(node);
			}

			tempBody->removeChild(tempRect);
			delete tempRect;
		}
	}

	removeChild(tempBody);
	delete tempBody;
}