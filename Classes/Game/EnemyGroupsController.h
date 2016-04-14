//#pragma once
//
//#include "cocos2d.h"
//USING_NS_CC;
//
//class EnemyBase;
//
//class EnemyGroupsController:public Node
//{
//public:
//	EnemyGroupsController();
//	~EnemyGroupsController();
//
//	//static EnemyGroupsController* create(int tankNum, int panzerNum, std::vector<Vec2> routeInfo,Layer* layer);
//	//bool init(int tankNum, int panzerNum, std::vector<Vec2> routeInfo,Layer* layer);
//
//	static EnemyGroupsController* create(int groups[][2], std::vector<Vec2> routeInfo, Layer* layer);
//	bool init(int groups[][2], std::vector<Vec2> routeInfo, Layer* layer);
//
//	void initAGroupEnemys(int i);
//	void addEnemys();
//	void update(float dt);
//
//private:
//	Layer* m_layer;
//	Vector<Vector<EnemyBase*>> m_enemys;
//	unsigned int m_currentCount;
//	int m_allGroupCount;
//	int m_currentGroupCount;
//};
//
/////先读取2维数组
/////获取里面的信息