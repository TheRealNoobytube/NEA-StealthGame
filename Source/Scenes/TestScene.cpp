#include "TestScene.h"

TestScene::TestScene(std::string name) : Node2D(name){
	addChild(&body);
	addChild(&player);
	body.addChild(&shape);
	body.position = Vector2D(40, 40);
}