#include<iostream>
#include<string>
using namespace std;

//邻接表
#define MAXNUM 100000
template<class T>
struct Edge {//边结点的定义
	int dest;//边的另一结点
	double cost;//边上的权值
	Edge<T>* link;//下一条边链指针
	Edge() {}//构造函数
	Edge(int num = -1, double weight = 0) :dest(num), cost(weight), link(NULL) {}//构造函数
};

template<class T>
struct Vertex {//顶点的定义
	T data;//顶点的名字
	Edge<T>* adj;//边链表的头指针
	Vertex() :adj(NULL) {}
};

//最小生成树
struct MSTEdgeNode {//生成树边结点类定义
	int tail, head;//生成树各边的两顶点
	double cost;//生成树各边的代价
	MSTEdgeNode(int mtail = -1, int mhead = -1, double mcost = 0) :tail(mtail), head(mhead), cost(mcost) {}
	bool operator <=(MSTEdgeNode& r) { return cost <= r.cost; }
	bool operator>(MSTEdgeNode& r) { return cost > r.cost; }
};

class MinSpanTree
{
	//生成树的类定义
public:
	MinSpanTree(int sz = 0) :MaxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[MaxSize];
	}
	~MinSpanTree() { delete[]edgevalue; }
	void Insert(MSTEdgeNode& item)//将item加到最小生成树中
	{
		if (n < MaxSize)
		{
			edgevalue[n] = item;
			n++;
		}
	}
	int getSize() { return n; }
	MSTEdgeNode getEdgeNode(int x)//得到x的生成树边结点
	{
		if (x >= 0 && x < n)return edgevalue[x];
		else
		{
			cout << "该结点不存在！" << endl;
			return NULL;
		}
	}
	void MakeEmpty()
	{
		for (int i = 0; i < MaxSize; i++)
		{
			edgevalue[i] = NULL;
		}
		n = 0;
	}
protected:
	MSTEdgeNode* edgevalue;//边值数组
	int MaxSize, n; //最大边数,当前边数
};

template<class T>
class Graph {
private:
	Vertex<T>* NodeTable;//顶点表（各边链表的头结点）
	int getVertex(const T vertex)
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == vertex)return i;
		}
		return -1;
	}//给出顶点vertex在图中的位置
	int numVertices;//当前顶点数
	int numEdges;//当前边数
	int maxVertices;//最大顶点数
public:
	Graph(int sz = 0);//构造函数
	~Graph();//析构函数
	T getValue(int i)
	{
		if (i >= 0 && i < numVertices)
		{
			return NodeTable[i].data;
		}
		else
			return "0";
	}//取位置为i的顶点中的值
	double getWeight(int v1, int v2);//返回边（v1，v2）上的权值
	bool insertVertex(const T& vertex);//在图中插入一个顶点vertex
	bool insertEdge(int v1, int v2, double cost);//在图中插入一条边（v1，v2）
	int getFirstNeighbor(int v);//取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w);//取v的邻接顶点w的下一邻接顶点
	int NumberOfVertices() { return numVertices; }//返回当前顶点数
	int NumberOfEdges() { return numEdges; }//返回当前边数
	int getNum(T& name)
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (name == NodeTable[i].data)return i;
		}
		cout << name << "不存在！" << endl;
		return -1;
	}
	void Prim(T& x, MinSpanTree* MST);//prim算法构造以x为顶点的最小生成树
	void output(MinSpanTree* x);//打印最小生成树
	void outputVertex()
	{
		for (int i = 0; i < numVertices; i++)
		{
			cout << NodeTable[i].data;
			if (i < numVertices - 1)cout << " ";
		}
		cout << endl;
	}
};

template<class T>
Graph<T>::Graph(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<T>[maxVertices];
	if (NodeTable == NULL)
	{
		cout << "存储分配失败！" << endl;
	}
	for (int i = 0; i < maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}

template<class T>
Graph<T>::~Graph()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T>* p = NodeTable[i].adj;
		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

template<class T>
double Graph<T>::getWeight(int v1, int v2)
{//函数返回边（v1，v2）上的权值，若该边不在图中，则函数返回权值0
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		if (v1 == v2) { return 0; }
		Edge<T>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)
		{
			return p->cost;
		}
	}
	return MAXNUM;//边（v1，v2）不存在
}

template<class T>
bool Graph<T>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices)
	{
		cout << "顶点已满!" << endl;
		return false;
	}//顶点已满，不能插入
	for (int i = 0; i < numVertices; i++)
	{
		if (NodeTable[i].data == vertex)
		{
			cout << vertex << "已存在！" << endl;
			return false;
		}//存在相同顶点，不能插入
	}
	NodeTable[numVertices].data = vertex;//插入在表的最后
	numVertices++;
	return true;
}

template<class T>
bool Graph<T>::insertEdge(int v1, int v2, double cost)
{
	//在图中插入一条边（v1，v2），权值为cost，若此边存在或参数不合理，函数返回false，否则返回true
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)//判断v1，v2是否在图中
	{
		Edge<T>* p = NodeTable[v1].adj;
		Edge<T>* q;
		while (p != NULL && p->dest != v2)//寻找是否存在（v1，v2）
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
			p = new Edge<T>(v2, cost);//在v1中插入v2
			q = new Edge<T>(v1, cost);//在v2中插入v1
			p->link = NodeTable[v1].adj;
			NodeTable[v1].adj = p;
			q->link = NodeTable[v2].adj;
			NodeTable[v2].adj = q;
			numEdges++;
			return true;
		}
	}
	return false;
}

template<class T>
int Graph<T>::getFirstNeighbor(int v)
{
	//给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回1
	if (v >= 0 && v < numVertices)//顶点v存在
	{
		Edge<T>* p = NodeTable[v].adj;//对应边链表的第一个边结点
		if (p != NULL)return p->dest;//存在，返回第一个邻接顶点
	}
	return -1;//不存在，返回-1
}

template<class T>
int Graph<T>::getNextNeighbor(int v, int w)
{
	//给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回-1
	if (v >= 0 && v < numVertices && w >= 0 && w < numVertices)//顶点v和w存在
	{
		Edge<T>* p = NodeTable[v].adj;//对应边链表的第一个边结点
		while (p != NULL && p->dest != w)//寻找邻接顶点w
		{
			p = p->link;
		}
		if (p->dest == NULL)
		{
			cout << NodeTable[v].data << "与" << NodeTable[w].data << "不存在边" << endl;//顶点v和顶点w不存在边
			return -1;
		}
		else if (p->link != NULL)return p->link->dest;//返回下一个邻接顶点
	}
	return -1;//下一个
}


template<class T>
void Graph<T>::Prim(T& x, MinSpanTree* MST)
{
	MST->MakeEmpty();
	int num = getNum(x);//num为x的位置
	double* lowcost = new double[numVertices];//存放生成树顶点集合内顶点到生成树外各顶点的各边上的当前最小权值；
	int* nearvex = new int[numVertices];//记录生成树顶点集合外各顶点距离集合内哪个顶点最近((即权值最小))。
	for (int i = 0; i < numVertices; i++)
	{
		lowcost[i] = getWeight(num, i); //顶点x到各边的代价
		nearvex[i] = num;//及最短带权路径
	}
	nearvex[num] = -1; //顶点x加到生成树顶点集合
	MSTEdgeNode e; //最小生成树结点辅助单元
	for (int i = 1; i < numVertices; i++)//循环n-1次, 加入n-1条边
	{
		double min = MAXNUM;
		int v = num;
		for (int j = 0; j < numVertices; j++)
		{
			if (nearvex[j] != -1 && lowcost[j] < min)
			{
				v = j;
				min = lowcost[j];
			}
			//求生成树外顶点到生成树内顶点具有最小
			//权值的边, v是当前具最小权值的边的位置
		}
		if (v != num)  //v==num表示再也找不到要求顶点了
		{
			e.tail = v;
			e.head = nearvex[v];
			e.cost = lowcost[v];
			MST->Insert(e); //选出的边加入生成树
			nearvex[v] = -1; //作该边已加入生成树标记
			for (int j = 0; j < numVertices; j++)
				if (nearvex[j] != -1 &&// j 不在生成树中
					getWeight(v, j) < lowcost[j])//需要修改
				{
					lowcost[j] = getWeight(v, j);
					nearvex[j] = v;
				}
		}
	}
	delete[]lowcost;
	delete[]nearvex;
}

template<class T>
void Graph<T>::output(MinSpanTree* x)
{
	int head, tail;//最小生成树一条边的起始结点编号、终止结点编号
	double cost;;//最小生成树一条边的权值
	cout << "最小生成树为：";
	for (int i = 0; i < x->getSize(); i++)
	{
		head = x->getEdgeNode(i).head;//最小生成树一条边的起始结点编号
		tail = x->getEdgeNode(i).tail;//最小生成树一条边的终止结点编号
		cost = x->getEdgeNode(i).cost;//最小生成树一条边的权值
		cout << getValue(head) << "-<" << cost << ">->" << getValue(tail);
		if (i != x->getSize() - 1)cout << " ";
	}
	cout << endl;
}

int main()
{
	cout << "**          电网造价模拟系统          **" << endl;
	cout << "----------------------------------------" << endl;
	cout << "**          A---创造电网结点          **" << endl;
	cout << "**          B---添加电网的边          **" << endl;
	cout << "**          C---构造最小生成树        **" << endl;
	cout << "**          D---显示最小生成树        **" << endl;
	cout << "**          E---退出程序              **" << endl;
	cout << "----------------------------------------" << endl;
	cout << endl;
	char op;//操作符
	int n = 0;//结点个数
	string node;//结点名称
	string n1, n2;//两顶点名
	int v1, v2;//两顶点的顶点号
	double l;//权值
	int edgecount = 0;//记录边数
	int verflag = 0;//记录顶点数
	int flag = 0;//记录A、B操作
	MinSpanTree* tree = nullptr;
	Graph<string>* G = nullptr;
	cout << "请选择操作:";
	cin >> op;
	while (op != 'E')
	{
		switch (op)
		{
		case 'A':
			if (flag >= 1)
			{
				cout << "已创造结点！不能再添加结点！" << endl;
				cout << endl;
				break;
			}
			cout << "请输入结点个数：";
			cin >> n;
			if (n <= 0)
			{
				cout << "结点个数输入错误！" << endl;
				break;
			}
			tree = new MinSpanTree(n - 1);
			G = new Graph<string>(n);
			cout << "请依次输入各结点：";
			for (int i = 0; i < n; i++)
			{
				cin >> node;
				verflag = G->insertVertex(node);
				if (!verflag)
				{
					i = i - 1;//结点插入失败
					cout << "请重新输入一个结点：";
				}
			}
			cout << "创造的结点分别为：";
			G->outputVertex();
			cout << endl;
			flag++;
			break;
		case 'B':
			if (n <= 1)
			{
				cout << "结点数不足以构造边！" << endl;
				cout << endl;
				break;
			}
			//B
			cout << "请添加边：(以？终止)" << "(最多添加" << n * (n - 1) / 2 << "条边）:";
			cin >> n1 >> n2 >> l;
			while (n1 != "?" && n2 != "?")
			{
				v1 = G->getNum(n1);
				v2 = G->getNum(n2);
				if (v1 == -1 || v2 == -1)
				{
					cout << "请添加边：(以？终止)" << "(最多添加" << n * (n - 1) / 2 << "条边）" << endl;
					cin >> n1 >> n2 >> l;
					continue;
				}
				G->insertEdge(v1, v2, l);
				cout << "建立的边为：" << G->getValue(v1) << "-" << G->getValue(v2) << " " << G->getWeight(v1, v2) << endl;
				edgecount = G->NumberOfEdges();
				if (edgecount == n * (n - 1) / 2)break;
				cout << "请添加边：(以？终止)" << "(最多添加" << n * (n - 1) / 2 << "条边）:";
				cin >> n1 >> n2 >> l;
			}
			cout << endl;
			flag++;
			break;
		case 'C':
			//C
			if (flag < 2)
			{
				cout << "当前无法建立最小生成树" << endl;
				break;
			}
			cout << "请输入要建立最小生成树的顶点:";
			cin >> node;
			//先检查该结点是否存在
			while (G->getNum(node) == -1)
			{
				cout << "请重新输入要建立最小生成树的顶点";
				cin >> node;
			}
			G->Prim(node, tree);
			cout << "生成Prim最小生成树！" << endl;
			cout << endl;
			break;
		case 'D':
			//D
			if (tree->getSize() != n - 1)
			{
				cout << "当前未生成最小生成树！" << endl;
				break;
			}
			G->output(tree);
			cout << endl;
			break;
		default:
			cout << "输入错误！" << endl;
			break;
		}
		cout << "请选择操作:";
		cin >> op;
	}

	return 0;
}