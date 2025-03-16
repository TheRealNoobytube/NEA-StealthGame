#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"
#include "Source/Scenes/Menus/AboutMenu/AboutMenu.h"
#include "Source/Scenes/Menus/SettingsMenu/SettingsMenu.h"
#include "Source/Scenes/TestScene.h"
#include "Source/Nodes/Rectangle/Rectangle.h"

class MainMenu : public Node2D {
private:
	Label* titleText = new Label("Stealth Game");
	Button* startButton = new Button("Start");
	Button* settingsButton = new Button("Settings");
	Button* aboutButton = new Button("About");
	Button* quitButton = new Button("Quit");


	Label* loadingText = new Label("Loading...");
	Rectangle* fadeoutRect = new Rectangle();

	bool fadeOut = false;

public:
	MainMenu(std::string name = "MainMenu");

	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;

	void onStartButtonClick();
	void onSettingsButtonClick();
	void onAboutButtonClick();
	void onQuitButtonClick();
};