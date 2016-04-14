#pragma once

#include "cocos2d.h"
USING_NS_CC;

class ReliefButton:public Node
{
	CC_SYNTHESIZE(std::function<void()>,m_clickCallback,ClickCallback);
public:
	static ReliefButton* create(Node* targetNode);
	bool init(Node* targetNode);

	bool onTouchedBegan(Touch* t,Event* e);
	void onTouchedMoved(Touch* t, Event* e);
	void onTouchedEnded(Touch* t, Event* e);

private:
	Node* m_targetNode;
};