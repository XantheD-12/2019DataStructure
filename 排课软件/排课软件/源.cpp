#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<fstream>
using namespace std;

const int DefaultSize = 10;
class Graph;
struct Edge {
	friend class Graph;
	int dest;
	Edge* link;
	Edge(int D) :
		dest(D), link(NULL) { }
	int operator != (Edge& E)const { return dest != E.dest; }
};

struct Vertex
{
	friend class Graph;
	string data;
	string name;
	int longtime;
	int time;
	Edge* adj;
	Vertex() :longtime(0), time(0), adj(NULL) {}
};

//有向无权图
class Graph { //图的邻接表的类定义
private:
	Vertex* NodeTable;//顶点表
	int* count;//记录各个顶点入度。入度为零的顶点即无前驱的顶点
	int n;//顶点数量
	int curn;//当前结点数量
	int getVertexPos(const string vertex)
	{
		for (int i = 0; i < n; i++)
		{
			if (NodeTable[i].data == vertex)return i;
		}
		return -1;//vertex不在顶点中
	}//给出vertex在顶点中的位置
public:
	Graph(const int vertices = 0) :n(vertices), curn(0) {
		NodeTable = new Vertex[n];
		count = new int[n];
		for (int i = 0; i < n; i++)count[i] = 0;
	};
	~Graph()
	{
		for (int i = 0; i < curn; i++)
		{
			Edge* p = NodeTable[i].adj;
			while (p != NULL)
			{
				NodeTable[i].adj = p->link;
				delete p;
				p = NodeTable[i].adj;
			}
		}
		delete[]NodeTable;
	}
	string getValue(int i);
	//DistType getWeight(int v1, int v2);
	bool InsertVertex(string& vertex, string name, int longtime, int time);
	bool RemoveVertex(int v);
	bool InsertEdge(string& v1, string& v2);
	bool RemoveEdge(int v1, int v2);
	void output(string vertex)
	{
		int i = getVertexPos(vertex);
		Edge* p = NodeTable[i].adj;
		cout << vertex << NodeTable[i].name;
		while (p != NULL)
		{
			cout << "->";
			cout << NodeTable[p->dest].data << NodeTable[p->dest].name;
			p = p->link;
		}
		cout << endl;
	}
	void TopologicalOrder();//拓扑排序
};

string Graph::getValue(int i)
{
	if (i >= 0 && i < n) return NodeTable[i].data;
	return "-1";
}

bool Graph::InsertVertex(string& vertex, string mname, int longtime, int time)
{
	if (getVertexPos(vertex) != -1)
	{
		cout << "该课程已存在！" << endl;
		return false;
	}
	if (curn < n)
	{
		NodeTable[curn].data = vertex;
		NodeTable[curn].name=mname;
		NodeTable[curn].longtime = longtime;
		NodeTable[curn].time = time;
		curn++;
		return true;
	}
	cout << "已满！不能插入！" << endl;
	return false;
}

bool Graph::RemoveVertex(int v)
{
	if (v<0 || v>curn)
	{
		cout << "该顶点不存在！" << endl;
		return false;
	}
	Edge* p;
	while (NodeTable[v].adj != NULL)
	{
		p = NodeTable[v].adj;
		NodeTable[v].adj = p->link;
		delete p;
		curn--;
	}
	return true;
}

bool Graph::InsertEdge(string& vex1, string& vex2)
{
	int v1 = getVertexPos(vex1);
	int v2 = getVertexPos(vex2);
	if (v1 >= 0 && v1 < n && v2 >= 0 && v2 < n)
	{
		Edge* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)//该边已存在
		{
			cout << "该边已存在！" << endl;
			return false;
		}
		else
		{
			p = new Edge(v2);//在v1中插入v2
			p->link = NodeTable[v1].adj;
			NodeTable[v1].adj = p;
			count[v2]++;//v2的入度增加
			return true;
		}
	}
	return false;
}

bool Graph::RemoveEdge(int v1, int v2)
{
	if (v1 >= 0 && v1 < curn && v2 >= 0 && v2 < curn)
	{
		Edge* p = NodeTable[v1].adj;
		Edge* s = p;
		Edge* q = NULL;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)
		{
			if (p == s) NodeTable[v1].adj = p->link;
			else q->link = p->link;
			delete p;
			count[v2]--;//v2的入度自减
			return true;
		}
		else
		{
			cout << "该边不存在！" << endl;
			return false;
		}
	}
	return false;
}


//拓扑排序的算法
void Graph::TopologicalOrder()
{
	fstream fout;
	fout.open("课表.txt");
	int sum = 0;//学时记录
	int time = 0;
	int weekday = 1;
	int temp;//暂存weekday
	int week[4][5];//每周的课程存储
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
			week[i][j] = -1;
	}
	int* flag = new int[n];
	int* key = new int[n];//记录是否该点删除，删除过为0
	for (int i = 0; i < n; i++)
	{
		flag[i] = 0;//初始化为0
		key[i] = 1;
	}
	int x = 1;
	while (time < n) //完成课表的分配
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				week[i][j] = -1;
		}
		fout << "====================================第" << x << "学期====================================" << endl;
		sum = 0;
		for (int i = 0; i < n; i++)
		{
			if (NodeTable[i].time == x && sum <= 50)//指定学期的课程学时只有5和3
			{
				if (NodeTable[i].longtime == 5)//2+3
				{
					//先排2再排3
					for (int m = 0; m < 5; m++)//排2
					{
						if (week[0][m] == -1)//第一大节
						{
							week[0][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//第二大节
						{
							week[2][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 3)	break;
					}//2已排完
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期

					//排3
					if (week[1][weekday - 1] == -1) {
						week[1][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
					else if (week[3][weekday - 1] == -1)
					{
						week[3][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
				}
				else if (NodeTable[i].longtime == 3)//3
				{
					for (int n = 0; n < 5; n++)
					{
						if (week[1][n] == -1) {
							week[1][n] = i; NodeTable[i].longtime -= 3; NodeTable[i].longtime -= 3; sum += 3; break;
						}
						else if (week[3][n] == -1) {
							week[3][n] = i; NodeTable[i].longtime -= 3;  NodeTable[i].longtime -= 3; sum += 3; break;
						}
					}
				}
				//cout << NodeTable[i].data << " " << NodeTable[i].name << endl;
				time++;
				flag[i] = 1;//已出
			}
		}
		for (int i = 0; i < n; i++)//第一轮做标记
		{
			if (NodeTable[i].time == 0 && count[i] == 0 && flag[i] != 1&&sum+NodeTable[i].longtime<=45)
			{
				if (NodeTable[i].longtime == 6)//3+3
				{
					for (int m = 0; m < 5; m++)//排3
					{
						if (week[1][m] == -1)//第二大节
						{
							week[1][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 3;
							sum += 3;
						}
						else if (week[3][m] == -1)//第四大节
						{
							week[3][m] = i;
							weekday = m + 1;//记录第一次课
							NodeTable[i].longtime -= 3;
							temp = weekday;
							sum += 3;
						}
						if (NodeTable[i].longtime == 3)break;
					}//3已排完
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
					if (week[1][weekday - 1] == -1) {
						week[1][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
					else if (week[3][weekday - 1] == -1)
					{
						week[3][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
					if (NodeTable[i].longtime == 3)
					{
						if (weekday % 2 == 1 && weekday <= 5)
						{
							while (weekday <= 5 && NodeTable[i].longtime == 3)
							{
								weekday++;
								if (week[1][weekday - 1] == -1) { week[1][weekday - 1] = i; NodeTable[i].longtime -= 3;sum += 3;}
								else if (week[3][weekday - 1] == -1) { week[3][weekday - 1] = i; NodeTable[i].longtime -= 3;sum += 3;}
							}
						}
					}
					//3节课未排进，2+1
					if (NodeTable[i].longtime == 3)
					{
						weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							weekday++;
						}
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
					}
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "未排进" << endl; }
				}
				else if (NodeTable[i].longtime == 5)//2+3
				{
					//先排2再排3
					for (int m = 0; m < 5; m++)//排2
					{
						if (week[0][m] == -1)//第一大节
						{
							week[0][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//第二大节
						{
							week[2][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 3)	break;
					}//2已排完
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期

					//排3
					if (week[1][weekday - 1] == -1) {
						week[1][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
					else if (week[3][weekday - 1] == -1)
					{
						week[3][weekday - 1] = i;
						NodeTable[i].longtime -= 3;
						sum += 3;
					}
					if (NodeTable[i].longtime == 3)//隔天没有排进去
					{
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							weekday++;
							if (week[1][weekday - 1] == -1) { week[1][weekday - 1] = i; NodeTable[i].longtime -= 3; sum += 3; }
							else if (week[3][weekday - 1] == -1) { week[3][weekday - 1] = i; NodeTable[i].longtime -= 3; sum += 3; }
						}
					}
					//3节课未排进，2+1
					if (NodeTable[i].longtime == 3)
					{
						weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							weekday++;
						}
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
					}
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "未排进" << endl; }
				}
				else if (NodeTable[i].longtime == 4)//2+2
				{
					for (int m = 0; m < 5; m++)//排2
					{
						if (week[0][m] == -1)//第一大节
						{
							week[0][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//第二大节
						{
							week[2][m] = i;
							weekday = m + 1;//记录第一次课
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 2)break;
					}//2已排完
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
					if (week[0][weekday - 1] == -1) {
						week[0][weekday - 1] = i;
						NodeTable[i].longtime -= 2;
						sum += 2;
					}
					else if (week[2][weekday - 1] == -1) {
						week[2][weekday - 1] = i;
						NodeTable[i].longtime -= 2;
						sum += 2;
					}
					//未在隔天排进
					if (NodeTable[i].longtime == 2)
					{
						weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
						while (weekday < 5 && NodeTable[i].longtime == 2)
						{
							weekday++;
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }

						}
					}
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "未排进" << endl; }
				}
				else//3
				{
					for (int n = 0; n < 5; n++)
					{
						if (week[1][n] == -1) {
							week[1][n] = i; NodeTable[i].longtime -= 3; NodeTable[i].longtime -= 3; sum += 3; break;
						}
						else if (week[3][n] == -1) {
							week[3][n] = i; NodeTable[i].longtime -= 3;  NodeTable[i].longtime -= 3; sum += 3; break;
						}
					}
					//3未排进去
					if (NodeTable[i].longtime == 3)
					{
						for (int m = 0; m < 5; m++)//排2
						{
							if (week[0][m] == -1)//第一大节
							{
								week[0][m] = i;
								weekday = m + 1;//记录第一次课
								temp = weekday;
								NodeTable[i].longtime -= 2;
								sum += 2;
							}
							else if (week[2][m] == -1)//第二大节
							{
								week[2][m] = i;
								weekday = m + 1;//记录第一次课
								temp = weekday;
								NodeTable[i].longtime -= 2;
								sum += 2;
							}
							if (NodeTable[i].longtime == 1)break;
						}//2已排完
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
						//未在隔天排进
						if (NodeTable[i].longtime == 1)
						{
							weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
							while (weekday < 5 && NodeTable[i].longtime == 3)
							{
								weekday++;
								if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
								else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }

							}
							weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//第二次课的日期
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
							else if (week[2][weekday - 1] == -1) {	week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2;	}
						}
						if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "未排进" << endl; }
					}
				}

				//cout << NodeTable[i].data << " " << NodeTable[i].name << endl;
				time++;
				flag[i] = 1;//已出
			}
		}
		fout << endl;
		//第二轮循环
		for (int j = 0; j < n; j++)
		{
			if (flag[j] && key[j])
			{
				key[j] = 0;
				Edge* l = NodeTable[j].adj;
				while (l) {//扫描该顶点的出边表
					int k = l->dest;//另一顶点
					if (count[k] > 0)count[k]--;
					else break;
					l = l->link;
				}
			}
		}
		fout << "	周一		周二		周三		周四		周五" << endl;
		for (int m = 0; m < 4; m++)
		{
			fout << m + 1 << "	";
			for (int n = 0; n < 5; n++)
			{
				if (week[m][n] != -1)
				{
					if(NodeTable[week[m][n]].name=="英语"|| NodeTable[week[m][n]].name == "Java"|| NodeTable[week[m][n]].name == "Delphi"|| 
						NodeTable[week[m][n]].name == "VB.net"|| NodeTable[week[m][n]].name == "C#.net")
						fout << NodeTable[week[m][n]].name << "		";
					else if (NodeTable[week[m][n]].name == "计算机系统结构"|| NodeTable[week[m][n]].name == "计算机组成原理"
						|| NodeTable[week[m][n]].name == "程序设计基础"|| NodeTable[week[m][n]].name == "操作系统原理"
						|| NodeTable[week[m][n]].name == "单片机应用"|| NodeTable[week[m][n]].name == "计算机网络"
						|| NodeTable[week[m][n]].name == "PowerBuilder"|| NodeTable[week[m][n]].name == "JSP程序设计"
						|| NodeTable[week[m][n]].name == "PowerBuilder"|| NodeTable[week[m][n]].name == "ASP程序设计"
						|| NodeTable[week[m][n]].name == "数据库原理"|| NodeTable[week[m][n]].name == "面向对象程序设计"
						|| NodeTable[week[m][n]].name == "C++Builder")fout << NodeTable[week[m][n]].name<<"	";
					else fout << NodeTable[week[m][n]].name << "		";
				}
				else fout << "		";
			}
			fout << endl;
			fout << endl;
		}
		fout << endl;
		fout << endl;
		x++;
	}
	fout.close();
}

int main()
{
	ifstream fin;
	fin.open("课程信息.txt");
	int N;
	string name;//课程名字
	string mname;
	string num;//课程编号
	int longtime;//学时
	int time;//指定学期
	string prior;
	string* term;///每学期的课程数
	//int weekday;//排课日期
	cout << "输入课程总数：";
	fin >> N;
	while (1)
	{
		if (N <= 0)
		{
			cout << "课程总数输入错误！" << endl;
			cout << "输入课程总数：";
			fin >> N;
		}
		else break;
	}
	Graph table(N);
	term = new string[N];
	cout << "请依次输入课程编号和课程名字、学时、指定开课学期及先行课程" << endl;
	int i = 0;
	while (i < N)
	{
		fin >> num >> name >> longtime >> time;
		
		if (table.InsertVertex(num, name, longtime, time))i++;//插入结点成功,i++
		while (fin.get() != 10)
		{
			fin >> prior;
			table.InsertEdge(prior, num);
		}
	}
	cout << "课程添加完毕！" << endl;
	table.TopologicalOrder();
	fin.close();
	return 0;
}

