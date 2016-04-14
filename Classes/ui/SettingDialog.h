#pragma once

#include "cocos2d.h"
USING_NS_CC;

class SettingDialog:public Node
{
public:
	static SettingDialog* create();
	bool init();	
};