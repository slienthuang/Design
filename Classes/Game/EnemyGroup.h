#pragma once

#include "cocos2d.h"
USING_NS_CC;

struct EnemyGroupCount{
	int tankCount;
	int panzerCount;
};

class EnemyBase;

class EnemyGroup
{
public:
	EnemyGroup();
	~EnemyGroup();

	static EnemyGroup* create(EnemyGroupCount* group, std::vector<Vec2> routeInfo);
	bool init(EnemyGroupCount* group, std::vector<Vec2> routeInfo);
	//void addEnemyUpdate(float dt);

private:
//	unsigned int m_currentCount;
	int m_tankNum;
	int m_panzerNum;
};




