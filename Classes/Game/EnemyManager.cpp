#include "EnemyManager.h"
#include "EnemyBase.h"


EnemyManager* EnemyManager::s_instance = new EnemyManager();

EnemyManager* EnemyManager::getInstance()
{
	return s_instance;
}


EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::addEnemy(EnemyBase* enemy)
{
	m_enemys.pushBack(enemy);
}

void EnemyManager::removeEnemy(EnemyBase* enemy)
{
	m_enemys.eraseObject(enemy);
}

void EnemyManager::clearEnemys()
{
	m_enemys.clear();
}

Vector<EnemyBase*> EnemyManager::getEnemysVector() const
{
	return m_enemys;
}

void EnemyManager::pauseEnemys()
{
	for (auto enemy : m_enemys)
	{
		enemy->pause();
	}
}

void EnemyManager::resumeEnemys()
{
	for (auto enemy : m_enemys)
	{
		enemy->resume();
	}
}