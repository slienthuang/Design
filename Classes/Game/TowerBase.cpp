#include "TowerBase.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "EnemyManager.h"

TowerBase::TowerBase():
m_towerSprite(0),
m_shootRange(0),
m_level(1),
m_levelCrown(NULL)
{
}

TowerBase::~TowerBase()
{
}

TowerBase* TowerBase::create(TowerType towerType)
{
	auto tower = new TowerBase();
	tower->init(towerType);
	tower->autorelease();
	return tower;
}

bool TowerBase::init(TowerType towerType)
{
	if (!Node::init())  return false;

	m_shootRange = 250.0f;
	m_shootTarget = NULL;
	setTowerType(towerType);
	switch (m_towerType)
	{
	case TowerType::devilfish:
		m_towerSprite = Sprite::create("devilfish.png");
		break;
	case TowerType::whale:
		m_towerSprite = Sprite::create("whale.png");
		break;
	case TowerType::dragon:
		m_towerSprite = Sprite::create("dragon.png");
		break;
	case TowerType::eel:
		m_towerSprite = Sprite::create("eel.png");
		break;
	}
	addChild(m_towerSprite);

    //this->setContentSize(m_towerSprite->getContentSize());
	//this->setContentSize();

	schedule(schedule_selector(TowerBase::shootUpdate),0.3f);
	return true;
}

bool TowerBase::isInRange(EnemyBase* enemy)
{
		Vec2 towerPos = this->getPosition();
		Vec2 enemyPos = enemy->getPosition();
		Vec2 deltaVec2 = towerPos - enemyPos;
		if ((deltaVec2.x*deltaVec2.x + deltaVec2.y*deltaVec2.y) < m_shootRange*m_shootRange)
		{
			return true;
		}
	return false;
}

void TowerBase::shootTarget()
{
	auto bullet = Bullet::create(m_shootTarget);
	m_shootTarget->getShootBullet(bullet);
	this->getParent()->addChild(bullet);
	bullet->setPosition(this->getPosition());
}

void TowerBase::shootUpdate(float dt)
{
	auto enemys = EnemyManager::getInstance()->getEnemysVector();
	m_shootTarget = NULL;
	for (auto enemy : enemys)
	{
		if (isInRange(enemy))
		{
			m_shootTarget = enemy;
			break;
		}
	}
	if (m_shootTarget)   shootTarget();
}

void TowerBase::upgrade()
{
	m_level++;
	
	if (!m_levelCrown)
	{
		m_levelCrown = Sprite::create("crown2.png");
		addChild(m_levelCrown);
		m_levelCrown->setPositionY(45);
	}
	if (m_level == 2)
	{
		m_levelCrown->initWithFile("crown2.png");
	}
	if (m_level == 3)
	{
		m_levelCrown->initWithFile("crown3.png");
	}
}
