#include "TravelMap.h"

void Menu(TravelMap & Train_Map,TravelMap & Plane_Map);
void Main_Function(TravelMap & Train_Map, TravelMap & Plane_Map);
void AddCity(TravelMap & Train_Map, TravelMap & Plane_Map);
void DestroyCity(TravelMap & Train_Map, TravelMap & Plane_Map);
void Display_city(TravelMap & Train_Map, TravelMap & Plane_Map);

int main()
{
	TravelMap Train_Map(0), 
		Plane_Map(1);
	system("color 8B");
	Menu(Train_Map,Plane_Map);
	cout << "Welcome!" << endl;
}

//菜单函数
void Menu(TravelMap & Train_Map, TravelMap & Plane_Map)		
{
	while (1)
	{
		cout << "\n\n\n\n";
		cout << "                     *****************************************\n";
		cout << "                     **          1=增加一个城市             **\n";
		cout << "                     **          2=增加一班火车             **\n";
		cout << "                     **          3=增加一班飞机             **\n";
		cout << "                     **          4=删除一个城市             **\n";
		cout << "                     **          5=删除一班火车             **\n";
		cout << "                     **          6=删除一班飞机             **\n";
		cout << "                     **          7=显示所有城市             **\n";
		cout << "                     **          8=显示所有火车             **\n";
		cout << "                     **          9=显示所有飞机             **\n";
		cout << "                     **          10=查询最短路线            **\n";
		cout << "                     **          0=退出                     **\n";
		cout << "                     *****************************************\n";
		cout << "                                   你的选择：";
		int choice;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 0:return;
		case 1:AddCity(Train_Map,Plane_Map); break;
		case 2:Train_Map.AddRoad(); break;
		case 3:Plane_Map.AddRoad(); break;
		case 4:DestroyCity(Train_Map,Plane_Map); break;
		case 5:Train_Map.DestroyRoad(); break;
		case 6:Plane_Map.DestroyRoad(); break;
		case 7:Display_city(Train_Map,Plane_Map); break;
		case 8:Train_Map.Display_road(); break;
		case 9:Plane_Map.Display_road(); break;
		case 10:Main_Function(Train_Map,Plane_Map); break;
		default:cout << "输入有误！请重新输入："; break;
		}
	}
}

void Main_Function(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "请输入出发地：";
	string start;
	cin >> start; cin.get();
	cout << "请输入目的地：";
	string end;
	cin >> end; cin.get();
	cout << "请选择出行方式：" << endl
		<< "0=火车" << endl
		<< "1=飞机" << endl
		<< "你的选择是：";
	bool travel_method;
	cin >> travel_method; cin.get();
	cout << "请输入出发时间（格式如8:45)：";
	Time start_t; int t;
	cin >> t; cin.get(); start_t.hour = t;
	cin >> t; cin.get(); start_t.minutes = t;
	cout << "请选择出行策略：" << endl
		<< "0=最省钱" << endl
		<< "1=最省时间" << endl
		<< "你的选择是：";
	bool strategy; 
	int tag;
	cin >> strategy; cin.get();
	if (travel_method)
	{
		if (strategy)
		{
			tag = Plane_Map.Least_Time_Road(start, end, start_t);
			if(tag==-1)	cout<< "无此城市，查询失败." << endl;
			else if (tag == -2)	cout << "两城市间没有可行路." << endl;
		}
		else
		{
			tag = Plane_Map.Lowest_Price_Road(start, end, start_t);
			if (tag == -1)	cout << "无此城市，查询失败." << endl;
			else if (tag == -2)	cout << "两城市间没有可行路." << endl;
		}
	} 
	else
	{
		if (strategy)
		{
			tag = Train_Map.Least_Time_Road(start, end, start_t);
			if (tag == -1)	cout << "无此城市，查询失败." << endl;
			else if (tag == -2)	cout << "两城市间没有可行路." << endl;
		}
		else
		{
			tag = Train_Map.Lowest_Price_Road(start, end, start_t);
			if (tag == -1)	cout << "无此城市，查询失败." << endl;
			else if (tag == -2)	cout << "两城市间没有可行路." << endl;
		}
	}

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=继续查询最短线路       **\n";
	cout << "                     **          0=返回上级菜单           **\n";
	cout << "                     ***************************************\n";
	cout << "                                   你的选择：";
	int choice;
	cin >> choice;
	if (choice)	Main_Function(Train_Map,Plane_Map);
	else
		system("CLS");
}

void AddCity(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "您想要添加城市的名字是：";
	string name;
	cin >> name;
	bool t1, t2;
	t1=Train_Map.AddCity(name);
	t2=Plane_Map.AddCity(name);
	if (t1&&t2)
		cout << "添加 " << name << " 成功!" << endl;
	else if (t1 && !t2)
		cout << "铁路图中添加此城市成功，航线图中已有此城市，添加失败。" << endl;
	else if (!t1&&t2)
		cout << "航线图中添加此城市成功，铁路图中已有此城市，添加失败。" << endl;
	else
		cout << "该城市已出现在铁路图与航线图中，无法重复添加。" << endl;
	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=继续增加城市             **\n";
	cout << "                     **          0=返回上级菜单             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   你的选择：";
	int choice;
	cin >> choice;
	if (choice)	AddCity(Train_Map,Plane_Map);
	else
		system("CLS");
}

void DestroyCity(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "您想要删除城市的名字是：";
	string name;
	cin >> name;
	cin.get();
	bool t1 = Train_Map.DestroyCity(name);
	bool t2 = Plane_Map.DestroyCity(name);
	if (t1&&t2)
		cout << "删除 " << name << " 成功！" << endl;
	else if (t1 && !t2)
		cout << "删除铁路成功，该城市没有机场。" << endl;
	else if (t2 && !t1)
		cout << "删除航线成功，该城市没有火车站。" << endl;
	else
		cout << "该城市没有火车站和飞机场，删除失败。" << endl;

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=继续删除城市             **\n";
	cout << "                     **          0=返回上级菜单             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   你的选择：";
	int choice;
	cin >> choice;
	if (choice)	DestroyCity(Train_Map,Plane_Map);
	else
		system("CLS");
}

void Display_city(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	Train_Map.Display_city();
	Plane_Map.Display_city();
}
