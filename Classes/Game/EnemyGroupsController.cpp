//#include "EnemyGroupsController.h"
//#include "EnemyBase.h"
//#include "EnemyManager.h"
//
//
//EnemyGroupsController::EnemyGroupsController():
//m_layer(NULL),
//m_currentCount(-1),
//m_allGroupCount(0),
//m_currentGroupCount(0)
//{
//}
//
//EnemyGroupsController::~EnemyGroupsController()
//{
//}
//
//
////EnemyGroupsController* EnemyGroupsController::create(int tankNum, int panzerNum, std::vector<Vec2> routeInfo, Layer* layer)
////{
////	auto EnemyGroupsController = new EnemyGroupsController();
////	EnemyGroupsController->init(tankNum, panzerNum, routeInfo,layer);
////	EnemyGroupsController->autorelease();
////	return EnemyGroupsController;
////}
//
////bool EnemyGroupsController::init(int tankNum, int panzerNum, std::vector<Vec2> routeInfo, Layer* layer)
////{
////	if (!Node::init()) return false;
////
////	m_tankNum = tankNum;
////	m_panzerNum = panzerNum;
////	m_layer = layer;
////
////	for (int i = 0; i < m_tankNum; i++)
////	{
////		auto tank = EnemyBase::create(EnemyType::Tank,routeInfo);
////		m_enemys.push_back(tank);
////		EnemyManager::getInstance()->addEnemy(tank);
////	}
////
////	for (int j = 0; j < m_panzerNum; j++)
////	{
////		auto panzer = EnemyBase::create(EnemyType::Panzer, routeInfo);
////		m_enemys.push_back(panzer);
////		EnemyManager::getInstance()->addEnemy(panzer);
////	}
////	addEnemys();
////	return true;
////}
//
//EnemyGroupsController* create(int groups[][2], std::vector<Vec2> routeInfo, Layer* layer)
//{
//		auto enemyGroupsController = new EnemyGroupsController();
//		enemyGroupsController->init(groups, routeInfo, layer);
//		enemyGroupsController->autorelease();
//		return enemyGroupsController;
//}
//
//bool EnemyGroupsController::init(int groups[][2], std::vector<Vec2> routeInfo, Layer* layer)
//{
//	if (!Node::init()) return false;
//	m_allGroupCount = sizeof(groups) / (sizeof(int)*2);
//
//	for (int i = 0; i < m_allGroupCount; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//
//		}
//	}
//
//	return true;
//}
//
//void EnemyGroupsController::addEnemys()
//{
//  
//}
//
////void EnemyGroupsController::addEnemy()
////{
////	m_layer->addChild(m_enemys[m_currentCount]);
////}
//
//void EnemyGroupsController::update(float dt)
//{
//
//}