#include "Pathfinding.h"


Pathfinding::Pathfinding(std::string name) : Node2D(name) {

}

void Pathfinding::ready() {
	__super::ready();
	auto level = dynamic_cast<Level*>(getSceneTree()->getCurrentScene());

	if (level == nullptr) {
		std::cout << "CURRENT SCENE IS NOT A LEVEL, NO NAVMESH AVAILABLE FOR PATHFINDING\n";
	}
	else {
		this->navMesh = level->navMesh;
	}
}

void Pathfinding::update(float delta) {
	__super::update(delta);

	if (drawPath) {
		for (int i = 0; i < currentPath.getSize(); i++) {
			drawRect(Vector2D(currentPath.get(i).x + navMesh->getGlobalPosition().x, currentPath.get(i).y + navMesh->getGlobalPosition().y), navMesh->boxSize, Color(255, 255, 255, 140));
		}


		if (currentPath.getSize() > 0) {

			Vector2D nextPoint = currentPath.get(0);
			nextPoint.x += navMesh->boxSize.x / 2;
			nextPoint.y += navMesh->boxSize.y / 2;

			drawRect(nextPoint, Vector2D(2, 2), Color(255, 255, 0));

		}

	}
}

bool Pathfinding::findPath(Vector2D startPos, Vector2D targetPos) {
	if (navMesh == nullptr) {
		return false;
	}

	if (navMesh->isInvalidMapPosition(navMesh->globalToMap(targetPos)) || navMesh->isInvalidMapPosition(navMesh->globalToMap(startPos))) {
		std::cout << "START OR TARGET POSITIONS OUT OF RANGE OF THE NAVIGATION MESH\n";
		return false;
	}

	bool targetReachable = false;
	if (!navMesh->getNode(targetPos).reachable) {
		for (int i = 0; i < navMesh->getNode(targetPos).neighbors.getSize(); i++) {
			if (navMesh->getNode(targetPos).neighbors.get(i)->reachable) {
				targetPos = navMesh->getNode(targetPos).neighbors.get(i)->position;
				targetReachable = true;
				break;
			}
		}
	}
	else {
		targetReachable = true;
	}

	if (!targetReachable) {
		std::cout << "TARGET IS NOT REACHABLE, CANNOT PATHFIND TO TARGET\n";
		return false;
	}
	
	List<AStarNode> toSearch = { navMesh->getNode(startPos) };
	List<AStarNode> processed;

	while (!toSearch.isEmpty()) {
		int index = 0;
		AStarNode current = toSearch.get(index);

		for (int i = 1; i < toSearch.getSize(); i++) {
			if (toSearch.get(i).getFCost() < current.getFCost() || toSearch.get(i).getFCost() == current.getFCost() && toSearch.get(i).hCost < current.hCost) {
				index = i;
				current = toSearch.get(index);
			}
		}

		toSearch.remove(index);
		processed.add(current);

		Vector2D targetPosFixedToMap = navMesh->mapToGlobal(navMesh->globalToMap(targetPos));

		if (current.position == targetPosFixedToMap) {
			constructPath(&navMesh->getNode(current.position), navMesh->getNode(startPos));
			return true;
		}

		for (int i = 0; i < current.neighbors.getSize(); i++) {
			AStarNode neighbor = *current.neighbors.get(i);

			if (!neighbor.reachable || processed.has(neighbor)) {
				continue;
			}

			float newCostToNeighbor = current.gCost + calculateDistance(current.position, neighbor.position);

			if (newCostToNeighbor < neighbor.gCost || !toSearch.has(neighbor)) {

				navMesh->getNode(neighbor.position).connection = &navMesh->getNode(current.position);
				navMesh->getNode(neighbor.position).gCost = newCostToNeighbor;
				navMesh->getNode(neighbor.position).hCost = calculateDistance(neighbor.position, targetPos);

				if (!toSearch.has(neighbor)) {
					toSearch.add(navMesh->getNode(neighbor.position));
				}
			}
		}
	}

	return false;
}


float Pathfinding::calculateDistance(Vector2D posOne, Vector2D posTwo) {
	float x = abs(posTwo.x - posOne.x);
	float y = abs(posTwo.y - posOne.y);


	//return (x > y) ? y : x;
	return sqrt(x * x + y * y);
}



void Pathfinding::constructPath(AStarNode* first, AStarNode startNode) {
	AStarNode* currentPathNode = first;
	List<Vector2D> tempList;
	currentPath.clear();

	while (currentPathNode->position != startNode.position) {
		tempList.add(Vector2D(currentPathNode->position.x , currentPathNode->position.y));
		currentPathNode = currentPathNode->connection;
	}

	List<Vector2D> simplifiedList;
	Vector2D lastDirection = Vector2D(0, 0);

	for (int i = tempList.getSize() - 1; i >= 0; i--) {
		currentPath.add(tempList.get(i));
	}
}


void Pathfinding::followPath(Entity* entity) {
	if (currentPath.isEmpty()) {
		return;
	}

	Vector2D nextPoint = currentPath.get(0);
	nextPoint.x += navMesh->boxSize.x / 2;
	nextPoint.y += navMesh->boxSize.y / 2;

	Vector2D navMeshGlobalPos = navMesh->getGlobalPosition();

	nextPoint.x += navMeshGlobalPos.x;
	nextPoint.y += navMeshGlobalPos.y;

	Vector2D entityGlobalPos = entity->getGlobalPosition();

	Vector2D directionToNextPoint;
	directionToNextPoint.x = nextPoint.x - entityGlobalPos.x;
	directionToNextPoint.y = nextPoint.y - entityGlobalPos.y;
	directionToNextPoint = directionToNextPoint.normalized();
	
	entity->movement->direction = directionToNextPoint;
	entity->movement->velocity.x = entity->speed * entity->movement->direction.x;
	entity->movement->velocity.y = entity->speed * entity->movement->direction.y;

	entity->movement->applyVelocity();

	if (entityGlobalPos.x > nextPoint.x - desiredDistanceToPoint && entityGlobalPos.x < nextPoint.x + desiredDistanceToPoint) {
		if (entityGlobalPos.y > nextPoint.y - desiredDistanceToPoint && entityGlobalPos.y < nextPoint.y + desiredDistanceToPoint) {
			currentPath.remove(0);

			if (currentPath.isEmpty()) {
				target_reached.emit();
			}
		}
	}
}

