#pragma once

#include "cocos2d.h"

USING_NS_CC;

class EnemyBase;
class Bullet:public Node
{
	CC_SYNTHESIZE(int,m_power,Power);
public:
	Bullet();
	~Bullet();
	static Bullet* create(EnemyBase* targetEnemy);
	bool init(EnemyBase* targetEnemy);
	void update(float dt);
	void explode();

	EnemyBase* m_targetEnemy;
private:
	Sprite* m_bulletSprite;
	int m_speed;
};
