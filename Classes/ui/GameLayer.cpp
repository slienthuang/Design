#include "GameLayer.h"
#include "EnemyBase.h"
#include "EnemyGroup.h"
#include "SelectTowerPanel.h"
#include "TowerBase.h"
#include "Bullet.h"
#include "TowerManager.h"
#include "EnemyManager.h"
#include "MenuTopBar.h"
#include "UpgradeTowerPanel.h"

//#include "SettingDialog.h"
#include "DialogBase.h"



int a[3][2] = { { 1, 1 },
				{ 2, 2 },
				{ 3, 3 } };

GameLayer::GameLayer():
m_currentCount(-1),
m_enemyGroup(NULL),
m_currentGroupCount(0),
m_selectedTower(NULL),
m_upgradeTowerPanel(NULL)
{
}

GameLayer::~GameLayer()
{
	delete(m_enemyGroup);
	m_enemyGroup = NULL;
}

GameLayer* GameLayer::create()
{
	auto gameLayer = new GameLayer();
	gameLayer->init();
	gameLayer->autorelease();
	return gameLayer;
}

bool GameLayer::init()
{
	if (!Layer::init())
		return false;


	///背景图
	m_tiledMap = TMXTiledMap::create("summer_sea.tmx");
	addChild(m_tiledMap);


	//auto dialog = DialogBase::create("SettingDialog.csb");
	//addChild(dialog);
	//dialog->setPosition(900,600);


	initRoutes();
	initTowerPoints();

	m_enemyManager = EnemyManager::getInstance();

	m_selectTowerPanel = SelectTowerPanel::create();
	addChild(m_selectTowerPanel,100);
	m_selectTowerPanel->setPosition(g_originalPoint);

	m_upgradeTowerPanel = UpgradeTowerPanel::create();
	addChild(m_upgradeTowerPanel, 10);
	m_upgradeTowerPanel->setPosition(g_originalPoint);


	//保存敌人组的数目
	for (int i = 0; i < 3; i++)
	{
		auto enemyGroupCount = new EnemyGroupCount();
		enemyGroupCount->tankCount = a[i][0];
		enemyGroupCount->panzerCount = a[i][1];
		m_enemyGroupCounts.push_back(enemyGroupCount);
	}

	auto enemyGroup = EnemyGroup::create(m_enemyGroupCounts.at(m_currentGroupCount), m_routePoints);
	log("batchs:%d", m_currentGroupCount);

	m_menuTopBar = MenuTopBar::create();
	this->addChild(m_menuTopBar);
	m_menuTopBar->setPosition(Vec2(0, 1200));
	m_menuTopBar->updateBarData(m_currentGroupCount+1,3);
	m_menuTopBar->setPauseCallback([this](){
		if (UserDefault::getInstance()->getBoolForKey("game_run"))
		{
			UserDefault::getInstance()->setBoolForKey("game_run", false);
			this->unschedule(schedule_selector(GameLayer::addEnemyUpdate));
			EnemyManager::getInstance()->pauseEnemys();
			TowerManager::getInstance()->pauseTowers();
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("game_run", true);
			this->schedule(schedule_selector(GameLayer::addEnemyUpdate),2.0f);
			EnemyManager::getInstance()->resumeEnemys();
			TowerManager::getInstance()->resumeTowers();
		}
		m_menuTopBar->updatePauseButton();
	});


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(GameLayer::onSelectTowerPanelTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(GameLayer::onSelectTowerPanelTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(GameLayer::onSelectTowerPanelTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_selectTowerPanel);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);
	listener2->onTouchBegan = CC_CALLBACK_2(GameLayer::onUpgradeTowerPanelTouchBegan, this);
	listener2->onTouchMoved = CC_CALLBACK_2(GameLayer::onUpgradeTowerPanelTouchMoved, this);
	listener2->onTouchEnded = CC_CALLBACK_2(GameLayer::onUpgradeTowerPanelTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, m_upgradeTowerPanel);
	schedule(schedule_selector(GameLayer::addEnemyUpdate), 2.0f);
	return true;
}

void GameLayer::initRoutes()
{
	TMXObjectGroup* path = m_tiledMap->getObjectGroup("path1");
	ValueVector routePoints = path->getObjects();
	for (auto point : routePoints)
	{
		auto pointInfo = point.asValueMap();
		float x = pointInfo["x"].asFloat();
		float y = pointInfo["y"].asFloat();
		m_routePoints.push_back(Vec2(x,y));
		log("route:%f,%f", x, y);
	}
}

void GameLayer::initTowerPoints()
{
	TMXObjectGroup* towers = m_tiledMap->getObjectGroup("tower");
	ValueVector towerPoints = towers->getObjects();
	for (auto point : towerPoints)
	{
		auto pointInfo = point.asValueMap();
		float x = pointInfo["x"].asFloat();
		float y = pointInfo["y"].asFloat();
		m_towerPoints.push_back(Vec2(x, y));
		log("%f,%f", x, y);
	}
}


bool GameLayer::onTouchBegan(Touch* t, Event* e)
{
	
	Vec2 _touchPos = t->getLocation();

	
	for (auto pos : m_towerPoints)
	{
		if (!isTouchTower(_touchPos))
		{
			m_upgradeTowerPanel->setPosition(g_originalPoint);
			if (abs(pos.x - _touchPos.x) < 50 && abs(pos.y - _touchPos.y) < 50)
			{
				m_selectTowerPanel->setPosition(pos);
				return true;
			}
		}
		else{
			m_selectTowerPanel->setPosition(g_originalPoint);
			m_upgradeTowerPanel->setPosition(m_selectedTower->getPosition());
		}
	}
	return false;
}

void GameLayer::onTouchMoved(Touch* t, Event* e)
{
}

void GameLayer::onTouchEnded(Touch* t, Event* e)
{

}



bool GameLayer::onSelectTowerPanelTouchBegan(Touch* t, Event* e)
{
	Vec2 pos = m_selectTowerPanel->convertTouchToNodeSpace(t);
	auto type = m_selectTowerPanel->getSelectedType(pos);
	if (type != TowerType::none)
	{
		auto tower = TowerBase::create(type);
		TowerManager::getInstance()->addTower(tower);
		addChild(tower);
		tower->setPosition(m_selectTowerPanel->getPosition());
		m_selectTowerPanel->setPosition(g_originalPoint);
		return true;
	}
	return false;
}

void GameLayer::onSelectTowerPanelTouchMoved(Touch* t, Event* e)
{

}

void GameLayer::onSelectTowerPanelTouchEnded(Touch* t, Event* e)
{
}

bool GameLayer::onUpgradeTowerPanelTouchBegan(Touch* t, Event* e)
{   
	Vec2 pos = m_upgradeTowerPanel->convertTouchToNodeSpace(t);
	auto type = m_upgradeTowerPanel->getOperateType(pos);
	if (type == OperateType::Upgrade)
	{
		m_selectedTower->upgrade();
		m_upgradeTowerPanel->setPosition(g_originalPoint);
		return true;
	}
	if (type == OperateType::Sell)
	{
		TowerManager::getInstance()->removeTower(m_selectedTower);
		m_selectedTower->removeFromParent();
		m_upgradeTowerPanel->setPosition(g_originalPoint);
		return true;
	}
	return false;
}

void GameLayer::onUpgradeTowerPanelTouchMoved(Touch* t, Event* e)
{

}

void GameLayer::onUpgradeTowerPanelTouchEnded(Touch* t, Event* e)
{

}

void GameLayer::addEnemyUpdate(float dt)
{

	m_currentCount++;
	if (m_currentCount < m_enemyManager->getEnemysVector().size())
	{
		this->addChild(m_enemyManager->getEnemysVector().at(m_currentCount),10);
	}
	else
	{
		if (m_enemyManager->getEnemysVector().size()==0)
		{
			nextGroup();
		}
	}

	m_menuTopBar->updateBarData(m_currentGroupCount+1,3);
}


void GameLayer::nextGroup()
{
	delete(m_enemyGroup);
	m_enemyGroup = NULL;
	m_currentCount = -1;
	m_currentGroupCount++;
	if (m_currentGroupCount < m_enemyGroupCounts.size())
	{
		log("batchs:%d",m_currentGroupCount);
		m_enemyGroup = EnemyGroup::create(m_enemyGroupCounts.at(m_currentGroupCount), m_routePoints);
	}
}


bool GameLayer::isTouchTower(Vec2 pos)
{
	bool _touch = false;
	auto towers = TowerManager::getInstance()->getTowersVector();
	for (auto tower : towers)
	{
		auto sp = tower->getTowerSprite();
		auto _pos = sp->getParent()->convertToNodeSpace(pos);
		if (tower->getTowerSprite()->getBoundingBox().containsPoint(_pos))
		{
			m_selectedTower = tower;
			_touch = true;
		}
	}
	return _touch;
}