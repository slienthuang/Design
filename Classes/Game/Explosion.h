#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Explosion:public Node
{
	CC_SYNTHESIZE(std::function<void()>, m_explodeStartCallback, ExplodeStartCallback);
	CC_SYNTHESIZE(std::function<void()>, m_explodeEndCallback, ExplodeEndCallback);

public:
	static Explosion* create(int type);
	bool init(int type);
};
