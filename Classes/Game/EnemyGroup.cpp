#include "EnemyGroup.h"
#include "EnemyBase.h"
#include "EnemyManager.h"


EnemyGroup::EnemyGroup():
//m_currentCount(-1),
m_tankNum(0),
m_panzerNum(0)
{
}

EnemyGroup::~EnemyGroup()
{
}


EnemyGroup* EnemyGroup::create(EnemyGroupCount* group, std::vector<Vec2> routeInfo)
{
	auto enemyGroup = new EnemyGroup();
	enemyGroup->init(group, routeInfo);
	return enemyGroup;
}

bool EnemyGroup::init(EnemyGroupCount* group, std::vector<Vec2> routeInfo)
{
	m_tankNum = group->tankCount;
	m_panzerNum = group->panzerCount;

	auto enemyManager = EnemyManager::getInstance();
	for (int i = 0; i < m_tankNum; i++)
	{
		auto tank = EnemyBase::create(EnemyType::Tank,routeInfo);
		enemyManager->addEnemy(tank);
	}

	for (int j = 0; j < m_panzerNum; j++)
	{
		auto panzer = EnemyBase::create(EnemyType::Panzer, routeInfo);
		enemyManager ->addEnemy(panzer);
	}

	//schedule(schedule_selector(EnemyGroup::addEnemyUpdate),2.0f);
	return true;
}

//void EnemyGroup::addEnemyUpdate(float dt)
//{
//
//		m_currentCount++;
//		if (m_currentCount < m_enemyManager->getEnemysVector().size())
//		{
//			m_layer->addChild(m_enemyManager->getEnemysVector().at(m_currentCount));
//		}
//}

