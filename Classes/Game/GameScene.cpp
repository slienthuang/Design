#include "GameScene.h"
#include "GameLayer.h"

GameScene* GameScene::create()
{
	auto scene = new GameScene();
	scene->init();
	scene->autorelease();
	return scene;
}


bool GameScene::init()
{
	if (!Scene::init())   return false;
	auto layer = GameLayer::create();
	addChild(layer);
	return true;
}