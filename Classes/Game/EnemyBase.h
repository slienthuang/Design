#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;
#include "constants.h"

class Bullet;

class EnemyBase:public Node
{

public:
	EnemyBase();
	~EnemyBase();

	static EnemyBase* create(EnemyType type,std::vector<Vec2> routeInfo);
	bool init(EnemyType type, std::vector<Vec2> routeInfo);


	void goNextPoint();
	void runRoute();
	float getStepTime();
	void  getAttacked(int damageNum);
	void explode();
	int getLive();
	void getShootBullet(Bullet* bullet);

	Vector<Bullet*> m_shootBullets;
private:
	Sprite* m_sp;
	std::vector<Vec2> m_routeInfo;
	Vec2 m_nextPoint;
	Vec2 m_currentPoint;
	int m_pointCount;
	float m_moveSpeed;
	LoadingBar* m_liveBar;
	bool m_isArriveEnd;
	
};