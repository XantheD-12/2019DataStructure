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

//������Ȩͼ
class Graph { //ͼ���ڽӱ���ඨ��
private:
	Vertex* NodeTable;//�����
	int* count;//��¼����������ȡ����Ϊ��Ķ��㼴��ǰ���Ķ���
	int n;//��������
	int curn;//��ǰ�������
	int getVertexPos(const string vertex)
	{
		for (int i = 0; i < n; i++)
		{
			if (NodeTable[i].data == vertex)return i;
		}
		return -1;//vertex���ڶ�����
	}//����vertex�ڶ����е�λ��
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
	void TopologicalOrder();//��������
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
		cout << "�ÿγ��Ѵ��ڣ�" << endl;
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
	cout << "���������ܲ��룡" << endl;
	return false;
}

bool Graph::RemoveVertex(int v)
{
	if (v<0 || v>curn)
	{
		cout << "�ö��㲻���ڣ�" << endl;
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
		if (p != NULL)//�ñ��Ѵ���
		{
			cout << "�ñ��Ѵ��ڣ�" << endl;
			return false;
		}
		else
		{
			p = new Edge(v2);//��v1�в���v2
			p->link = NodeTable[v1].adj;
			NodeTable[v1].adj = p;
			count[v2]++;//v2���������
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
			count[v2]--;//v2������Լ�
			return true;
		}
		else
		{
			cout << "�ñ߲����ڣ�" << endl;
			return false;
		}
	}
	return false;
}


//����������㷨
void Graph::TopologicalOrder()
{
	fstream fout;
	fout.open("�α�.txt");
	int sum = 0;//ѧʱ��¼
	int time = 0;
	int weekday = 1;
	int temp;//�ݴ�weekday
	int week[4][5];//ÿ�ܵĿγ̴洢
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
			week[i][j] = -1;
	}
	int* flag = new int[n];
	int* key = new int[n];//��¼�Ƿ�õ�ɾ����ɾ����Ϊ0
	for (int i = 0; i < n; i++)
	{
		flag[i] = 0;//��ʼ��Ϊ0
		key[i] = 1;
	}
	int x = 1;
	while (time < n) //��ɿα�ķ���
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				week[i][j] = -1;
		}
		fout << "====================================��" << x << "ѧ��====================================" << endl;
		sum = 0;
		for (int i = 0; i < n; i++)
		{
			if (NodeTable[i].time == x && sum <= 50)//ָ��ѧ�ڵĿγ�ѧʱֻ��5��3
			{
				if (NodeTable[i].longtime == 5)//2+3
				{
					//����2����3
					for (int m = 0; m < 5; m++)//��2
					{
						if (week[0][m] == -1)//��һ���
						{
							week[0][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//�ڶ����
						{
							week[2][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 3)	break;
					}//2������
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����

					//��3
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
				flag[i] = 1;//�ѳ�
			}
		}
		for (int i = 0; i < n; i++)//��һ�������
		{
			if (NodeTable[i].time == 0 && count[i] == 0 && flag[i] != 1&&sum+NodeTable[i].longtime<=45)
			{
				if (NodeTable[i].longtime == 6)//3+3
				{
					for (int m = 0; m < 5; m++)//��3
					{
						if (week[1][m] == -1)//�ڶ����
						{
							week[1][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 3;
							sum += 3;
						}
						else if (week[3][m] == -1)//���Ĵ��
						{
							week[3][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							NodeTable[i].longtime -= 3;
							temp = weekday;
							sum += 3;
						}
						if (NodeTable[i].longtime == 3)break;
					}//3������
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
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
					//3�ڿ�δ�Ž���2+1
					if (NodeTable[i].longtime == 3)
					{
						weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							weekday++;
						}
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
					}
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "δ�Ž�" << endl; }
				}
				else if (NodeTable[i].longtime == 5)//2+3
				{
					//����2����3
					for (int m = 0; m < 5; m++)//��2
					{
						if (week[0][m] == -1)//��һ���
						{
							week[0][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//�ڶ����
						{
							week[2][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 3)	break;
					}//2������
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����

					//��3
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
					if (NodeTable[i].longtime == 3)//����û���Ž�ȥ
					{
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							weekday++;
							if (week[1][weekday - 1] == -1) { week[1][weekday - 1] = i; NodeTable[i].longtime -= 3; sum += 3; }
							else if (week[3][weekday - 1] == -1) { week[3][weekday - 1] = i; NodeTable[i].longtime -= 3; sum += 3; }
						}
					}
					//3�ڿ�δ�Ž���2+1
					if (NodeTable[i].longtime == 3)
					{
						weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
						while (weekday <= 5 && NodeTable[i].longtime == 3)
						{
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
							weekday++;
						}
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
					}
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "δ�Ž�" << endl; }
				}
				else if (NodeTable[i].longtime == 4)//2+2
				{
					for (int m = 0; m < 5; m++)//��2
					{
						if (week[0][m] == -1)//��һ���
						{
							week[0][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						else if (week[2][m] == -1)//�ڶ����
						{
							week[2][m] = i;
							weekday = m + 1;//��¼��һ�ο�
							temp = weekday;
							NodeTable[i].longtime -= 2;
							sum += 2;
						}
						if (NodeTable[i].longtime == 2)break;
					}//2������
					weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
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
					//δ�ڸ����Ž�
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
					if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "δ�Ž�" << endl; }
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
					//3δ�Ž�ȥ
					if (NodeTable[i].longtime == 3)
					{
						for (int m = 0; m < 5; m++)//��2
						{
							if (week[0][m] == -1)//��һ���
							{
								week[0][m] = i;
								weekday = m + 1;//��¼��һ�ο�
								temp = weekday;
								NodeTable[i].longtime -= 2;
								sum += 2;
							}
							else if (week[2][m] == -1)//�ڶ����
							{
								week[2][m] = i;
								weekday = m + 1;//��¼��һ�ο�
								temp = weekday;
								NodeTable[i].longtime -= 2;
								sum += 2;
							}
							if (NodeTable[i].longtime == 1)break;
						}//2������
						weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
						if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
						else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2; }
						//δ�ڸ����Ž�
						if (NodeTable[i].longtime == 1)
						{
							weekday = (temp + 2 - 5) > 0 ? (temp + 2 - 5) : (temp + 2);
							while (weekday < 5 && NodeTable[i].longtime == 3)
							{
								weekday++;
								if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }
								else if (week[2][weekday - 1] == -1) { week[2][weekday - 1] = i; NodeTable[i].longtime -= 2; sum += 2; }

							}
							weekday = (weekday + 2 - 5) > 0 ? (weekday + 2 - 5) : (weekday + 2);//�ڶ��οε�����
							if (week[0][weekday - 1] == -1) { week[0][weekday - 1] = i;  NodeTable[i].longtime -= 1; sum += 2; }
							else if (week[2][weekday - 1] == -1) {	week[2][weekday - 1] = i; NodeTable[i].longtime -= 1; sum += 2;	}
						}
						if (NodeTable[i].longtime != 0) { fout << NodeTable[i].name << "δ�Ž�" << endl; }
					}
				}

				//cout << NodeTable[i].data << " " << NodeTable[i].name << endl;
				time++;
				flag[i] = 1;//�ѳ�
			}
		}
		fout << endl;
		//�ڶ���ѭ��
		for (int j = 0; j < n; j++)
		{
			if (flag[j] && key[j])
			{
				key[j] = 0;
				Edge* l = NodeTable[j].adj;
				while (l) {//ɨ��ö���ĳ��߱�
					int k = l->dest;//��һ����
					if (count[k] > 0)count[k]--;
					else break;
					l = l->link;
				}
			}
		}
		fout << "	��һ		�ܶ�		����		����		����" << endl;
		for (int m = 0; m < 4; m++)
		{
			fout << m + 1 << "	";
			for (int n = 0; n < 5; n++)
			{
				if (week[m][n] != -1)
				{
					if(NodeTable[week[m][n]].name=="Ӣ��"|| NodeTable[week[m][n]].name == "Java"|| NodeTable[week[m][n]].name == "Delphi"|| 
						NodeTable[week[m][n]].name == "VB.net"|| NodeTable[week[m][n]].name == "C#.net")
						fout << NodeTable[week[m][n]].name << "		";
					else if (NodeTable[week[m][n]].name == "�����ϵͳ�ṹ"|| NodeTable[week[m][n]].name == "��������ԭ��"
						|| NodeTable[week[m][n]].name == "������ƻ���"|| NodeTable[week[m][n]].name == "����ϵͳԭ��"
						|| NodeTable[week[m][n]].name == "��Ƭ��Ӧ��"|| NodeTable[week[m][n]].name == "���������"
						|| NodeTable[week[m][n]].name == "PowerBuilder"|| NodeTable[week[m][n]].name == "JSP�������"
						|| NodeTable[week[m][n]].name == "PowerBuilder"|| NodeTable[week[m][n]].name == "ASP�������"
						|| NodeTable[week[m][n]].name == "���ݿ�ԭ��"|| NodeTable[week[m][n]].name == "�������������"
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
	fin.open("�γ���Ϣ.txt");
	int N;
	string name;//�γ�����
	string mname;
	string num;//�γ̱��
	int longtime;//ѧʱ
	int time;//ָ��ѧ��
	string prior;
	string* term;///ÿѧ�ڵĿγ���
	//int weekday;//�ſ�����
	cout << "����γ�������";
	fin >> N;
	while (1)
	{
		if (N <= 0)
		{
			cout << "�γ������������" << endl;
			cout << "����γ�������";
			fin >> N;
		}
		else break;
	}
	Graph table(N);
	term = new string[N];
	cout << "����������γ̱�źͿγ����֡�ѧʱ��ָ������ѧ�ڼ����пγ�" << endl;
	int i = 0;
	while (i < N)
	{
		fin >> num >> name >> longtime >> time;
		
		if (table.InsertVertex(num, name, longtime, time))i++;//������ɹ�,i++
		while (fin.get() != 10)
		{
			fin >> prior;
			table.InsertEdge(prior, num);
		}
	}
	cout << "�γ������ϣ�" << endl;
	table.TopologicalOrder();
	fin.close();
	return 0;
}

