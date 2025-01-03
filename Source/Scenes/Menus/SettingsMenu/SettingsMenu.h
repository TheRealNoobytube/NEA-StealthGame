#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Slider/Slider.h"

class SettingsMenu : public Node2D {
private:
	Label settingsText = Label("Settings");

	Label musicSliderText = Label("Music");
	Slider musicSlider;

	Label soundSliderText = Label("SFX");
	Slider soundSlider;

	Button backButton = Button("Back");

public:
	Node* lastScene;

	SettingsMenu(std::string name = "Settings Menu");

	void ready() override;
	void update(float delta) override;

	void onBackButtonClick();
};