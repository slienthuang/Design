#include "TowerManager.h"
#include "TowerBase.h"

TowerManager* TowerManager::s_instance = new TowerManager();

TowerManager* TowerManager::getInstance()
{
	return s_instance;
}

TowerManager::TowerManager()
{
}

TowerManager::~TowerManager()
{
}

void TowerManager::addTower(TowerBase* tower)
{
	m_towers.pushBack(tower);
}

void TowerManager::removeTower(TowerBase* tower)
{
	m_towers.eraseObject(tower);
}

void TowerManager::clearTowers()
{
	m_towers.clear();
}

Vector<TowerBase*> TowerManager::getTowersVector() const
{
	return m_towers;
}

void TowerManager::pauseTowers()
{
	for (auto tower : m_towers)
	{
		tower->pause();
	}
}

void TowerManager::resumeTowers()
{
	for (auto tower : m_towers)
	{
		tower->resume();
	}
}