#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "my_cocostudio.h"

class ReliefButton;
class MenuTopBar:public Node
{
public:
	static MenuTopBar* create();
	bool init();
	void updateBarData(int x,int y);
	void setPauseCallback(std::function<void()> callback);
	void updatePauseButton();
private:
	Node* m_rootNode;
	Sprite* m_pauseSprite;
	ui::Text* m_groupRecordText;
	ReliefButton* m_pauseButton;

	ReliefButton* m_menuButton;
};