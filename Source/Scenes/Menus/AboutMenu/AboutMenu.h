#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"

class AboutMenu : public Node2D{
private:
	Label aboutText = Label("This is a game about stealth\nYeag");
	Button backButton = Button("Back");

	Texture* frame;
	IMG_Animation* animation;

public:
	Node* lastScene;

	AboutMenu(std::string name = "AboutMenu");

	void ready() override;
	void update(float delta) override;

	void onBackButtonClick();

};