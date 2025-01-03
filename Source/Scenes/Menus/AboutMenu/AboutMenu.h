#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"

class AboutMenu : public Node2D{
private:
	Label aboutText = Label();
	Button backButton = Button("Back");

public:
	Node* lastScene;

	AboutMenu(std::string name = "AboutMenu");

	void ready() override;
	void update(float delta) override;

	void onBackButtonClick();

};