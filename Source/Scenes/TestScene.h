#pragma once

#include "Source/Scenes/Levels/Level.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"
#include "Source/Items/Ration/Ration.h"
#include "Source/Weapons/Pistol/Pistol.h"

class TestScene : public Level {
private:

	List<Vector2D> positions = {};

	Pistol* pistol = new Pistol();
	Ration* item = new Ration();
	Ration* item2 = new Ration();
	Node2D* tiles = new Node2D();

	Player* player = new Player();
	CollisionBody* body2 = new CollisionBody();
	CollisionRect* shape2 = new CollisionRect();
	CollisionBody* body = new CollisionBody();
	CollisionRect* shape = new CollisionRect();

	Button* backButton = new Button("Back");


public:
	Node2D* lastScene;
	TestScene(std::string name = "Test Scene");
	~TestScene();

	void ready() override;

	void onBackButtonPressed();

};