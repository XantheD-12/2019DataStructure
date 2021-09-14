#include<iostream>
#include<string>
using namespace std;

//��ʽ�����ඨ��
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
	void MakeEmpty(); //ʵ����~Queue( )ͬ
	bool IsEmpty()const { return front == NULL; }
private:
	QueueNode<Type>* front, * rear; //����ָ��
};

template <class Type>
Queue<Type>::~Queue()
{
	//���е���������
	QueueNode<Type>* p;
	while (front != NULL) {//�������ͷ�
		p = front;
		front = front->link;
		delete p;
	}
}

template <class Type>
void Queue<Type>::MakeEmpty()
{
	//���е���������
	QueueNode<Type>* p;
	while (front != NULL) {//�������ͷ�
		p = front;
		front = front->link;
		delete p;
	}
}

template <class Type>
void Queue<Type>::EnQueue(const Type& item)
{
	//����Ԫ��item���뵽���еĶ�β
	if (front == NULL) //��, ������һ�����
	{
		front = rear = new QueueNode<Type>(item, NULL);
	}
	else//���в���, ����
	{
		rear = rear->link = new QueueNode<Type>(item, NULL);
	}
}

template <class Type>
Type Queue<Type>::DeQueue()
{//ɾȥ��ͷ��㣬�����ض�ͷԪ�ص�ֵ
	if (IsEmpty() == true)
	{
		cout << "�����ѿգ�" << endl;
		return -1;
	}//�жӿ�
	QueueNode<Type>* p = front;
	Type retvalue = p->data; //�����ͷ��ֵ
	front = front->link;//�¶�ͷ
	delete p;
	return retvalue;
}

template <class Type>
Type Queue<Type>::GetFront()
{//���Ӳ��գ��������ض�ͷԪ�ص�ֵ; ���ӿգ���������0
	if (IsEmpty() == true)
	{
		cout << "�����ѿգ�" << endl;
		return;
	}//�жӿ�
	return front->data;
}
int main()
{
	Queue<int> a, b;
	int N;
	cin >> N;
	if (N < 0)
	{
		cout << "��������" << endl;
		return -1;
	}
	int* str=new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> str[i];
		if (str[i] < 0)
		{
			cout << "��������" << endl;
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