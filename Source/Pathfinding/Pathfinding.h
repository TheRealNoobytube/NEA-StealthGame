#pragma once
#include "Source/Scenes/Levels/Level.h"
#include "Source/Components/Movement/MovementComponent.h"
using AStarNode = NavigationMesh::AStarNode;

class Pathfinding : public Node2D {
private:

	float calculateDistance(Vector2D posOne, Vector2D posTwo);

	void constructPath(AStarNode* first, AStarNode& startNode);

public:
	Pathfinding(std::string name = "Pathfinding");

	List<Vector2D> currentPath;

	float desiredDistanceToPoint = 10;


	void followPath(Entity& node, MovementComponent& movement);

	void findPath(Vector2D start, Vector2D target);

	void update(float delta) override;
};