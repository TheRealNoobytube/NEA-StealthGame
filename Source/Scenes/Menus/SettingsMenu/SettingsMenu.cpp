#include "SettingsMenu.h"
#include "Source/UI/Slider/Slider.h"


SettingsMenu::SettingsMenu(std::string name) : Node2D(name){
	addChild(settingsText);
	addChild(musicSlider);
	addChild(musicSliderText);
	addChild(soundSlider);
	addChild(soundSliderText);
	addChild(backButton);
}

void SettingsMenu::ready() {
	__super::ready();
	Vector2D viewportSize = getSceneTree()->getViewportSize();

	settingsText->setFontSize(40);
	settingsText->scale = Vector2D(0.5, 0.5);
	settingsText->position.x = (viewportSize.x / 2) - (settingsText->getTextSize().x / 2) * settingsText->scale.x;

	musicSliderText->setFontSize(28);
	musicSliderText->scale = Vector2D(0.5, 0.5);
	musicSliderText->position.x = (viewportSize.x / 2) - (musicSliderText->getTextSize().x / 2) * musicSliderText->scale.x;
	musicSliderText->position.y = 35;

	musicSlider->setSize(Vector2D(120, 10));
	musicSlider->position.x = (viewportSize.x / 2) - (musicSlider->getSize().x / 2);
	musicSlider->position.y = 53;

	soundSliderText->setFontSize(28);
	soundSliderText->scale = Vector2D(0.5, 0.5);
	soundSliderText->position.x = (viewportSize.x / 2) - (soundSliderText->getTextSize().x / 2) * soundSliderText->scale.x;
	soundSliderText->position.y = 75;

	soundSlider->setSize(Vector2D(120, 10));
	soundSlider->position.x = (viewportSize.x / 2) - (soundSlider->getSize().x / 2);
	soundSlider->position.y = 93;

	backButton->position.x = (viewportSize.x / 2) - (backButton->getSize().x / 2);
	backButton->position.y = viewportSize.y - 30;
	backButton->on_click.connect([this]() { this->onBackButtonClick(); });
}


void SettingsMenu::update(float delta) {
	__super::update(delta);
}

void SettingsMenu::onBackButtonClick() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}