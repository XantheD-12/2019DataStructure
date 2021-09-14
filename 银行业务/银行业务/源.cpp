#include<iostream>
#include<string>
using namespace std;

//链式队列类定义
template<class Type>class Queue;
template<class Type>class QueueNode {
	friend class Queue<Type>;
private:
	Type data;
	QueueNode<Type>* link;
	QueueNode(Type d = 0, QueueNode* l = NULL) :data(d), link(l) { }
};

template <class Type> class Queue {
public:
	Queue() : rear(NULL), front(NULL) { }
	~Queue();
	void EnQueue(const Type& item);
	Type DeQueue();
	Type GetFront();
	void MakeEmpty(); //实现与~Queue( )同
	bool IsEmpty()const { return front == NULL; }
private:
	QueueNode<Type>* front, * rear; //队列指针
};

template <class Type>
Queue<Type>::~Queue()
{
	//队列的析构函数
	QueueNode<Type>* p;
	while (front != NULL) {//逐个结点释放
		p = front;
		front = front->link;
		delete p;
	}
}

template <class Type>
void Queue<Type>::MakeEmpty()
{
	//队列的析构函数
	QueueNode<Type>* p;
	while (front != NULL) {//逐个结点释放
		p = front;
		front = front->link;
		delete p;
	}
}

template <class Type>
void Queue<Type>::EnQueue(const Type& item)
{
	//将新元素item插入到队列的队尾
	if (front == NULL) //空, 创建第一个结点
	{
		front = rear = new QueueNode<Type>(item, NULL);
	}
	else//队列不空, 插入
	{
		rear = rear->link = new QueueNode<Type>(item, NULL);
	}
}

template <class Type>
Type Queue<Type>::DeQueue()
{//删去队头结点，并返回队头元素的值
	if (IsEmpty() == true)
	{
		cout << "队列已空！" << endl;
		return -1;
	}//判队空
	QueueNode<Type>* p = front;
	Type retvalue = p->data; //保存队头的值
	front = front->link;//新队头
	delete p;
	return retvalue;
}

template <class Type>
Type Queue<Type>::GetFront()
{//若队不空，则函数返回队头元素的值; 若队空，则函数返回0
	if (IsEmpty() == true)
	{
		cout << "队列已空！" << endl;
		return;
	}//判队空
	return front->data;
}
int main()
{
	Queue<int> a, b;
	int N;
	cin >> N;
	if (N < 0)
	{
		cout << "输入有误！" << endl;
		return -1;
	}
	int* str=new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> str[i];
		if (str[i] < 0)
		{
			cout << "输入有误！" << endl;
			return -1;
		}
		if (str[i] % 2 == 0)
		{
			b.EnQueue(str[i]);
		}
		else
		{
			a.EnQueue(str[i]);
		}
	}
	while (!a.IsEmpty() || !b.IsEmpty())
	{
		if (!a.IsEmpty())
		{
			cout << a.DeQueue();
			if (!a.IsEmpty() || !b.IsEmpty()) cout << " ";
		}
		if (!a.IsEmpty())
		{
			cout << a.DeQueue();
			if (!a.IsEmpty()|| !b.IsEmpty()) cout << " ";
		}
		if (!b.IsEmpty())
		{
			cout << b.DeQueue();
			if (!a.IsEmpty() || !b.IsEmpty()) cout << " ";
		}
	}
	delete []str;
	return 0;
}