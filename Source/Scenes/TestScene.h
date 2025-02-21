#pragma once

#include "Source/Scenes/Levels/Level.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"

class TestScene : public Level {
private:

	List<Vector2D> positions = {};



	Node2D tiles;


	Enemy enemy;
	Player player;
	CollisionBody body2;
	CollisionRect shape2;
	CollisionBody body;
	CollisionRect shape;

	Button backButton = Button("Back");


public:
	Node2D* lastScene;
	TestScene(std::string name = "Test Scene");

	void ready() override;

	void onBackButtonPressed();

};