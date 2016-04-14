#pragma once

enum class TowerType{
	none,
	devilfish,
	whale,
	dragon,
	eel,
};

enum class EnemyType{
	Tank,
	Panzer,
};


enum class OperateType
{
	Upgrade,
	Sell,
	None,
};


//struct


//int EnemyGroups[10][2] = {
//	{2,1},
//	{3,2},
//	{4,3},
//	{5,4},
//	{7,10},
//	{ 8, 12 },
//	{ 10, 1 },
//	{ 4, 2 },
//	{ 5, 1 },
//	{ 2, 2 }
//};


//int g_enemyGroups[2][2] = {
//	{ 2, 1 },
//	{ 3, 2 },
//};

struct TowerData
{
	float shootRange;
	float power;
	int fireRate;
	int price;
}a;

//struct TowerData a;
a.shootRange = 1.0f;


struct EnemyData
{

};