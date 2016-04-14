#pragma once 

#include "cocos2d.h"
USING_NS_CC;
#include "constants.h"


class SelectTowerPanel:public Node
{
public:

	SelectTowerPanel();
	~SelectTowerPanel();
	static SelectTowerPanel* create();
	bool init();
	TowerType getSelectedType(Vec2 pos);
	Sprite* getSelectPanel();

private:
	Node* m_rootNode;
	//Sprite* m_selectPanel;
	Sprite* m_devilfish;
	Sprite* m_whale;
	Sprite* m_dragon;
	Sprite* m_eel;
};