#include "ReliefButton.h"

ReliefButton* ReliefButton::create(Node* targetNode)
{
	auto reliefButton = new ReliefButton();
	reliefButton->init(targetNode);
	reliefButton->autorelease();
	return reliefButton;
}

bool ReliefButton::init(Node* targetNode)
{
	if (!Node::init())  return false;
	m_targetNode = targetNode;
	m_targetNode->addChild(this);
	this->setName(m_targetNode->getName());


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ReliefButton::onTouchedBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ReliefButton::onTouchedMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ReliefButton::onTouchedEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,m_targetNode);

	return true;
}

bool ReliefButton::onTouchedBegan(Touch* t, Event* e)
{
	auto pos = m_targetNode->getParent()->convertTouchToNodeSpace(t);
	if (m_targetNode->getBoundingBox().containsPoint(pos))
	{

		m_targetNode->runAction(ScaleTo::create(0.2f,0.5f));
		return true;
	}
	return false;
}

void ReliefButton::onTouchedMoved(Touch* t, Event* e)
{

}

void ReliefButton::onTouchedEnded(Touch* t, Event* e)
{
	m_targetNode->runAction(ScaleTo::create(0.2f, 1.0f));
	if (m_clickCallback)
		m_clickCallback();
}