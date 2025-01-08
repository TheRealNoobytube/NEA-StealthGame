#include "AboutMenu.h"

AboutMenu::AboutMenu( std::string name) : Node2D(name){
	addChild(&aboutText);
	aboutText.setTextWrapLength(300);
	aboutText.setFontSize(12);
	aboutText.scale = Vector2D(0.7, 0.7);

	aboutText.text = "This game was created for my Year 13 A-Level NEA." 
	"\n The goal is to go through the levels as stealthily as possible, picking up any items along the way to beat"
	"\n                                      the final boss."

	"\n\n                                          Controls:"
	"\n                                       W: Move Up"
	"\n                                       A: Move Left"
	"\n                                     S: Move Down"
	"\n                                      D: Move Right"
	"\n                                 Space: Pick Up Item"
	"\n                Left Mouse Button: Use Weapon/Punch";

	addChild(&backButton);
}



void AboutMenu::ready() {
	__super::ready();
	Vector2D viewportSize = getSceneTree()->getViewportSize();

	//centers all the ui elements
	aboutText.position.x = (viewportSize.x / 2) - ((aboutText.getTextSize().x / 2) * aboutText.scale.x);
	aboutText.position.y = 2;

	backButton.position.x = (viewportSize.x / 2) - (backButton.getSize().x / 2);
	backButton.position.y = viewportSize.y - 30;

	aboutText.color = Color(20, 220, 255);

	backButton.on_click.connect([this]() { this->onBackButtonClick(); });
	
}

void AboutMenu::onBackButtonClick() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}


void AboutMenu::update(float delta) {
	__super::update(delta);
}

