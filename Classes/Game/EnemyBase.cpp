#include "EnemyBase.h"
#include "Explosion.h"
#include "EnemyManager.h"
#include "Bullet.h"

EnemyBase::EnemyBase() :
m_pointCount(0),
m_nextPoint(Vec2(0, 0)),
m_currentPoint(Vec2(0, 0)),
m_moveSpeed(50.0f),
m_isArriveEnd(false)
{
}

EnemyBase::~EnemyBase()
{
}

EnemyBase* EnemyBase::create(EnemyType type, std::vector<Vec2> routeInfo)
{
	auto enemyBase = new EnemyBase();
	enemyBase->init(type,routeInfo);
	enemyBase->autorelease();
	return enemyBase;
}

bool EnemyBase::init(EnemyType type, std::vector<Vec2> routeInfo)
{
	if (!Node::init()) return false;

	switch (type)
	{
	case EnemyType::Tank:
		m_sp = Sprite::create("tank.png");
		break;
	case EnemyType::Panzer:
		m_sp = Sprite::create("panzer.png");
		break;
	}
	addChild(m_sp);

	auto liveBgBar = Sprite::create("liveBarBg.png");
	addChild(liveBgBar);
	liveBgBar->setPosition(-40,m_sp->getContentSize().height/2+20);
	liveBgBar->setScale(0.5);
	//liveBar->setPosition();

	m_liveBar = LoadingBar::create("liveBar.png");
	addChild(m_liveBar);
	m_liveBar->setScale(0.5);
	m_liveBar->setPosition(liveBgBar->getPosition());
	m_liveBar->setPercent(100);

	m_routeInfo = routeInfo;
	this->runRoute();


	return true;
}


void EnemyBase::goNextPoint()
{
	m_currentPoint = m_routeInfo[m_pointCount];
	this->setPosition(m_currentPoint);
	m_pointCount++;
	if (m_pointCount < m_routeInfo.size())
	{
		m_nextPoint = m_routeInfo[m_pointCount];
	}
	else
	{
		m_isArriveEnd = true;
	}

}



void EnemyBase::runRoute()
{
	goNextPoint();
	if (!m_isArriveEnd)
	{
		this->runAction(Sequence::create(MoveTo::create(getStepTime(), m_nextPoint), CallFuncN::create(CC_CALLBACK_0(EnemyBase::runRoute, this)), NULL));
	}
	else
	{
		EnemyManager::getInstance()->removeEnemy(this);
		this->removeFromParent();
	}
}

float EnemyBase::getStepTime()
{
	float _distance = abs(m_nextPoint.x - m_currentPoint.x) + abs(m_nextPoint.y-m_currentPoint.y);
	return _distance / m_moveSpeed;
}


void  EnemyBase::getAttacked(int damageNum)
{
	int nowLive = m_liveBar->getPercent() - damageNum;
	if (nowLive>0)  m_liveBar->setPercent(nowLive);
	else
	{
		m_liveBar->setPercent(0);
		this->explode();
	}
}

void EnemyBase::explode()
{
	log("%d", EnemyManager::getInstance()->getEnemysVector().size());
	auto explosion = Explosion::create(2);
	this->getParent()->addChild(explosion);
	explosion->setPosition(this->getPosition());
	explosion->setExplodeStartCallback([this, explosion](){
		for (auto bullet : m_shootBullets)
		{
			bullet->removeFromParent();
		}
		EnemyManager::getInstance()->removeEnemy(this);
		log("enemy:%d", EnemyManager::getInstance()->getEnemysVector().size());
		this->removeFromParent();
	});
	explosion->setExplodeEndCallback([explosion](){
		explosion->removeFromParent();
	});
}

int EnemyBase::getLive()
{
	return m_liveBar->getPercent();
}


void EnemyBase::getShootBullet(Bullet* bullet)
{
	m_shootBullets.pushBack(bullet);
}



