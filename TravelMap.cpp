#include "TravelMap.h"

int TravelMap::CityPos(string & cityname)
{
	for (int i = 0; i < Citylist.size(); ++i)
		if (Citylist[i].name == cityname)	return i;
	return -1;
}

TravelMap::TravelMap(string & departure, string & terminal, Time & start, bool travel_method)
{
	ifstream fin;
	if (travel_method)
		fin.open("flightnext.txt");
	else
		fin.open("railnet.txt");
	string temp;
	getline(fin, temp);			//读掉第一行表头

	string number_t, dep_t, ter_t;
	int hour_t, minute_t, hour_tt, minute_tt, hour_ttt, minute_ttt;
	double price_t;
	Time start_t, stop_t, duration_t;
	while (fin.good())
	{
		if (!(fin >> number_t))
			break;
		fin >> dep_t;
		fin >> hour_t;	fin.get();	fin >> minute_t;
		start_t.hour = hour_t; start_t.minutes = minute_t;
		if (start_t > start_t)
		{
			getline(fin, temp);
			continue;
		}
		fin >> ter_t;
		fin >> hour_tt;	fin.get();	fin >> minute_tt;
		fin >> hour_ttt;	fin.get();	fin >> hour_ttt;
		fin >> price_t;
		stop_t.hour = hour_tt; stop_t.minutes = minute_tt;
		duration_t.hour = hour_ttt; duration_t.minutes = minute_ttt;

		if (CityPos(dep_t) == -1)
			AddCity(dep_t);
		if (CityPos(ter_t) == -1)
			AddCity(ter_t);
		AddRoad(dep_t, ter_t, number_t, start_t, stop_t, duration_t, price_t);
		fin.get();
	}
}

TravelMap::~TravelMap()
{
	Road * p;
	for (int i = 0; i < Citylist.size(); ++i)
	{
		p = Citylist[i].adj;
		while (p)
		{
			Citylist[i].adj = p->next;
			delete p;
			p = Citylist[i].adj;
		}
	}
}

void TravelMap::AddCity(string & name)
{
	Citylist.push_back(name);
}

void TravelMap::DestroyCity(string & name)
{
	int des_pos = CityPos(name);
	auto iter = Citylist.begin() + des_pos;		//从城市列表删去name
	Citylist.erase(iter);
	Road * p, *q;
	for (int i = 0; i < Citylist.size(); ++i)	//从其他城市出度中删去这个城市
	{
		p = Citylist[i].adj;
		DestroyRoad(Citylist[i].name, name);
		while (p)
		{
			if (p->ter_num > des_pos)
				p->ter_num--;
			p = p->next;
		}
	}
}

void TravelMap::AddRoad(string & start, string & end, string & num, 
	Time & start_t, Time & end_t, Time & dur, double cost)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	Road * p = Citylist[start_pos].adj;
	if (p == nullptr)	Citylist[start_pos].adj = new Road(end_pos, start_t, end_t, dur, num, cost);
	while (p->next)
		p = p->next;
	p->next=new Road(end_pos, start_t, end_t, dur, num, cost);
}

void TravelMap::DestroyRoad(string & start, string & end)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	Road * p = Citylist[start_pos].adj, *q;
	while (p&&p->ter_num==end_pos)
	{
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return;
	p = p->next; q = p;
	while (p)
	{
		if (p->ter_num==end_pos)
		{
			q->next = p;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
}

void TravelMap::DestroyRoad(string & start, string & end, string & num)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	Road * p = Citylist[start_pos].adj, *q;
	while (p && p->number == num&&p->ter_num==end_pos)
	{
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return;
	p = p->next; q = p;
	while (p)
	{
		if (p->number == num&&p->ter_num==end_pos)
		{
			q->next = p;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
}

void TravelMap::DestroyRoad(string & start, string & end, Time & t)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	Road * p = Citylist[start_pos].adj, *q;
	while (p && p->start_time==t&&p->ter_num==end_pos)
	{
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return;
	p = p->next; q = p;
	while (p)
	{
		if (p->start_time==t&&p->ter_num==end_pos)
		{
			q->next = p;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
}

void TravelMap::MainFunction(string & start, bool stratege)
{

}
