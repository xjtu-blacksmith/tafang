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
	bool _GameOver;	// ��Ϸ����״̬

	vector<vector<Grid*>> _map;			// ��ͼ����
	vector<Mob*> _mobList;						// �����б�
	vector<Tower*> _towerList;					// �����б�
	vector<BASEPOINT> _baseList;				// �������ɵ��б�
	vector<BASEPOINT> _baserouteList[10];		// ��֮��Ӧ�Ĺ���·���б�
	vector<BASEPOINT> _flybaserouteList[10];	// ��֮��Ӧ�ķ��й���·���б�

	int _money,_health;			// Ǯ��Ѫ
	MOUSEMSG _msg;				// �����Ϣ
	int _endRow, _endColumn;	// �ҵ�����

	long _addclock;				// ��ʱ��
	int _round;					// ���μ�����
	int _roundtime[100];		// ���γ���ʱ������
	int _roundmode[100];		// ������ģֵ����
	int _wave;					// ������
	int _roundMaxNum;			// ÿ���ε���������
	int _roundNum;				// �ò��������ɹ�����
	int _module;				// ��ģֵ
	bool _inRound;				// �ò����Ƿ��ڼ���

	vector<BASEPOINT> _route;	// ��ʱ����·��

	TOWERTYPE _buildtype;		// ��������
	bool _isbuying;				// �Ƿ�������
	bool _showDis;				// �Ƿ���ʾ����ͷ�ֵ

	int _Select;		// ���水ť״̬
	bool _canbuild[WindowHeight / GRIDSIZE][WindowWidth / GRIDSIZE];			// �����Ƿ������
	IMAGE _checkimg;	// ��ť�����µ�ͼƬ
	Button *_LaserBtn,*_LineBtn,*_RocketBtn,*_ElecBtn,*_startRoundBtn,*_ShowBtn;		// ��ť

public:
	Game();
	void run();										// �ⲿ�ӿڣ���Ϸ��������
	~Game();
	
protected:
	void TowerAttack(Tower* tower, Mob* mob);		// ����
	void CauseRemoveBulletEffect(Bullet* bullet);	// �����ӵ�
	bool MobHome(Mob* mob);							// ����һ��mob�Ƿ񵽼�
	void setRoute();
	MOBTYPE randMobType();							// ������ɹ�������
	bool isInArea(BASEPOINT point);					// �ж��Ƿ��ڽ���
	void vec_sort(vector<Grid*> &vec);				// A*�㷨�е�����
	bool findPath(BASEPOINT,vector<BASEPOINT> &route,bool isflying=false);		// ½��������·
	bool findFlyPath(BASEPOINT, vector<BASEPOINT> &route, bool isflying=true);	// ����������·
	void draw();									// �������е�Object
	void drawMap();									// ���Ƶ�ͼ
	void initMap();									// ��ͼ��ʼ��
	void randomMap();								// ���������ͼ
	void addMob(int x,int y, MOBTYPE type,int order);							// ���ɹ���
	void addTower(int row, int col, TOWERTYPE type);// ����
	void InitGame();								// ��ͼ��ʼ��
	bool IsBlocked(GRID gtype, bool flying);		// �ж��Ƿ��ͨ��
};