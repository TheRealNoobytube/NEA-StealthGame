#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Collision/CollisionBody.h"

class NavigationMesh : public Node2D{
public:
	NavigationMesh(std::string name = "NavigationMesh");

	struct NavigationNode {

		NavigationNode(Vector2D position = Vector2D(0, 0)) : position(position) {}
		Vector2D position;
		List<NavigationNode*> neighbors;
		float gCost = 0;
		float hCost = 0;
		float fCost = 0;
		//Color color = Color((float)(rand()), (float)(rand()), (float)(rand()));
		Color color = Color(0, 110, 200);
	};

	int bakingCollisionLayer = 1;

	void ready() override;
	void update(float delta) override;
	
	void bakeMesh();

private:
	List<NavigationNode> map;

	Vector2D boxSize = Vector2D(8, 8);
	Vector2D size = Vector2D(96 * 2, 96 * 2);

};