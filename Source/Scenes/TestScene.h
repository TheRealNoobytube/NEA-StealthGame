#pragma once

#include "Source/Scenes/Levels/Level.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"
#include "Source/Items/Ration/Ration.h"
#include "Source/Weapons/Pistol/Pistol.h"

class TestScene : public Level {
private:

	List<Vector2D> positions = {};

	Pistol pistol;
	Ration item;
	Ration item2;
	Node2D tiles;

	Player player;
	CollisionBody body2;
	CollisionRect shape2;
	CollisionBody body;
	CollisionRect shape;

	Button backButton = Button("Back");


public:
	Node2D* lastScene;
	TestScene(std::string name = "Test Scene");
	~TestScene();

	void ready() override;

	void onBackButtonPressed();

};