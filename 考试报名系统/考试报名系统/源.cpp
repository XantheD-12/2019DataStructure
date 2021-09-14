#include<iostream>
#include<string>
using namespace std;

class List;
class ListNode {
	friend class List;
	string number;//考号
	string name;//姓名
	string sex;//性别
	string age;//年龄
	string sort;//报考种类
	//结点数据
	ListNode* link; //结点链接指针
public:
	ListNode(); //链表结点构造函数
	ListNode(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort);//链表结点构造函数

};


ListNode::ListNode() : link(NULL) { }

ListNode::ListNode(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort) :
	number(m_number), name(m_name), sex(m_sex), age(m_age), sort(m_sort), link(NULL) { }

class List {
	ListNode* first, * last;
	int length;//链表元素个数
public:
	List() {
		first = last = new ListNode;
		length = 0;
	}
	List(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort, const int& m_length)
	{
		last = first = new ListNode(m_number, m_name, m_sex, m_age, m_sort);
		length = m_length;
	} //构造函数
	~List() { MakeEmpty(); delete first, last; } //析构函数

	void MakeEmpty(); //链表置空
	int Length() const; //求链表长度
	ListNode* getHead()const { return first; }//返回附加头结点地址
	ListNode* Search(string x)const;//搜索编号为x的元素
	bool find();//查找操作
	bool getData()const;//取值
	void setData();//修改值
	bool Insert();//插入
	bool Remove();//删除值
	bool IsEmpty()const { return first->link == NULL ? true : false; }//判断表空否？空则返回true
	void output();//输出
	void inputRear();//后插法
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

int List::Length()const
{
	ListNode* p = first->link;//检测指针p指示第一个结点
	int count = 0;
	while (p != NULL)//逐个结点检测
	{
		p = p->link;
		count++;
	}
	return count;
}

ListNode* List::Search(string x)const//搜索含数据x的元素
{
	//在表中搜索含数据x的结点，搜索成功时函数返回该结点地址，否则返回NULL值
	ListNode* current = first->link;
	while (current != NULL)
	{
		if (current->number == x) break;
		else current = current->link;
	}
	return current;
}

bool List::find()
{
	string x;
	cout << "请输入你要查找的考生考号:";
	cin >> x;
	ListNode* p = Search(x);
	if (p == NULL) {
		cout << "未查找到该考生，请检查输入!" << endl;
		return false;
	}
	else
	{
		cout << "查找的信息为：";
		cout << p->number << " ";
		cout << p->name << " ";
		cout << p->sex << " ";
		cout << p->age << " ";
		cout << p->sort << " ";
		cout << endl;
		return true;

	}
}

bool List::getData()const//取出第i个元素的值
{
	string x;//要取出的编号
	//if (i <= 0)return NULL;
	cout << "请输入你查找考生的考号:";
	cin >> x;
	ListNode* current = Search(x);
	if (current == NULL)
	{
		cout << "输入的考号有误!" << endl;
		return false;
	}
	else
	{
		cout << current->number;
		cout << current->name;
		cout << current->sex;
		cout << current->age;
		cout << current->sort;//依次输出搜索的值
		return true;
	}
}

void List::setData()//修改
{
	string x;//要修改的编号
	string m_number;
	string m_name;
	string m_sex;
	string m_age;
	string m_sort;
	cout << "请输入你要修改的编号:" ;
	cin >> x;
	//if (i <= 0)return;
	ListNode* current = Search(x);
	if (current == NULL)
	{
		cout << "该考生不存在，请检查输入!" << endl;
		return;
	}
	else
	{
		cout << "请依次输入考生考号、姓名、性别、年龄、报考类别！" << endl;
		cin >> m_number;
		cin >> m_name;
		cin >> m_sex;
		cin >> m_age;
		cin >> m_sort;
		current->number = m_number;
		current->name = m_name;
		current->sex = m_sex;
		current->age = m_age;
		current->sort = m_sort;
	}
}

bool List::Insert()
{
	string x;//要插入的位置
	string m_number;
	string m_name;
	string m_sex;
	string m_age;
	string m_sort;
	ListNode* p = first->link;
	cout << "请输入你要插入的位置:";
	cin >> x;
	ListNode* current = Search(x);

	if (current == NULL)
	{
		cout << "该插入位置不存在!" << endl;
		return false;//插入不成功
	}
	else
	{
		cout << "请依次输入考生考号、姓名、性别、年龄、报考类别！" << endl;
		cin >> m_number;
		cin >> m_name;
		cin >> m_sex;
		cin >> m_age;
		cin >> m_sort;
	}
	ListNode* newNode = new ListNode(m_number, m_name, m_sex, m_age, m_sort);
	if (newNode == NULL)
	{
		cout << "存储分配错误！" << endl;
		exit(-1);
	}
	newNode->link = current->link;//链接在current之后
	current->link = newNode;
	length++;
	return true;//插入成功
}

bool List::Remove()
{
	string x;//要删除的编号
	cout << "请输入你要删除的信息:";
	cin >> x;
	ListNode* current = first->link;
	ListNode* prior = first;
	int flag = 0;
	while ((flag == 0) && (current != NULL))
	{
		if (current == Search(x))
		{
			flag = 1;
			length--;//长度减一
			prior->link = current->link;
			cout << "你要删除的信息是：";
			cout << current->number << " ";
			cout << current->name << " ";
			cout << current->sex << " ";
			cout << current->age << " ";
			cout << current->sort;
			cout << endl;
			delete current;
			return true;
		}
		else
		{
			current = current->link;
			prior = prior->link;
		}
	}
	cout << "未查找到相关人员，请检查输入！" << endl;
	return false;
}

void List::output()//输出
{
	cout << "考号" << "	";
	cout << "姓名" << "	";
	cout << "性别" << "	";
	cout << "年龄" << "	";
	cout << "报考类别" << endl;
	ListNode* current = first->link;
	while (current != NULL)
	{
		cout << current->number << "	";
		cout << current->name << "	";
		cout << current->sex << "	";
		cout << current->age << "	";
		cout << current->sort;
		//if (current->link != NULL) 
		cout << endl;
		current = current->link;
	}
}

void List::inputRear()//后插法
{
	ListNode* newNode;
	string m_number;
	string m_name;
	string m_sex;
	string m_age;
	string m_sort;
	MakeEmpty();
	for (int i = 0; i < length; i++)
	{
		cin >> m_number;
		cin >> m_name;
		cin >> m_sex;
		cin >> m_age;
		cin >> m_sort;
		newNode = new ListNode(m_number, m_name, m_sex, m_age, m_sort);
		if (newNode == NULL)
		{
			cout << "存储分配错误！" << endl;
			exit(-1);
		}
		last->link = newNode;
		last = newNode;
		last->link = NULL;
	}
}

int main()
{
	int n;
	char optionnumber='0';
	cout << "请建立信息库" << endl;
	cout << "请输入建立考生个数：";
	cin >> n;
	while (1)
	{	
		if (n > 0)break;
		cout << "考生人数输入错误！请输入正整数！" << endl;
		cout << "请输入建立考生个数：";
		cin >> n;
	}
	List number("", "", "", "", "", n);
	cout << "请依次输入考生考号、姓名、性别、年龄、报考类别！" << endl;
	number.inputRear();
	cout << "建立的信息库为：" << endl;
	number.output();
	cout << endl;
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出）:";
	cin >> optionnumber;
	while (optionnumber != '0')
	{
		switch (optionnumber)
		{
		case '1':
			number.Insert();
			cout << endl;
			number.output();
			break;
		case '2':number.Remove();
			cout << endl;
			number.output();
			break;
		case '3':
			number.find();
			cout << endl;
			number.output();
			break;
		case '4':number.setData();
			cout << endl;
			number.output();
			break;
		case '5':
			cout << endl;
			number.output();
			break;
		default:
		{
			cout << "操作选择错误!" << endl;
			break; 
		}
		}

		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出）:";
		cin >> optionnumber;
	}
	return 0;
}