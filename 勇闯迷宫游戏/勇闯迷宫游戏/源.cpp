#include<iostream>
#include <vector> 
using namespace std;

class Maze {
private:
	int Size;//�����Թ�ΪSize*Size��������
	int x1, y1;//�������
	int x2, y2;//��������
public:

};

bool isvalid(vector<vector<int>>& map, int n, int x1, int y1, int x2, int y2)//�ж��Թ��Ƿ����,������1����������0
{
	if (x1 < 0 || y1 < 0 || x1 >= n || y1 >=n)
	{
		cout << "�Թ���ڲ����Թ���Χ�ڣ�" << endl;
		return false;
	}
	else if (1 == map[x1][y1])
	{
		cout << "�Թ�������ò�����" << endl;
		return false;
	}
	else if (x2 < 0 || y2 < 0 || x2 >= n || y2 >=n)
	{
		cout << "�Թ����ڲ����Թ���Χ�ڣ�" << endl;
		return false;
	}
	else if (1 == map[x2][y2])
	{
		cout << "�Թ��������ò�����" << endl;
		return false;
	}
	else if (x1 == x2 && y1 == y2)
	{
		cout << "�Թ���ںͳ����غϣ�" << endl;
		return false;
	}
	return true;
}

template <class Type> class Node
{
public:

	Node(const Type& m_value, Node<Type>* m_link = NULL) : data(m_value), link(m_link) {}
	Node(Node<Type>* m_link = NULL) : link(m_link) {}

	Type data;
	Node<Type>* link;
};

template<class Type>
class Stack {
private:
	Node<Type>* top;
public:
	Stack() { top = NULL; }
	~Stack();
	void Push(const Type& data);
	Type Pop();
	Type GetTop();
	void MakeEmpty();
	bool IsEmpty() { return top == NULL; }// ջΪ���򷵻�1�����򷵻�0.
};

template<class Type>
Stack<Type>::~Stack()
{
	Node<Type>* p;
	while (top != NULL) //�������
	{
		p = top;
		top = top->link;
		delete p;
	}
}

template<class Type>
void Stack<Type>::MakeEmpty()
{
	Node<Type>* p;
	while (top != NULL) //�������
	{
		p = top;
		top = top->link;
		delete p;
	}
}

template<class Type>
void Stack<Type>::Push(const Type& data)
{
	top = new Node<Type>(data, top);
}

template<class Type>
Type Stack<Type>::Pop()
{
	if (IsEmpty())
	{
		//cout << "ջ�ѿ�" << endl;
		return -1;
	}
	Node<Type>* p = top;
	Type retvalue = p->data; //�ݴ�ջ������
	top = top->link;//�޸�ջ��ָ��
	delete p;
	return retvalue; //�ͷ�,��������
}

template <class Type>
Type Stack<Type>::GetTop()
{
	if (IsEmpty())
	{
		//cout << "ջ�ѿ�" << endl;
		return -1;
	}
	return top->ata;
}

void dfs(vector<vector<int>>& map, vector<vector<bool>>& mapflag, Stack<int>& path_x, Stack<int>& path_y, int i, int j, int x2, int y2, bool& pathflag)
{
	int x, y;
	path_x.Push(i);
	path_y.Push(j);
	int n = map.size();
	mapflag[i][j] = true;

	if (i == x2 && j == y2)//�ҵ��յ�λ��
	{
		pathflag = true;
		Stack<int> rpath_x;
		Stack<int> rpath_y;
		while (!path_x.IsEmpty())
		{
			x = path_x.Pop();
			y = path_y.Pop();
			rpath_x.Push(x);
			rpath_y.Push(y);
			map[x][y] = 2;
		}
		cout << " " << '\t';
		for (i = 0; i < n; i++)
		{
			cout << i << "��" << '\t';
		}
		cout << endl;
		for (i = 0; i < n; i++)
		{
			cout << i << "��" << '\t';
			for (j = 0; j < n; j++)
			{
				if (map[i][j] == 1)
				{
					cout << "#" << '\t';
				}
				else if (map[i][j] == 0)
				{
					cout << 0 << '\t';
				}
				else if (map[i][j] == 2)
				{
					cout << "X" << '\t';
				}
			}
			cout << endl;
			if (i < n - 1)cout << endl;
		}
		cout << "�Թ�·��Ϊ��";
		while (!rpath_x.IsEmpty())
		{
			cout << '<' << rpath_x.Pop() << ',' << rpath_y.Pop() << '>';
			if (!rpath_x.IsEmpty())cout << "->";
		}
		cout << endl;
		return;
	}
	if (i - 1 >= 0 && map[i - 1][j] == 0 && mapflag[i - 1][j] == 0)
	{
		dfs(map, mapflag, path_x, path_y, i - 1, j, x2, y2, pathflag);
	}
	if (i + 1 < n && map[i + 1][j] == 0 && mapflag[i + 1][j] == 0)
	{
		dfs(map, mapflag, path_x, path_y, i + 1, j, x2, y2, pathflag);
	}
	if (j - 1 >= 0 && map[i][j - 1] == 0 && mapflag[i][j - 1] == 0)
	{
		dfs(map, mapflag, path_x, path_y, i, j - 1, x2, y2, pathflag);
	}
	if (j + 1 < n && map[i][j + 1] == 0 && mapflag[i][j + 1] == 0)
	{
		dfs(map, mapflag, path_x, path_y, i, j + 1, x2, y2, pathflag);
	}
	path_x.Pop();
	path_y.Pop();
}

int main()
{
	int n;
	int x1, y1;//�Թ��Ĵ�С
	int x2, y2;
	bool pathflag = false;
	Stack<int> path_x, path_y;
	cout << "�������Թ��Ĵ�С��";
	while (1)
	{
		cin >> n;
		if (n < 2)
		{
			cout << "�Թ���С���ò��������������룺" ;
			continue;
		}
		else break;
	}
	vector<vector<int>>map(n, vector<int>(n, 1));//����һ�������洢���� int
	vector<vector<bool>>mapflag(n, vector<bool>(n, 0));//����һ�������洢���� �Ƿ���ʹ�
	cout << "�������Թ�����СΪ" <<n<<"X"<<n<<"):"<< endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				mapflag[i][j] = 1;
			}
		}
	}

	cout << "������������꣺";
	cin >> x1 >> y1;
	cout << "������������꣺";
	cin >> x2 >> y2;
	
	//��ӡ�Թ�
	if (isvalid(map, n, x1, y1, x2, y2))//�Թ����ú�����д��������������
	{
		cout << "�Թ���ͼ" << endl;
		cout << " " << '\t';
		for (int i = 0; i < n; i++)
		{
			cout << i << "��" << '\t';
		}
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << i << "��" << '\t';
			for (int j = 0; j < n; j++)
			{
				if (1 == map[i][j])
				{
					cout << "#" << '\t';
				}
				else
				{
					cout << map[i][j] << '\t';
				}
			}
			cout << endl;
			cout << endl;

		}
		dfs(map, mapflag, path_x, path_y, x1, y1, x2, y2, pathflag);
		if (pathflag == 0)
			cout << "������·����" << endl;
	}
	return 0;
}