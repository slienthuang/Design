#pragma once

#include "cocos2d.h"
USING_NS_CC;

class EnemyBase;
class EnemyManager
{
public:
	static EnemyManager* getInstance();
	void addEnemy(EnemyBase* enemy);
	void removeEnemy(EnemyBase* enemy);
	void clearEnemys();
	void pauseEnemys();
	void resumeEnemys();

	Vector<EnemyBase*> getEnemysVector() const;

private:
	EnemyManager();
	virtual ~EnemyManager();
	static EnemyManager* s_instance;


	Vector<EnemyBase*> m_enemys;

};