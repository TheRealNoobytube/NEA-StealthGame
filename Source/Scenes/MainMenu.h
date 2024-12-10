#pragma once
#include "../Nodes/Node2D/Node2D.h"
#include "../UI/Button/Button.h"

class MainMenu : public Node2D {
private:
	Label titleText;
	Button startButton;
	Button quitButton;

public:
	MainMenu(std::string name = "MainMenu");

	void ready() override;
	void update(float delta) override;

};