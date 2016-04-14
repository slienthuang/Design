#include "UpgradeTowerPanel.h"
#include "my_cocostudio.h"

UpgradeTowerPanel* UpgradeTowerPanel::create()
{
	auto dialog = new UpgradeTowerPanel();
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool UpgradeTowerPanel::init()
{
	if (!Node::init()) return false;

	m_rootNode = CSLoader::createNode("UpgradeTowerPanel.csb");
	addChild(m_rootNode);


	m_upgradeIcon = static_cast<Sprite*>(m_rootNode->getChildByName("upgrade"));
	m_sellIcon = static_cast<Sprite*>(m_rootNode->getChildByName("sell"));

	return true;
}

OperateType UpgradeTowerPanel::getOperateType(Vec2 pos)
{
	if (m_upgradeIcon->getBoundingBox().containsPoint(pos))
	{
		return OperateType::Upgrade;
	}
	else if (m_sellIcon->getBoundingBox().containsPoint(pos))
	{
		return OperateType::Sell;
	}
	return OperateType::None;
}


void UpgradeTowerPanel::setTargetTower(TowerBase* tower)
{
	m_targetTower = tower;
}

void UpgradeTowerPanel::updateTagetTowerState()
{

}