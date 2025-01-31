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
		this->navMesh = &level->navMesh;
	}
}

void Pathfinding::update(float delta) {
	__super::update(delta);

}

void Pathfinding::findPath(Vector2D startPos, Vector2D targetPos) {

	if (navMesh == nullptr) {
		return;
	}

	if (navMesh->isInvalidMapPosition(navMesh->globalToMap(targetPos)) || navMesh->isInvalidMapPosition(navMesh->globalToMap(startPos))) {
		std::cout << "START OR TARGET POSITIONS OUT OF RANGE OF THE NAVIGATION MESH\n";
		return;
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
		return;
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
			return;
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
}


float Pathfinding::calculateDistance(Vector2D posOne, Vector2D posTwo) {
	float x = abs(posTwo.x - posOne.x);
	float y = abs(posTwo.y - posOne.y);

	return (x < y) ? x : y;
}



void Pathfinding::constructPath(AStarNode* first, AStarNode startNode) {
	AStarNode* currentPathNode = first;
	List<Vector2D> tempList;
	currentPath.clear();

	while (currentPathNode->position != startNode.position) {
		tempList.add(currentPathNode->position);
		AStarNode* lastNode = currentPathNode;
		currentPathNode = currentPathNode->connection;
	}

	for (int i = tempList.getSize() - 1; i >= 0; i--) {
		currentPath.add(tempList.get(i));
	}
}


void Pathfinding::followPath(Entity& entity, MovementComponent& movement) {



	//std::cout << "ffollowing\n";

	Vector2D nextPoint = currentPath.get(0);
	Vector2D entityGlobalPos = entity.getGlobalPosition();

	//drawRect(entityGlobalPos, Vector2D(8, 8), Color(255, 255, 0));
	//drawRect(nextPoint, Vector2D(8, 8), Color(0, 255, 255));

	Vector2D directionToNextPoint;
	directionToNextPoint.x = nextPoint.x - entityGlobalPos.x;
	directionToNextPoint.y = nextPoint.y - entityGlobalPos.y;
	directionToNextPoint = directionToNextPoint.normalized();
	
	movement.direction = directionToNextPoint;
	movement.velocity.x = entity.speed * movement.direction.x;
	movement.velocity.y = entity.speed * movement.direction.y;

	movement.applyVelocity();

	if (entityGlobalPos.x > nextPoint.x - desiredDistanceToPoint && entityGlobalPos.x < nextPoint.x + desiredDistanceToPoint) {
		if (entityGlobalPos.y > nextPoint.y - desiredDistanceToPoint && entityGlobalPos.y < nextPoint.y + desiredDistanceToPoint) {
			currentPath.remove(0);
		}
	}
}