#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/UI/Button/Button.h"
#include "Source/Entities/Enemy/Enemy.h"

class TestScene : public Node2D {
private:
	Enemy enemy;


	Player player;
	CollisionBody body2;
	CollisionRect shape2;
	CollisionBody body;
	CollisionRect shape;


	CollisionBody buttonBody;
	CollisionRect shape3;
	Button backButton = Button("Back");
	


public:
	Node2D* lastScene;
	TestScene(std::string name = "Test Scene");

	void ready() override;

	void onBackButtonPressed();

};