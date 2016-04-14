#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TowerBase;
class TowerManager
{
public:
	static TowerManager* getInstance();
	void addTower(TowerBase* enemy);
	void removeTower(TowerBase* enemy);
	void clearTowers();
	void pauseTowers();
	void resumeTowers();

	Vector<TowerBase*> getTowersVector() const;

private:
	TowerManager();
	virtual ~TowerManager();
	static TowerManager* s_instance;

	Vector<TowerBase*> m_towers;

};