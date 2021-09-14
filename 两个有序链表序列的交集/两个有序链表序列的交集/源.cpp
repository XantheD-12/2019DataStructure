#include<iostream>
using namespace std;

#include<iostream>
#include<string>
using namespace std;

class List;
class ListNode {
	friend class List;
	int data; //结点数据
	ListNode* link; //结点链接指针
public:
	ListNode(); //链表结点构造函数
	ListNode(const int& item);
};


ListNode::ListNode() : data(-1),link(NULL) { }

ListNode::ListNode(const int& item) :
	data(item), link(NULL) { }

class List {
	ListNode* first, * last;
	int length;
public:
	List() { first = last = new ListNode; length = 0; }
	List(const int& value) { last = first = new ListNode(value); length = 0; } //构造函数
	~List() { MakeEmpty(); delete first, last; } //析构函数
	void MakeEmpty(); //链表置空
	bool IsEmpty()const { return first->link == NULL ? true : false; }//判断表空否？空则返回true
	void output();//输出
	void inputRear(int endTag);//后插法
	List& operator*(List& s2);
};

void List::MakeEmpty()
{
	ListNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;//将表头结点后第一个结点从链中摘下
		delete q;//释放它
	}
	last = first;//修改表尾指针
}

void List::output()//输出
{
	ListNode* current = first->link;
	if (current == NULL)
	{
		cout << "NULL" << endl;;
		return;
	}

	while (current != NULL)
	{
		cout << current->data;
		if (current->link != NULL)cout << " ";
		current = current->link;
	}
	cout << endl;
}


void List::inputRear(int endTag)//后插法
{
	ListNode* newNode;
	int val;
	MakeEmpty();
	cin >> val;
	while (val != endTag)
	{
		length++;
		newNode = new ListNode(val);
		if (newNode == NULL)
		{
			cout << "存储分配错误！" << endl;
			exit(-1);
		}
		last->link = newNode;
		last = newNode;
		cin >> val;
		last->link = NULL;
	}
}

List& List::operator* (List& s2)
{
	ListNode* p1 = first->link;
	ListNode* p2 = s2.first->link;
	ListNode* p = first;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->data == p2->data)
		{
			p1 = p1->link;
			p2 = p2->link;
			p = p->link;
		}
		else if (p1->data < p2->data)
		{
			p->link = p1->link;
			delete p1;
			p1 = p->link;
		}
		else
		{
			p2 = p2->link;
		}
	}
	while (p1 != NULL) {
		p->link = p1->link;
		delete p1;
		p1 = p->link;
	}
	last = p;
	return *this;
}

int main()
{
	cout << "请建立数字链表，以-1为截止符" << endl;
	int end = -1;
	List number1;
	number1.inputRear(end);
	List number2;
	number2.inputRear(end);
	//cout << "建立的链表为：" << endl;
	//number1.output();
	//number2.output();
	cout << "交集为：" << endl;
	number1 = number1 * number2;
	number1.output();
	return 0;
}