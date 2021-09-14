#include<iostream>
#include<string>
using namespace std;

//�ڽӱ�
#define MAXNUM 100000
template<class T>
struct Edge {//�߽��Ķ���
	int dest;//�ߵ���һ���
	double cost;//���ϵ�Ȩֵ
	Edge<T>* link;//��һ������ָ��
	Edge() {}//���캯��
	Edge(int num = -1, double weight = 0) :dest(num), cost(weight), link(NULL) {}//���캯��
};

template<class T>
struct Vertex {//����Ķ���
	T data;//���������
	Edge<T>* adj;//�������ͷָ��
	Vertex() :adj(NULL) {}
};

//��С������
struct MSTEdgeNode {//�������߽���ඨ��
	int tail, head;//���������ߵ�������
	double cost;//���������ߵĴ���
	MSTEdgeNode(int mtail = -1, int mhead = -1, double mcost = 0) :tail(mtail), head(mhead), cost(mcost) {}
	bool operator <=(MSTEdgeNode& r) { return cost <= r.cost; }
	bool operator>(MSTEdgeNode& r) { return cost > r.cost; }
};

class MinSpanTree
{
	//���������ඨ��
public:
	MinSpanTree(int sz = 0) :MaxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[MaxSize];
	}
	~MinSpanTree() { delete[]edgevalue; }
	void Insert(MSTEdgeNode& item)//��item�ӵ���С��������
	{
		if (n < MaxSize)
		{
			edgevalue[n] = item;
			n++;
		}
	}
	int getSize() { return n; }
	MSTEdgeNode getEdgeNode(int x)//�õ�x���������߽��
	{
		if (x >= 0 && x < n)return edgevalue[x];
		else
		{
			cout << "�ý�㲻���ڣ�" << endl;
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
	MSTEdgeNode* edgevalue;//��ֵ����
	int MaxSize, n; //������,��ǰ����
};

template<class T>
class Graph {
private:
	Vertex<T>* NodeTable;//��������������ͷ��㣩
	int getVertex(const T vertex)
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == vertex)return i;
		}
		return -1;
	}//��������vertex��ͼ�е�λ��
	int numVertices;//��ǰ������
	int numEdges;//��ǰ����
	int maxVertices;//��󶥵���
public:
	Graph(int sz = 0);//���캯��
	~Graph();//��������
	T getValue(int i)
	{
		if (i >= 0 && i < numVertices)
		{
			return NodeTable[i].data;
		}
		else
			return "0";
	}//ȡλ��Ϊi�Ķ����е�ֵ
	double getWeight(int v1, int v2);//���رߣ�v1��v2���ϵ�Ȩֵ
	bool insertVertex(const T& vertex);//��ͼ�в���һ������vertex
	bool insertEdge(int v1, int v2, double cost);//��ͼ�в���һ���ߣ�v1��v2��
	int getFirstNeighbor(int v);//ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);//ȡv���ڽӶ���w����һ�ڽӶ���
	int NumberOfVertices() { return numVertices; }//���ص�ǰ������
	int NumberOfEdges() { return numEdges; }//���ص�ǰ����
	int getNum(T& name)
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (name == NodeTable[i].data)return i;
		}
		cout << name << "�����ڣ�" << endl;
		return -1;
	}
	void Prim(T& x, MinSpanTree* MST);//prim�㷨������xΪ�������С������
	void output(MinSpanTree* x);//��ӡ��С������
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
		cout << "�洢����ʧ�ܣ�" << endl;
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
{//�������رߣ�v1��v2���ϵ�Ȩֵ�����ñ߲���ͼ�У���������Ȩֵ0
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
	return MAXNUM;//�ߣ�v1��v2��������
}

template<class T>
bool Graph<T>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices)
	{
		cout << "��������!" << endl;
		return false;
	}//�������������ܲ���
	for (int i = 0; i < numVertices; i++)
	{
		if (NodeTable[i].data == vertex)
		{
			cout << vertex << "�Ѵ��ڣ�" << endl;
			return false;
		}//������ͬ���㣬���ܲ���
	}
	NodeTable[numVertices].data = vertex;//�����ڱ�����
	numVertices++;
	return true;
}

template<class T>
bool Graph<T>::insertEdge(int v1, int v2, double cost)
{
	//��ͼ�в���һ���ߣ�v1��v2����ȨֵΪcost�����˱ߴ��ڻ������������������false�����򷵻�true
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)//�ж�v1��v2�Ƿ���ͼ��
	{
		Edge<T>* p = NodeTable[v1].adj;
		Edge<T>* q;
		while (p != NULL && p->dest != v2)//Ѱ���Ƿ���ڣ�v1��v2��
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
			p = new Edge<T>(v2, cost);//��v1�в���v2
			q = new Edge<T>(v1, cost);//��v2�в���v1
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
	//��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������1
	if (v >= 0 && v < numVertices)//����v����
	{
		Edge<T>* p = NodeTable[v].adj;//��Ӧ������ĵ�һ���߽��
		if (p != NULL)return p->dest;//���ڣ����ص�һ���ڽӶ���
	}
	return -1;//�����ڣ�����-1
}

template<class T>
int Graph<T>::getNextNeighbor(int v, int w)
{
	//��������v���ڽӶ���w����һ���ڽӶ����λ�ã���û����һ���ڽӶ��㣬��������-1
	if (v >= 0 && v < numVertices && w >= 0 && w < numVertices)//����v��w����
	{
		Edge<T>* p = NodeTable[v].adj;//��Ӧ������ĵ�һ���߽��
		while (p != NULL && p->dest != w)//Ѱ���ڽӶ���w
		{
			p = p->link;
		}
		if (p->dest == NULL)
		{
			cout << NodeTable[v].data << "��" << NodeTable[w].data << "�����ڱ�" << endl;//����v�Ͷ���w�����ڱ�
			return -1;
		}
		else if (p->link != NULL)return p->link->dest;//������һ���ڽӶ���
	}
	return -1;//��һ��
}


template<class T>
void Graph<T>::Prim(T& x, MinSpanTree* MST)
{
	MST->MakeEmpty();
	int num = getNum(x);//numΪx��λ��
	double* lowcost = new double[numVertices];//������������㼯���ڶ��㵽�������������ĸ����ϵĵ�ǰ��СȨֵ��
	int* nearvex = new int[numVertices];//��¼���������㼯�����������뼯�����ĸ��������((��Ȩֵ��С))��
	for (int i = 0; i < numVertices; i++)
	{
		lowcost[i] = getWeight(num, i); //����x�����ߵĴ���
		nearvex[i] = num;//����̴�Ȩ·��
	}
	nearvex[num] = -1; //����x�ӵ����������㼯��
	MSTEdgeNode e; //��С��������㸨����Ԫ
	for (int i = 1; i < numVertices; i++)//ѭ��n-1��, ����n-1����
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
			//���������ⶥ�㵽�������ڶ��������С
			//Ȩֵ�ı�, v�ǵ�ǰ����СȨֵ�ıߵ�λ��
		}
		if (v != num)  //v==num��ʾ��Ҳ�Ҳ���Ҫ�󶥵���
		{
			e.tail = v;
			e.head = nearvex[v];
			e.cost = lowcost[v];
			MST->Insert(e); //ѡ���ı߼���������
			nearvex[v] = -1; //���ñ��Ѽ������������
			for (int j = 0; j < numVertices; j++)
				if (nearvex[j] != -1 &&// j ������������
					getWeight(v, j) < lowcost[j])//��Ҫ�޸�
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
	int head, tail;//��С������һ���ߵ���ʼ����š���ֹ�����
	double cost;;//��С������һ���ߵ�Ȩֵ
	cout << "��С������Ϊ��";
	for (int i = 0; i < x->getSize(); i++)
	{
		head = x->getEdgeNode(i).head;//��С������һ���ߵ���ʼ�����
		tail = x->getEdgeNode(i).tail;//��С������һ���ߵ���ֹ�����
		cost = x->getEdgeNode(i).cost;//��С������һ���ߵ�Ȩֵ
		cout << getValue(head) << "-<" << cost << ">->" << getValue(tail);
		if (i != x->getSize() - 1)cout << " ";
	}
	cout << endl;
}

int main()
{
	cout << "**          �������ģ��ϵͳ          **" << endl;
	cout << "----------------------------------------" << endl;
	cout << "**          A---����������          **" << endl;
	cout << "**          B---��ӵ����ı�          **" << endl;
	cout << "**          C---������С������        **" << endl;
	cout << "**          D---��ʾ��С������        **" << endl;
	cout << "**          E---�˳�����              **" << endl;
	cout << "----------------------------------------" << endl;
	cout << endl;
	char op;//������
	int n = 0;//������
	string node;//�������
	string n1, n2;//��������
	int v1, v2;//������Ķ����
	double l;//Ȩֵ
	int edgecount = 0;//��¼����
	int verflag = 0;//��¼������
	int flag = 0;//��¼A��B����
	MinSpanTree* tree = nullptr;
	Graph<string>* G = nullptr;
	cout << "��ѡ�����:";
	cin >> op;
	while (op != 'E')
	{
		switch (op)
		{
		case 'A':
			if (flag >= 1)
			{
				cout << "�Ѵ����㣡��������ӽ�㣡" << endl;
				cout << endl;
				break;
			}
			cout << "�������������";
			cin >> n;
			if (n <= 0)
			{
				cout << "�������������" << endl;
				break;
			}
			tree = new MinSpanTree(n - 1);
			G = new Graph<string>(n);
			cout << "�������������㣺";
			for (int i = 0; i < n; i++)
			{
				cin >> node;
				verflag = G->insertVertex(node);
				if (!verflag)
				{
					i = i - 1;//������ʧ��
					cout << "����������һ����㣺";
				}
			}
			cout << "����Ľ��ֱ�Ϊ��";
			G->outputVertex();
			cout << endl;
			flag++;
			break;
		case 'B':
			if (n <= 1)
			{
				cout << "����������Թ���ߣ�" << endl;
				cout << endl;
				break;
			}
			//B
			cout << "����ӱߣ�(�ԣ���ֹ)" << "(������" << n * (n - 1) / 2 << "���ߣ�:";
			cin >> n1 >> n2 >> l;
			while (n1 != "?" && n2 != "?")
			{
				v1 = G->getNum(n1);
				v2 = G->getNum(n2);
				if (v1 == -1 || v2 == -1)
				{
					cout << "����ӱߣ�(�ԣ���ֹ)" << "(������" << n * (n - 1) / 2 << "���ߣ�" << endl;
					cin >> n1 >> n2 >> l;
					continue;
				}
				G->insertEdge(v1, v2, l);
				cout << "�����ı�Ϊ��" << G->getValue(v1) << "-" << G->getValue(v2) << " " << G->getWeight(v1, v2) << endl;
				edgecount = G->NumberOfEdges();
				if (edgecount == n * (n - 1) / 2)break;
				cout << "����ӱߣ�(�ԣ���ֹ)" << "(������" << n * (n - 1) / 2 << "���ߣ�:";
				cin >> n1 >> n2 >> l;
			}
			cout << endl;
			flag++;
			break;
		case 'C':
			//C
			if (flag < 2)
			{
				cout << "��ǰ�޷�������С������" << endl;
				break;
			}
			cout << "������Ҫ������С�������Ķ���:";
			cin >> node;
			//�ȼ��ý���Ƿ����
			while (G->getNum(node) == -1)
			{
				cout << "����������Ҫ������С�������Ķ���";
				cin >> node;
			}
			G->Prim(node, tree);
			cout << "����Prim��С��������" << endl;
			cout << endl;
			break;
		case 'D':
			//D
			if (tree->getSize() != n - 1)
			{
				cout << "��ǰδ������С��������" << endl;
				break;
			}
			G->output(tree);
			cout << endl;
			break;
		default:
			cout << "�������" << endl;
			break;
		}
		cout << "��ѡ�����:";
		cin >> op;
	}

	return 0;
}