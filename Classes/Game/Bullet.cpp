#include "Bullet.h"
#include "Explosion.h"
#include "EnemyBase.h"
#include "Explosion.h"


Bullet::Bullet():
m_speed(10),
m_power(10)
{
}

Bullet::~Bullet()
{
}

Bullet* Bullet::create(EnemyBase* targetEnemy)
{
	auto bullet = new Bullet();
	bullet->init(targetEnemy);
	bullet->autorelease();
	return bullet;
}

bool Bullet::init(EnemyBase* targetEnemy)
{
	if (!Node::init())  return false;
	m_targetEnemy = targetEnemy;

	m_bulletSprite = Sprite::create("bullet.png");
	addChild(m_bulletSprite);
	scheduleUpdate();
	return true;
}

void Bullet::update(float dt)
{
		Vec2 currentPos = this->getPosition();
		Vec2 targetPos = m_targetEnemy->getPosition();
		float deltaA = targetPos.x - currentPos.x;
		float deltaB = targetPos.y - currentPos.y;

		if (abs(deltaA) < 10 && abs(deltaB < 10))
		{
			this->explode();
			unscheduleUpdate();
		}
		else{
			float deltaC = sqrt(deltaA*deltaA + deltaB*deltaB);
			Vec2 deltaVec2 = Vec2(deltaA / deltaC*m_speed, deltaB / deltaC*m_speed);
			this->setPosition(currentPos + deltaVec2);
		}
	
}

void Bullet::explode()
{
	 auto explosion = Explosion::create(1);
	 m_targetEnemy->addChild(explosion);
	 explosion->setExplodeStartCallback([this, explosion](){
		m_targetEnemy->getAttacked(m_power);
		m_targetEnemy->m_shootBullets.eraseObject(this);
		this->removeFromParent();
	});
	 explosion->setExplodeEndCallback([this, explosion](){
		explosion->removeFromParent();
	});
}
