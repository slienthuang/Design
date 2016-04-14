#pragma once

#include "cocos2d.h"
USING_NS_CC;


const Vec2 g_originalPoint = Vec2(-500, -500);
class SelectTowerPanel;
struct EnemyGroupCount;
class EnemyManager;
class EnemyGroup;
class MenuTopBar;
class TowerBase;
class UpgradeTowerPanel;

class GameLayer :public Layer
{
public:
	GameLayer();
	~GameLayer();

	static GameLayer* create();
	bool init();
	void initRoutes();
	void initTowerPoints();
	bool onTouchBegan(Touch* t,Event* e);
	void onTouchMoved(Touch* t,Event* e);
	void onTouchEnded(Touch* t,Event* e);
	bool onSelectTowerPanelTouchBegan(Touch* t, Event* e);
	void onSelectTowerPanelTouchMoved(Touch* t, Event* e);
	void onSelectTowerPanelTouchEnded(Touch* t, Event* e);


	bool onUpgradeTowerPanelTouchBegan(Touch* t, Event* e);
	void onUpgradeTowerPanelTouchMoved(Touch* t, Event* e);
	void onUpgradeTowerPanelTouchEnded(Touch* t, Event* e);

	void nextGroup();
	void addEnemyUpdate(float dt);

	bool isTouchTower(Vec2 pos);

private:
	TMXTiledMap* m_tiledMap;
	Sprite* m_tank;
	std::vector<Vec2> m_routePoints;
	std::vector<Vec2> m_towerPoints;
	SelectTowerPanel* m_selectTowerPanel;
	std::vector<EnemyGroupCount*> m_enemyGroupCounts;
	unsigned int m_currentCount;  //当前波走了第几个
	int m_currentGroupCount; //波数
	EnemyManager* m_enemyManager;
	EnemyGroup* m_enemyGroup;
	MenuTopBar* m_menuTopBar;
	TowerBase* m_selectedTower;
	UpgradeTowerPanel* m_upgradeTowerPanel;
};