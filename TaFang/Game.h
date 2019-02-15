#pragma once
#include <graphics.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <tchar.h>
#include <string.h>
#include "DrawAid.h"

#include "AllObjects.h"
#include "Grid.h"

using namespace std;

#define WindowWidth 600//960
#define WindowHeight 300//480
#define FrameSleepDur 5
#define HomeHealth 20
#define TextHeight 20
#define LaserPrice 300
#define LinePrice 100
#define RocketPrice 800
#define ElecPrice 800
#define StartMoney 1800

class Game
{
protected:
	bool _GameOver;	// 游戏结束状态

	vector<vector<Grid*>> _map;			// 地图格子
	vector<Mob*> _mobList;						// 怪物列表
	vector<Tower*> _towerList;					// 塔的列表
	vector<BASEPOINT> _baseList;				// 怪物生成点列表
	vector<BASEPOINT> _baserouteList[10];		// 与之对应的怪物路线列表
	vector<BASEPOINT> _flybaserouteList[10];	// 与之对应的飞行怪物路线列表

	int _money,_health;			// 钱和血
	MOUSEMSG _msg;				// 鼠标消息
	int _endRow, _endColumn;	// 家的行列

	long _addclock;				// 计时器
	int _round;					// 波次计数器
	int _roundtime[100];		// 波次持续时间数组
	int _roundmode[100];		// 波次求模值数组
	int _wave;					// 波次数
	int _roundMaxNum;			// 每波次的最大怪物数
	int _roundNum;				// 该波次已生成怪物数
	int _module;				// 求模值
	bool _inRound;				// 该波次是否在继续

	vector<BASEPOINT> _route;	// 临时储存路线

	TOWERTYPE _buildtype;		// 造塔类型
	bool _isbuying;				// 是否在造塔
	bool _showDis;				// 是否显示距离惩罚值

	int _Select;		// 储存按钮状态
	bool _canbuild[WindowHeight / GRIDSIZE][WindowWidth / GRIDSIZE];			// 储存是否可造塔
	IMAGE _checkimg;	// 按钮被按下的图片
	Button *_LaserBtn,*_LineBtn,*_RocketBtn,*_ElecBtn,*_startRoundBtn,*_ShowBtn;		// 按钮

public:
	Game();
	void run();										// 外部接口，游戏正常运行
	~Game();
	
protected:
	void TowerAttack(Tower* tower, Mob* mob);		// 攻击
	void CauseRemoveBulletEffect(Bullet* bullet);	// 触发子弹
	bool MobHome(Mob* mob);							// 返回一个mob是否到家
	void setRoute();
	MOBTYPE randMobType();							// 随机生成怪物类型
	bool isInArea(BASEPOINT point);					// 判断是否在界内
	void vec_sort(vector<Grid*> &vec);				// A*算法中的排序
	bool findPath(BASEPOINT,vector<BASEPOINT> &route,bool isflying=false);		// 陆地生物找路
	bool findFlyPath(BASEPOINT, vector<BASEPOINT> &route, bool isflying=true);	// 飞行生物找路
	void draw();									// 绘制所有的Object
	void drawMap();									// 绘制地图
	void initMap();									// 地图初始化
	void randomMap();								// 生成随机地图
	void addMob(int x,int y, MOBTYPE type,int order);							// 生成怪物
	void addTower(int row, int col, TOWERTYPE type);// 造塔
	void InitGame();								// 地图初始化
	bool IsBlocked(GRID gtype, bool flying);		// 判断是否可通过
};