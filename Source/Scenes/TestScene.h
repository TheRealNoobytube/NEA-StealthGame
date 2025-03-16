#pragma once

#include "Source/Scenes/Levels/Level.h"
#include "Source/Entities/Player/Player.h"
#include "Source/Entities/Enemy/Enemy.h"
#include "Source/Items/Ration/Ration.h"
#include "Source/Weapons/Pistol/Pistol.h"

class TestScene : public Level {
private:
	Player* player = new Player();
	Button* backButton = new Button("Back");

public:
	Node2D* lastScene;
	TestScene(std::string name = "Test Scene");

	void ready() override;

	void onBackButtonPressed();



	void restartLevel();
	void onGameOver() override;

};