#pragma once

#include "cocos2d.h"
#include "constants.h"
USING_NS_CC;

class TowerBase;
class UpgradeTowerPanel:public Node
{
public:
	static UpgradeTowerPanel* create();
	bool init();
	OperateType getOperateType(Vec2 pos);
	void setTargetTower(TowerBase* tower);
	void updateTagetTowerState();

private:
	Node* m_rootNode;
	OperateType m_operateType;
	Sprite* m_upgradeIcon;
	Sprite* m_sellIcon;
	TowerBase* m_targetTower;
};