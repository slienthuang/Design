#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "constants.h"
class EnemyBase;

class TowerBase:public Node
{
	CC_SYNTHESIZE(TowerType,m_towerType,TowerType);
	CC_SYNTHESIZE(Sprite*,m_towerSprite,TowerSprite);
public:
	TowerBase();
	~TowerBase();

	static TowerBase* create(TowerType towerType);
	bool init(TowerType towerType);
	bool isInRange(EnemyBase* enemy);
	void shootTarget();
	void shootUpdate(float dt);

	void upgrade();

	EnemyBase* m_shootTarget;
private:
	float m_shootRange;
	int m_level;
	Sprite* m_levelCrown;
};