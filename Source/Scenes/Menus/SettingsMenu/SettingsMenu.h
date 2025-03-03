#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Slider/Slider.h"

class SettingsMenu : public Node2D {
private:
	Label* settingsText = new Label("Settings");

	Label* musicSliderText = new Label("Music");
	Slider* musicSlider = new Slider();

	Label* soundSliderText = new Label("SFX");
	Slider* soundSlider = new Slider();

	Button* backButton = new Button("Back");

public:
	Node* lastScene;

	SettingsMenu(std::string name = "Settings Menu");

	void ready() override;
	void update(float delta) override;

	void onBackButtonClick();
};