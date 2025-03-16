#include "AboutMenu.h"

AboutMenu::AboutMenu( std::string name) : Node2D(name){
	addChild(aboutText);
	aboutText->setTextWrapLength(600);
	aboutText->setFontSize(24);
	aboutText->scale = Vector2D(0.28, 0.28);

	aboutText->text = "This game was created for my Year 13 A-Level NEA."
		"\n The goal is to go through the levels as stealthily as possible, picking up any items along the way to beat"
		"\n                                      the final boss.\n"
		"BTW: there actually is no final boss and there is only one level. go mess around and do whatever"

		"\n\n                                          Controls:"
		"\n                            W or Up Arrow: Move Up"
		"\n                           A or Left Arrow: Move Left"
		"\n                         S or Down Arrow: Move Down"
		"\n                         D or Right Arrow: Move Right"
		"\n                                    Space: Use Item"
		"\n               Left Mouse Button or X: Shoot Weapon"
		"\n                            Shift Button: Switch Item"
		"\n                         Ctrl Button: Switch Weapon";

	addChild(backButton);

	addChild(balls);
}



void AboutMenu::ready() {
	__super::ready();
	Vector2D viewportSize = getSceneTree()->getViewportSize();

	//centers all the ui elements
	aboutText->position.x = (viewportSize.x / 2) - ((aboutText->getTextSize().x / 2) * aboutText->scale.x);
	aboutText->position.y = 2;
	aboutText->color = Color(20, 220, 255);

	backButton->position.x = (viewportSize.x / 2) - (backButton->getSize().x / 2);
	backButton->position.y = viewportSize.y - 26;

	backButton->on_click.connect([this]() { this->onBackButtonClick(); });

	balls->setTexture(getSceneTree()->getBasePath() + "../Assets/myballs.png");
	balls->setHFrames(11);
	balls->scale = Vector2D(0.15, 0.15);
	balls->createAnimation("balls", { 0, 1, 2, 3, 4, 5 ,6 , 7, 8 ,9, 10 }, 12, false, false, true);
	balls->play("balls");
	balls->position = Vector2D(25, 100);
	
	
}

void AboutMenu::onBackButtonClick() {
	queueFree();
	getSceneTree()->changeScene(lastScene);
}


void AboutMenu::update(float delta) {
	__super::update(delta);
}

