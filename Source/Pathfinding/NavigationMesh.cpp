#include "NavigationMesh.h"

NavigationMesh::NavigationMesh(std::string name) : Node2D(name) {

}

NavigationMesh::~NavigationMesh() {
	for (int i = map.getSize() - 1; i >= 0; i--) {
		delete map.get(i);
	}
}


void NavigationMesh::ready() {
	__super::ready();
}

void NavigationMesh::update(float delta) {
	__super::update(delta);

	int ratioX = size.x / boxSize.x;
	int ratioY = size.y / boxSize.y;

	for (int x = 0; x < map.getSize(); x++) {
		for (int y = 0; y < map.get(x)->getSize(); y++) {
			//AStarNode node = map.get(x)->get(y);

			if (map.get(x)->get(y).reachable) {
				drawRect(Vector2D(map.get(x)->get(y).position.x + 0.5, map.get(x)->get(y).position.y + 0.5), Vector2D(boxSize.x - 1, boxSize.y - 1), Color(50, 100, 220, 100));
			}
			else {
				drawRect(Vector2D(map.get(x)->get(y).position.x + 0.5, map.get(x)->get(y).position.y + 0.5), Vector2D(boxSize.x - 1, boxSize.y - 1), Color(0, 190, 0, 100));
			}

		}
	}
}


void NavigationMesh::bakeMesh() {
	if (!map.isEmpty()) {
		map.clear();
	}

	Vector2D globalPosition = getGlobalPosition();
	int mapSpaceX = size.x / boxSize.x;
	int mapSpaceY = size.y / boxSize.y;

	CollisionBody* tempBody = new CollisionBody();
	CollisionRect* tempRect = new CollisionRect();

	tempRect->setSize(boxSize);
	tempBody->mask = bakingCollisionLayer;
	tempBody->addChild(tempRect);
	addChild(tempBody);

	//initialize the grid, any nodes that overlap with a collision body in the bakingCollisionLayer are considered unreachable
	for (int x = 0; x < mapSpaceX; x++) {
		map.add(new List<AStarNode>());
		for (int y = 0; y < mapSpaceY; y++) {
			AStarNode node;
			Vector2D nodePosition = Vector2D(x * boxSize.x, y * boxSize.y);
			node.position = nodePosition;

			if (nodePosition.x == 0 || nodePosition.y == 0) {
				node.reachable = false;
			}
			else {
				tempRect->position = nodePosition;
				List<CollisionBody*> bodies = tempBody->requestCollisions();
				if (!bodies.isEmpty()) {
					node.reachable = false;
				}
				bodies.clear();
			}

			map.get(x)->add(node);
		}
	}

	tempBody->queueFree();

	//adding neighbors to each node
	for (int x = 0; x < mapSpaceX; x++) {
		for (int y = 0; y < mapSpaceY; y++) {
			AStarNode& current = map.get(x)->get(y);

			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i == 0 && j == 0) {
						continue;
					}

					if ((i + x) > 0 && (i + x) < mapSpaceX && (j + y) > 0 && (j + y) < mapSpaceY){

						current.neighbors.add(&map.get(x + i)->get(y + j));
					}
				}
			}
		}
	}
}

NavigationMesh::AStarNode& NavigationMesh::getNode(Vector2D position) {
	position = globalToMap(position);
	return map.get(position.x)->get(position.y);
}


Vector2D NavigationMesh::globalToMap(Vector2D position) {
	int x = (int)floor(position.x / boxSize.x);
	int y = (int)floor(position.y / boxSize.y);
	
	return Vector2D(x, y);
}

Vector2D NavigationMesh::mapToGlobal(Vector2D position) {

	return Vector2D(position.x * boxSize.x, position.y * boxSize.y);
}

bool NavigationMesh::isInvalidMapPosition(Vector2D position) {
	if (map.isEmpty()) {
		return true;
	}

	if (position.x < 0 || position.y < 0) {
		return true;
	}

	if (position.x >= map.getSize() || position.y >= map.get(0)->getSize()) {
		return true;
	}

	return false;
}