#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"
#include "Source/Nodes/Rectangle/Rectangle.h"

class GameOverScreen : public Node2D {
public:
	GameOverScreen(std::string name = "GameOverScreen");




	Rectangle* background = new Rectangle();

	Label* gameOverText = new Label("Game Over");
	Button* restartButton = new Button("Restart");
	Button* backButton = new Button("Back");

	bool startGameOverSequence = false;
	bool showBlackScreen = false;


	void ready();
	void physicsUpdate(float delta) override;

	void gameOver();



};

