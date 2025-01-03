#include "TestScene.h"

TestScene::TestScene(std::string name) : Node2D(name){
	addChild(&player);
}