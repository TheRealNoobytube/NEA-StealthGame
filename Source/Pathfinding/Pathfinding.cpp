#include "Pathfinding.h"


Pathfinding::Pathfinding(std::string name) : Node2D(name) {

}




void Pathfinding::update(float delta) {
	__super::update(delta);

	if (!currentPath.isEmpty()) {
		for (int i = 0; i < currentPath.getSize(); i++) {
			//drawRect(currentPath.get(i), Vector2D(8, 8), Color(255, 255, 255));
		}
	}

}


void Pathfinding::findPath(Vector2D startPos, Vector2D targetPos) {

	auto level = dynamic_cast<Level*>(getSceneTree()->getCurrentScene());

	if (level == nullptr) {
		std::cout << "CURRENT SCENE IS NOT A LEVEL, NO NAVMESH AVAILABLE FOR PATHFINDING\n";
		return;
	}

	NavigationMesh* navMesh = &level->navMesh;

	startPos = navMesh->globalToMap(startPos);
	targetPos = navMesh->globalToMap(targetPos);
	AStarNode startNode = navMesh->map.get(startPos.x)->get(startPos.y);
	AStarNode targetNode = navMesh->map.get(targetPos.x)->get(targetPos.y);

	List<AStarNode> toSearch;
	List<AStarNode> processed;

	toSearch.add(startNode);

	int currentNodeIndex = 0;
	AStarNode current = toSearch.get(currentNodeIndex);

	while (!toSearch.isEmpty()) {
		currentNodeIndex = 0;
		current = toSearch.get(currentNodeIndex);
		
		//std::cout << "searchving\n";

		for (int i = 1; i < toSearch.getSize(); i++) {
			AStarNode node = toSearch.get(i);
			//std::cout << "new node pos " << node.position.x << " " << node.position.y << "\n";
			if (node.getFCost() < current.getFCost() || (node.getFCost() == current.getFCost() && node.hCost < current.hCost)) {
				currentNodeIndex = i;
				current = toSearch.get(i);
			}
		}

		toSearch.remove(currentNodeIndex);
		processed.add(current);

		if (current.position == targetNode.position) {
			constructPath(new AStarNode(current), startNode);
			//AStarNode* connection = current.connection;
			return;
		}

		//std::cout << "current pos " << current.position.x << " " << current.position.y << "\n";


		for (int i = 0; i < current.neighbors.getSize(); i++) {
			AStarNode neighbor = *current.neighbors.get(i);

			if (!neighbor.reachable || processed.find(neighbor) != -1) {
				continue;
			}

			int newCostToNeighbor = current.gCost + calculateDistance(current.position, neighbor.position);
			if (newCostToNeighbor < neighbor.gCost || toSearch.find(neighbor) == -1) {
				neighbor.gCost = newCostToNeighbor;
				neighbor.hCost = calculateDistance(neighbor.position, targetNode.position);

				//std::cout << "neighbor pos " << neighbor->position.x << " " << neighbor->position.y << "\n";

				neighbor.connection = new AStarNode(current);

				if (toSearch.find(neighbor) == -1) {
					toSearch.add(neighbor);
				}
			}
		}
	}
	constructPath(new AStarNode(current), startNode);
}


float Pathfinding::calculateDistance(Vector2D posOne, Vector2D posTwo) {
	float x = posTwo.x - posOne.x;
	float y = posTwo.y - posOne.y;

	return (x > y) ? x : y;
}



void Pathfinding::constructPath(AStarNode* first, AStarNode& startNode) {
	AStarNode* currentPathNode = first;
	List<Vector2D> tempList;
	currentPath.clear();

	while (currentPathNode->position != startNode.position) {
		tempList.add(currentPathNode->position);
		AStarNode* lastNode = currentPathNode;
		currentPathNode = currentPathNode->connection;
		delete lastNode;
	}
	delete currentPathNode;

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