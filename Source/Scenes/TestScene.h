#pragma once

#include "Source/Scenes/Levels/Level.h"



class TestScene : public Level {
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