#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"
#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"

class AboutMenu : public Node2D{
private:
	Label* aboutText = new Label();
	Button* backButton = new Button("Back");

public:
	Node* lastScene;

	AnimatedSprite* balls = new AnimatedSprite();

	AboutMenu(std::string name = "AboutMenu");

	void ready() override;
	void update(float delta) override;

	void onBackButtonClick();

};