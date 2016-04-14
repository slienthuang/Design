#include "Explosion.h"

Explosion* Explosion::create(int type)
{
	auto explosion = new Explosion();
	explosion->init(type);
	explosion->autorelease();
	return explosion;
}

bool Explosion::init(int type)
{

	if (!Node::init())  return false;

	//setExplosionCallback([this](){
	//	this->removeFromParent();
	//});

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("wsparticle.plist");
	auto animation = Animation::create();
	Sprite* sp;
	switch (type)
	{
	case 1:
		sp = Sprite::createWithSpriteFrameName("a_001.png");
		for (int i=1;i<= 4;i++)
		{
			__String* fileName = __String::createWithFormat("a_00%d.png",i);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		break;
	case 2:
		sp = Sprite::createWithSpriteFrameName("b_001.png");
		for (int i = 1; i <= 8; i++)
		{
			__String* fileName = __String::createWithFormat("b_00%d.png", i);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		break;
	case 3:
		sp = Sprite::createWithSpriteFrameName("c_001.png");
		for (int i = 1; i <= 8; i++)
		{
			__String* fileName = __String::createWithFormat("c_00%d.png", i);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		break;
	case 4:
		sp = Sprite::createWithSpriteFrameName("d_00001.png");
		for (int i = 1; i <= 9; i++)
		{
			__String* fileName = __String::createWithFormat("d_000%d.png", i);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		break;
	}
	this->addChild(sp);
	animation->setDelayPerUnit(0.15f);

	auto action = Animate::create(animation);

	sp->runAction(Sequence::create(CallFunc::create([this, sp](){
									if (m_explodeStartCallback)
										m_explodeStartCallback();
									}), action, 
								   CallFunc::create([this, sp](){
									if (m_explodeEndCallback)
										m_explodeEndCallback();
								    }), NULL));
		return true;
}