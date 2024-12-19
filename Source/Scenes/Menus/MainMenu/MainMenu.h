#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"
#include "Source/Scenes/Menus/AboutMenu/AboutMenu.h"

class MainMenu : public Node2D {
private:
	Label titleText = Label("Stealth Game");
	Button startButton = Button("Start");
	Button settingsButton = Button("Settings");
	Button aboutButton = Button("About");
	Button quitButton = Button("Quit");

	AboutMenu aboutMenuScene;

public:
	MainMenu(std::string name = "MainMenu");

	void ready() override;
	void update(float delta) override;

	void onStartButtonClick();
	void onSettingsButtonClick();
	void onAboutButtonClick();
	void onQuitButtonClick();
};