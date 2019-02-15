#include <fstream>
#include "Game.h"
using namespace std;

Game::Game()
{
	srand(unsigned(time(NULL)));				// 设定随机种子
	initgraph(WindowWidth, WindowHeight+80);	// 窗口生成
	InitGame();				// 游戏参数初始化
	settextcolor(WHITE);	// 字体颜色

	// 按钮初始化
	_Select = -1;	// 没有按钮按下
	IMAGE btnup;
	IMAGE btndown;

	// 加载各个按钮
	loadimage(&_checkimg, _T("./Picture/_Down.bmp"), 0, 0, true);
	loadimage(&btnup, _T("./Picture/Line.bmp"), 0, 0, true);
	loadimage(&btndown, _T("./Picture/_Line.bmp"), 0, 0, true);
	_LineBtn = new Button(0, WindowHeight, &btnup, &btndown, LINE);
	loadimage(&btnup, _T("./Picture/Laser.bmp"), 0, 0, true);
	loadimage(&btndown, _T("./Picture/_Laser.bmp"), 0, 0, true);
	_LaserBtn = new Button(80, WindowHeight, &btnup, &btndown, LASER);
	loadimage(&btnup,_T("./Picture/Rocket.bmp"),0,0,true);
	loadimage(&btndown,_T("./Picture/_Rocket.bmp"),0,0,true);
	_RocketBtn = new Button(160,WindowHeight,&btnup,&btndown,ROCKET);
	loadimage(&btnup,_T("./Picture/Elec.bmp"),0,0,true);
	loadimage(&btndown,_T("./Picture/_Elec.bmp"),0,0,true);
	_ElecBtn = new Button(240,WindowHeight,&btnup,&btndown,ELEC);
	loadimage(&btnup,_T("./Picture/Start.bmp"),0,0,true);
	loadimage(&btndown,_T("./Picture/_Start.bmp"),0,0,true);
	_startRoundBtn = new Button(320, WindowHeight, &btnup, &btndown, LASER);
	loadimage(&btnup,_T("./Picture/Show.bmp"),0,0,true);
	loadimage(&btndown,_T("./Picture/_Show.bmp"),0,0,true);
	_ShowBtn = new Button(400,WindowHeight,&btnup,&btndown,LASER);

	// 其他的初始化
	initMap();	// 地图格子初始化
	draw();		// 第一次绘制
	
}


Game::~Game()
{
	// 清除动态列表空间
	_baseList.clear();
	for(int i=0;i<_mobList.size();i++)
		delete _mobList[i];
	_mobList.clear();
	for(int i=0;i<_towerList.size();i++)
		delete _towerList[i];
	_towerList.clear();

	// 清除地图格子空间
	for(int i=0;i<_map.size();i++){
		for(int j=0;j<_map[i].size();j++)
			delete _map[i][j];
		_map[i].clear();
	}
	_map.clear();

	// 清除按钮空间
	delete _LaserBtn;
	delete _LineBtn;
	delete _RocketBtn;
	delete _ElecBtn;
	delete _startRoundBtn;
	delete _ShowBtn;

	// 关闭窗口
	closegraph();
}

void Game::run(){
	// 游戏未结束时每帧运行一次
	while (!_GameOver){

		// 1.刷怪
		if(_inRound && _roundNum > _roundMaxNum)
		{
			_inRound = false;	// 本波次结束
			if (_wave < 10){ _roundMaxNum += 46; }	// 强度上升
			if (_wave > 20){ Mob::_MobHpMultiplier *= 1.05; }	// 血量额外上升
			Mob::_MobHpMultiplier *= 1.08;		// 血量上升
			if (_wave < 24){
				_module = 18 - _wave / 3;		// 出怪间隔修正（求模值）
			}
			_wave++;		// 预备下一波
		}
		if(_inRound)		// 在波次内
		{
			if (_roundNum%_module == 0){	// 求模成功
				int i = rand() % _baseList.size();	// 随机生成一个怪物
				addMob(_baseList[i].column*GRIDSIZE + GRIDSIZE / 2, _baseList[i].row*GRIDSIZE + GRIDSIZE / 2, randMobType(), i);
			}
			_roundNum ++;	// 波次计数器前进
		}

		// 2.所有mob移动
		for (int i = 0; i < _mobList.size(); i++){
			_mobList[i]->Move();
		}

		// 3.所有tower尝试攻击，提供给其整个怪物列表
		for (int i = 0; i < _towerList.size(); i++){
			_towerList[i]->Attack(_mobList);
		}

		// 4.检测鼠标事件队列
		while (MouseHit()){
			_msg = GetMouseMsg();
			if (_msg.uMsg == WM_LBUTTONDOWN || _msg.uMsg == WM_LBUTTONUP){
				// 各按钮检测是否有效按下
				// 以下为造塔按钮
				if (_LaserBtn->MouseResponse(_msg)){
					if (_Select == 1){_Select = -1;}else{_Select = 1;}
				}
				if (_LineBtn->MouseResponse(_msg)){
					if (_Select == 2){ _Select = -1; }else{ _Select = 2; }
				}
				if(_RocketBtn->MouseResponse(_msg))
				{
					if(_Select == 3){_Select = -1;}else{_Select =3;}
				}
				if(_ElecBtn->MouseResponse(_msg))
				{
					if(_Select == 4){_Select = -1;}else{_Select =4;}
				}
				if(_startRoundBtn->MouseResponse(_msg))	// 开始下一波次
				{
					if(_inRound == false&&_mobList.empty())	// 检查该波次是否结束
					{
						_money += 200;	// 初始奖励赠送
						setRoute();		// 配置怪物行进路线
						_inRound = true;
						_roundNum = 0;	// 计数器清空
					}
					else
						MessageBox(GetForegroundWindow(),L"本波次还未结束！",L"警告",MB_OK);
				}
				if (_ShowBtn->MouseResponse(_msg))
					_showDis = !_showDis;	// 切换是否显示惩罚值的状态
			}
			
			// 造塔进程
			if (_Select != -1 && _msg.y < WindowHeight)
			{
				if (_msg.uMsg == WM_LBUTTONDOWN)	// 左键按下
				{
					int buildrow = _msg.y / GRIDSIZE;
					int buildcolumn = _msg.x / GRIDSIZE;
					if (_canbuild[buildrow][buildcolumn]){	// 此处可以造塔
						switch (_Select)	// 根据不同造塔类型进行塔的生成
						{
						case 1:
							if (_money>=LaserPrice)
							{ 
								addTower(buildrow, buildcolumn, LASER); 
								_canbuild[buildrow][buildcolumn] = false; 
								_money -= LaserPrice; 
							}
							else
								MessageBox(GetForegroundWindow(),L"你穷得叮当响，买不起！",L"警告",MB_OK);
							break; 
						case 2:
							if (_money >= LinePrice)
							{ 
								addTower(buildrow, buildcolumn, LINE);
								_canbuild[buildrow][buildcolumn] = false; 
								_money -= LinePrice; 
							}
							else
								MessageBox(GetForegroundWindow(),L"你穷得叮当响，买不起！",L"警告",MB_OK);
							break;
						case 3:
							if(_money >= RocketPrice){
								addTower(buildrow, buildcolumn, ROCKET); 
								_canbuild[buildrow][buildcolumn] = false; 
								_money -= RocketPrice; 
							}
							else
								MessageBox(GetForegroundWindow(),L"你穷得叮当响，买不起！",L"警告",MB_OK);
							break;
						case 4:
							if(_money >= ElecPrice){ 
								addTower(buildrow, buildcolumn, ELEC); 
								_canbuild[buildrow][buildcolumn] = false; 
								_money -= ElecPrice; 
							}
							else
								MessageBox(GetForegroundWindow(),L"你穷得叮当响，买不起！",L"警告",MB_OK);
							break;
						default:
							break;
						}
						_Select = -1;	// 按钮复原
					}
				}
			}
		}

		// 5.检测Mob死亡，Mob到终点，移除Mob，记得移除所有指向Mob的Bullet
		for (int i = 0; i < _mobList.size();){
			//是否需要移除
			if (_mobList[i]->IsDead() || MobHome(_mobList[i])){
				//到家扣血
				if (MobHome(_mobList[i])){
					_health--;	// 啊！！！
				}
				else{
					_money += _mobList[i]->_dropmoney;	// 奖励掉落
					int irow = _mobList[i]->_row;
					int icol = _mobList[i]->_column;
					_map[irow][icol]->_distance+=rand()%51+50;	// 在死亡处附加随机的惩罚值
				}
				delete _mobList[i];		
				_mobList.erase(_mobList.begin() + i);	// 从列表中移出
			}
			else
				i++;	// 下一个
		}

		// 6.全部绘制
		BeginBatchDraw();
		cleardevice();
		draw();
		EndBatchDraw();

		// 7.检测是否结束游戏
		if (_health < 0){
			_GameOver = true;
		}

		// 8.停顿一下
		Sleep(FrameSleepDur);
	}
}

void Game::InitGame()
{
	//初始化各种参数
	_health = HomeHealth;
	_money = StartMoney;

	//释放vector内存
	for (int i = 0; i < _mobList.size(); i++){
		delete _mobList[i];
	}
	_mobList.clear();

	for (int i = 0; i < _towerList.size(); i++){
		delete _towerList[i];
	}
	_towerList.clear();

	//初始化地图
	_endRow = 0;
	_endColumn = 0;
	_GameOver=false;
	_addclock=0;

	// 初始化波次
	_round = 0;
	for(int i=0;i<100;i++)
	{
		_roundtime[i]=500*i;
		_roundmode[i]=50;
	}
	_wave = 0;
	_inRound = false;
	_roundNum = 0;
	_roundMaxNum = 240;
	_module = 18;

	// 不显示距离惩罚值
	_showDis = false;
}


bool Game::IsBlocked(GRID gtype, bool flying)
{
	switch (gtype)
	{
	case EMPTY:
		return false;
	case WALL:
		return true;
	case WATER:
		if(flying)
			return false;
		else
			return true;
	case MUD:
		return false;
	case IRON:
		return true;
	}
	return false;
}




bool Game::MobHome(Mob* mob)
{
	if (mob->_row == _endRow && mob->_column == _endColumn)return true;
	return false;
}

void Game::draw()
{
	drawMap();

	// 画刷怪
	for (int i = 0; i<_baseList.size(); i++)
	{
		setlinecolor(RGB(240, 0, 0));
		for (int j = 0; j < GRIDSIZE / 2; j += 2){
			rectangle(
				_baseList[i].column*GRIDSIZE + j, 
				_baseList[i].row*GRIDSIZE + j, 
				_baseList[i].column*GRIDSIZE + GRIDSIZE - j, 
				_baseList[i].row*GRIDSIZE + GRIDSIZE - j
				);
		}
	}

	for (int i = 0; i<_mobList.size(); i++)
		_mobList[i]->Draw();
	for (int i = 0; i<_towerList.size(); i++)
		_towerList[i]->Draw();

	// 画按钮
	_LaserBtn->Draw();
	_LineBtn->Draw();
	_RocketBtn->Draw();
	_ElecBtn->Draw();
	_ShowBtn->Draw();
	_startRoundBtn->Draw();
	
	// 画家的
	setlinecolor(RGB(0, 240, 0));
	for (int i = 0; i < GRIDSIZE / 2; i += 2){
		rectangle(
			_endColumn*GRIDSIZE + i, 
			_endRow*GRIDSIZE + i, 
			_endColumn*GRIDSIZE + GRIDSIZE - i, 
			_endRow*GRIDSIZE + GRIDSIZE - i
			);
	}
	
	// 显示钱数
	settextstyle(TextHeight,0,_T("Calibri"));
	setbkmode(OPAQUE);

	TCHAR ms[100] = _T("Money: ");
	TCHAR moneystr[100];
	_itot(_money, moneystr, 10);
	_tcscat(ms, moneystr);
	_tcscat(ms, _T("          "));
	outtextxy(500, 300, ms);

	TCHAR hp[100] = _T("Life: ");
	TCHAR hpstr[100];
	_itot(_health, hpstr, 10);
	_tcscat(hp, hpstr);
	_tcscat(hp, _T("      "));
	outtextxy(500, 330, hp);

	TCHAR wv[100] = _T("Wave: ");
	TCHAR wvstr[100];
	_itot(_wave, wvstr, 10);
	_tcscat(wv, wvstr);
	_tcscat(wv, _T("      "));
	outtextxy(500, 360, wv);

    // 显示按下
	switch (_Select)
	{
	case -1:
		break; 
	case 1:
		putimage(80, 300, &_checkimg); 
		break; 
	case 2:
		putimage(0, 300, &_checkimg); 
		break; 
	case 3:
		putimage(160, 300, &_checkimg); 
		break;
	case 4:
		putimage(240, 300, &_checkimg); 
		break;
	}
}

void Game::drawMap()
{
	setlinecolor(WHITE);
	settextcolor(WHITE);
	settextstyle(GRIDSIZE/2,0,L"Consolas");
	setbkcolor(TRANSPARENT);
	for(int i=0;i<WindowHeight/GRIDSIZE;i++)
		for(int j=0;j<WindowWidth/GRIDSIZE;j++){
			_map[i][j]->Draw();
			if(_showDis){
				TCHAR tmp[10];
				_itot(_map[i][j]->_distance, tmp, 10);
				setbkmode(OPAQUE);
				outtextxy(_map[i][j]->_column*GRIDSIZE,_map[i][j]->_row*GRIDSIZE,tmp);
			}
		}

}



void Game::initMap()
{
		// 分配空间，动态分配内存
		_baseList.clear();
		vector<Grid*> v_grid;
		Grid *p_grid;
		for(int i=0;i<WindowHeight/GRIDSIZE;i++)
		{
			v_grid.clear();
			for(int j=0;j<WindowWidth/GRIDSIZE;j++)
			{
				p_grid = new Grid;
				v_grid.push_back(p_grid);
			}
			_map.push_back(v_grid);
		}

		// 地图格子初始化时没有设置行列，在此设置一下
		for(int i=0;i< _map.size();i++)
			for(int j=0;j<_map[i].size();j++)
			{
				_map[i][j]->_row=i;
				_map[i][j]->_column=j;
			}

		// 出生点和家的设置
		_baseList.clear();
		_endRow = WindowHeight/GRIDSIZE-1;
		_endColumn = WindowWidth/GRIDSIZE-1;
		BASEPOINT home_1 = {0,0};
		BASEPOINT home_2 = {WindowHeight/GRIDSIZE-1,0};
		_baseList.push_back(home_1);
		_baseList.push_back(home_2);

		// 随机生成地图直至其是联通的
		do 
		{
			randomMap();
			_map[_endRow][_endColumn]->_type=EMPTY;
			_map[0][0]->_type=EMPTY;
			_map[WindowHeight/GRIDSIZE-1][0]->_type=EMPTY;
		} while (!findPath(_baseList[0],_route)||!findPath(_baseList[1],_route));
		setRoute(); // 配置路线
}


void Game::addTower(int row,int col,TOWERTYPE type)
{
	Tower* tower_tmp;
	switch(type)
	{
	case LASER:
		tower_tmp=new LaserTower(row,col);
		break;
	case LINE:
		tower_tmp=new LineTower(row,col);
		break;
	case ROCKET:
		tower_tmp=new Rocket(row,col);
		break;
	case ELEC:
		tower_tmp = new Elec(row,col);
		break;
	}
	_towerList.push_back(tower_tmp);
}

void Game::addMob(int x,int y,MOBTYPE type,int order)
{
	Mob* mob_tmp;
	Healer* heal_tmp;
	switch(type)
	{
	case ZOMBIE:
		mob_tmp=new Zombie(x,y);
		break;
	case BEE:
		mob_tmp=new Bee(x,y);
		break;
	case GIANT:
		mob_tmp=new Giant(x,y);
		break;
	case GIANTBEE:
		mob_tmp=new GiantBee(x,y);
		break;
	case RUNNER:
		mob_tmp=new Runner(x,y);
		break;
	}
	// 依据其飞行特性分配不同的路线
	if (mob_tmp->_isflying){ mob_tmp->_route = _flybaserouteList[order]; }
	else{ mob_tmp->_route = _baserouteList[order]; }
	_mobList.push_back(mob_tmp);
}

MOBTYPE Game::randMobType()
{
	// 怪物随机生成
	int tmp=rand()%10;
	switch(tmp)
	{
	case 0:
	case 1:
	case 2:
		return ZOMBIE;
	case 3:
	case 4:
	case 5:
		return BEE;
	case 6:
		return GIANT;
	case 7:
		return GIANTBEE;
	case 8:
	case 9:
		return RUNNER;
	}
}

bool Game::isInArea(BASEPOINT point)
{
	return point.column>=0&&
		point.row>=0&&
		point.row<WindowHeight/GRIDSIZE&&
		point.column<WindowWidth/GRIDSIZE;
}

bool Game::findPath(BASEPOINT source,vector<BASEPOINT> &route,bool isflying)
{
	route.clear();
	vector<Grid*> open,close;
	Grid* begin=_map[source.row][source.column];
	Grid* end=_map[_endRow][_endColumn];

	// 1. 把起始格添加到开启列表
	open.push_back(begin);
	Grid* p_tmp;

	// 2. 重复如下的工作：
	while(!open.empty())
	{

		// a) 寻找开启列表中F值最低的格子, 称它为当前格
		vec_sort(open);
		Grid* current=open.back();


		// b) 把它切换到关闭列表
		open.pop_back();
		close.push_back(current);
		p_tmp=current;

		BASEPOINT check[4]=
		{
			{p_tmp->_row-1,p_tmp->_column},
			{p_tmp->_row+1,p_tmp->_column},
			{p_tmp->_row,p_tmp->_column-1},
			{p_tmp->_row,p_tmp->_column+1}
		};

		random_shuffle(check,check+4);

		// c) 对相邻的4格中的每一个:
		for(int i=0;i<4;i++)
		{
			// 如果它不可通过或者已经在关闭列表中，略过它
			if(isInArea(check[i])
				&&!IsBlocked(_map[check[i].row][check[i].column]->_type,isflying)
				&&std::find(close.begin(),close.end(),_map[check[i].row][check[i].column])==close.end())
			{
				// 反之如下
				Grid* g_tmp = _map[check[i].row][check[i].column];

				// 如果它不在开启列表中
				if(std::find(open.begin(),open.end(),g_tmp)==open.end()){
					g_tmp->_father=current;	// 把它添加进去
					if (_map[check[i].row][check[i].column]->_type == MUD)
					{ g_tmp->G = current->G + g_tmp->_distance + 300; }
					else{ g_tmp->G = current->G + g_tmp->_distance; }
					g_tmp->H=abs(g_tmp->_row-_endRow)+abs(g_tmp->_column-_endColumn);
					g_tmp->F=g_tmp->G+g_tmp->H;
					open.push_back(g_tmp);						// 记录这一格的F,G,和H值
				}

				// 如果它已经在开启列表中
				// 用G值为参考检查新的路径是否更好
				// 更低的G值意味着更好的路径
				else if(g_tmp->G>current->G+g_tmp->_distance)	// 如果是这样
				{
					g_tmp->_father=current;	// 就把这一格的父节点改成当前格
					g_tmp->G=current->G+g_tmp->_distance;
					g_tmp->F=g_tmp->G+g_tmp->H;		// 并且重新计算这一格的G和F值
				}

			}
		}

		//  d) 停止，当你把目标格添加进了开启列表，这时候路径被找到
		if(find(open.begin(),open.end(),end)!=open.end())
		{
			Grid* g_tmp=end;
			do{
				BASEPOINT tmp={g_tmp->_row,g_tmp->_column};
				route.push_back(tmp);
				g_tmp=g_tmp->_father;
			}while(g_tmp!=begin);
			BASEPOINT tmp={g_tmp->_row,g_tmp->_column};
			route.push_back(tmp);
			open.clear();
			close.clear();
			return true;
		}
	}
	// 没有找到目标格，开启列表已经空了
	// 这时候，路径不存在
	open.clear();
	close.clear();
	return false;
}

bool Game::findFlyPath(BASEPOINT source, vector<BASEPOINT> &route, bool isflying)
{
	route.clear();
	vector<Grid*> open, close;
	Grid* begin = _map[source.row][source.column];
	Grid* end = _map[_endRow][_endColumn];

	// 1. 把起始格添加到开启列表
	open.push_back(begin);
	Grid* p_tmp;

	// 2. 重复如下的工作：
	while (!open.empty())
	{

		// a) 寻找开启列表中F值最低的格子, 称它为当前格
		vec_sort(open);
		Grid* current = open.back();


		// b) 把它切换到关闭列表
		open.pop_back();
		close.push_back(current);
		p_tmp = current;

		BASEPOINT check[4] =
		{
			{ p_tmp->_row - 1, p_tmp->_column },
			{ p_tmp->_row + 1, p_tmp->_column },
			{ p_tmp->_row, p_tmp->_column - 1 },
			{ p_tmp->_row, p_tmp->_column + 1 }
		};

		random_shuffle(check, check + 4);

		// c) 对相邻的4格中的每一个:
		for (int i = 0; i<4; i++)
		{
			// 如果它不可通过或者已经在关闭列表中，略过它
			if (isInArea(check[i])
				&& !IsBlocked(_map[check[i].row][check[i].column]->_type, isflying)
				&& std::find(close.begin(), close.end(), _map[check[i].row][check[i].column]) == close.end())
			{
				// 反之如下
				Grid* g_tmp = _map[check[i].row][check[i].column];

				// 如果它不在开启列表中
				if (std::find(open.begin(), open.end(), g_tmp) == open.end()){
					g_tmp->_father = current;	// 把它添加进去
					g_tmp->G = current->G + g_tmp->_distance;
					g_tmp->H = abs(g_tmp->_row - _endRow) + abs(g_tmp->_column - _endColumn);
					g_tmp->F = g_tmp->G + g_tmp->H;
					open.push_back(g_tmp);						// 记录这一格的F,G,和H值
				}

				// 如果它已经在开启列表中
				// 用G值为参考检查新的路径是否更好
				// 更低的G值意味着更好的路径
				else if (g_tmp->G>current->G + g_tmp->_distance)	// 如果是这样
				{
					g_tmp->_father = current;	// 就把这一格的父节点改成当前格
					g_tmp->G = current->G + g_tmp->_distance;
					g_tmp->F = g_tmp->G + g_tmp->H;		// 并且重新计算这一格的G和F值
				}

			}
		}

		//  d) 停止，当你把目标格添加进了开启列表，这时候路径被找到
		if (find(open.begin(), open.end(), end) != open.end())
		{
			Grid* g_tmp = end;
			do{
				BASEPOINT tmp = { g_tmp->_row, g_tmp->_column };
				route.push_back(tmp);
				g_tmp = g_tmp->_father;
			} while (g_tmp != begin);
			BASEPOINT tmp = { g_tmp->_row, g_tmp->_column };
			route.push_back(tmp);
			open.clear();
			close.clear();
			return true;
		}
	}
	// 没有找到目标格，开启列表已经空了
	// 这时候，路径不存在
	open.clear();
	close.clear();
	return false;
}

void Game::vec_sort(vector<Grid*> &vec)
{
	for(int i=0;i<vec.size();i++)
		for(int j=0;j<i;j++)
			if(vec[i]->F>vec[j]->F)
			{
				Grid* g_tmp=vec[i];
				vec[i]=vec[j];
				vec[j]=g_tmp;
			}
}


void Game::setRoute()
{
	for(int i=0;i<_baseList.size();i++)
		findPath(_baseList[i],_baserouteList[i]);
	for (int i = 0; i<_baseList.size(); i++)
		findFlyPath(_baseList[i], _flybaserouteList[i]);
}
void Game::randomMap()
{
	for(int i=0;i<WindowHeight / GRIDSIZE;i++)
		for(int j=0;j<WindowWidth / GRIDSIZE;j++)
		{
			int tmp = rand() % 8;
			switch(tmp)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				_map[i][j]->_type = EMPTY;
				break;
			case 4:
				_map[i][j]->_type = WALL;
				break;
			case 5:
				_map[i][j]->_type = IRON;
				break;
			case 6:
				_map[i][j]->_type = WATER;
				break;
			case 7:
				_map[i][j]->_type = MUD;
				break;
			}
		}

	for (int i = 0; i < WindowHeight / GRIDSIZE; i++){
		for (int j = 0; j < WindowWidth / GRIDSIZE; j++){
			if (_map[i][j]->_type == WALL)
				_canbuild[i][j] = true;
			else 
				_canbuild[i][j] = false; 
			}
	}
	
}