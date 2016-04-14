#include "SelectTowerPanel.h"
#include "my_cocostudio.h"

SelectTowerPanel::SelectTowerPanel():
m_rootNode(NULL)
{
}

SelectTowerPanel::~SelectTowerPanel()
{
}

SelectTowerPanel* SelectTowerPanel::create()
{
	auto dialog = new SelectTowerPanel();
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool SelectTowerPanel::init()
{
	if (!Node::init())  return false;
	m_rootNode = CSLoader::createNode("SelectTowerPanel.csb");
	this->addChild(m_rootNode);

	//m_selectPanel = static_cast<Sprite*>(m_rootNode->getChildByName("selectFrame"));
	m_devilfish = static_cast<Sprite*>(m_rootNode->getChildByName("devilfish"));
	m_whale = static_cast<Sprite*>(m_rootNode->getChildByName("whale"));
	m_dragon = static_cast<Sprite*>(m_rootNode->getChildByName("dragon"));
	m_eel = static_cast<Sprite*>(m_rootNode->getChildByName("eel"));
	return true;
}  


TowerType SelectTowerPanel::getSelectedType(Vec2 pos)
{
	//Vec2 _pos = m_selectPanel->convertToNodeSpace(t->getLocation());
	if (m_devilfish->getBoundingBox().containsPoint(pos))
	{
		return TowerType::devilfish;

	}
	else if (m_whale->getBoundingBox().containsPoint(pos))
	{
		return TowerType::whale;

	}
	else if (m_dragon->getBoundingBox().containsPoint(pos))
	{
		return TowerType::dragon;
	
	}
	else if (m_eel->getBoundingBox().containsPoint(pos))
	{
		return TowerType::eel;
	}
	return TowerType::none;
}

//Sprite* SelectTowerPanel::getSelectPanel()
//{
//	return m_selectPanel;
//}