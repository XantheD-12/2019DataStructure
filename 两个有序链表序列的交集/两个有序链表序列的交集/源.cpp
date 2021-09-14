#include<iostream>
using namespace std;

#include<iostream>
#include<string>
using namespace std;

class List;
class ListNode {
	friend class List;
	int data; //�������
	ListNode* link; //�������ָ��
public:
	ListNode(); //�����㹹�캯��
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
	List(const int& value) { last = first = new ListNode(value); length = 0; } //���캯��
	~List() { MakeEmpty(); delete first, last; } //��������
	void MakeEmpty(); //�����ÿ�
	bool IsEmpty()const { return first->link == NULL ? true : false; }//�жϱ�շ񣿿��򷵻�true
	void output();//���
	void inputRear(int endTag);//��巨
	List& operator*(List& s2);
};

void List::MakeEmpty()
{
	ListNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;//����ͷ�����һ����������ժ��
		delete q;//�ͷ���
	}
	last = first;//�޸ı�βָ��
}

void List::output()//���
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


void List::inputRear(int endTag)//��巨
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
			cout << "�洢�������" << endl;
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
	cout << "�뽨������������-1Ϊ��ֹ��" << endl;
	int end = -1;
	List number1;
	number1.inputRear(end);
	List number2;
	number2.inputRear(end);
	//cout << "����������Ϊ��" << endl;
	//number1.output();
	//number2.output();
	cout << "����Ϊ��" << endl;
	number1 = number1 * number2;
	number1.output();
	return 0;
}