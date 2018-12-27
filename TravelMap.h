#ifndef TRAVELMAP_H_
#define TRAVELMAP_H
#include<iostream>
#include<queue>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

enum { time_prio = 0, money_prio = 1 };

struct Time
{
	int hour;
	int minutes;
	bool operator==(Time & a) { return hour == a.hour&&minutes == a.minutes; }
	bool operator<(Time & a) { return hour < a.hour || (hour == a.hour&&minutes < a.minutes); }
	bool operator>(Time & a){ return hour > a.hour || (hour == a.hour&&minutes > a.minutes); }
};

class TravelMap;

class City;

class Road
{
	friend class City;
	friend class TravelMap;
private:
	int ter_num;			//表示相连结点的序号
	Time start_time, arrive_time, duration;		//本车次的发车时间，到达时间，历经时间
	string number;			//车次序号
	double price;			//车票钱
	Road * next;
public:
	Road(int a,Time & b,Time & c,Time & d,string & e,double f, Road *g=nullptr)
		:ter_num(a), start_time(b), arrive_time(c), duration(d), number(e), price(f), next(g) {;}
};

class City
{
	friend class TravelMap;
private:
	string name;	//这里存储节点的真正信息
	Road * adj;			//这里存储节点的邻接表
public:
	City(string & a, Road * b = nullptr) :name(a), adj(b) { ; }
};

class TravelMap
{
private:
	
	vector<City>Citylist;
	bool Type;		//0代表铁路图，1代表航线图
	int CityPos(string & cityname);
public:
	TravelMap(string & departure, string & terminal, Time & start, bool travel_method);//要给出最早出发时间start
																				//和交通工具,0代表火车，1代表飞机
	~TravelMap();

	void AddCity(string & name);
	void DestroyCity(string & name);
	void AddRoad(string & start, string & end, string & num, Time & start_t, 
					Time & end_t, Time & dur, double cost);
	void DestroyRoad(string & start, string & end);	//从起点到终点断开所有路
	void DestroyRoad(string & start, string & end, string & num);//按照起点、终点、车次删除一条路
	void DestroyRoad(string & start, string & end, Time & t);//按照起点,终点，出发时间删除一条路
	
	void MainFunction(string & start, bool stratege);	//策略为0代表省时间，策略为1代表省钱,根据起点、终点和策略确定一条最短路

};
