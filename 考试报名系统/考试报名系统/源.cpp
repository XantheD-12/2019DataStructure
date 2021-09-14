#include<iostream>
#include<string>
using namespace std;

class List;
class ListNode {
	friend class List;
	string number;//����
	string name;//����
	string sex;//�Ա�
	string age;//����
	string sort;//��������
	//�������
	ListNode* link; //�������ָ��
public:
	ListNode(); //�����㹹�캯��
	ListNode(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort);//�����㹹�캯��

};


ListNode::ListNode() : link(NULL) { }

ListNode::ListNode(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort) :
	number(m_number), name(m_name), sex(m_sex), age(m_age), sort(m_sort), link(NULL) { }

class List {
	ListNode* first, * last;
	int length;//����Ԫ�ظ���
public:
	List() {
		first = last = new ListNode;
		length = 0;
	}
	List(const string& m_number, const string& m_name, const string& m_sex, const string& m_age, const string& m_sort, const int& m_length)
	{
		last = first = new ListNode(m_number, m_name, m_sex, m_age, m_sort);
		length = m_length;
	} //���캯��
	~List() { MakeEmpty(); delete first, last; } //��������

	void MakeEmpty(); //�����ÿ�
	int Length() const; //��������
	ListNode* getHead()const { return first; }//���ظ���ͷ����ַ
	ListNode* Search(string x)const;//�������Ϊx��Ԫ��
	bool find();//���Ҳ���
	bool getData()const;//ȡֵ
	void setData();//�޸�ֵ
	bool Insert();//����
	bool Remove();//ɾ��ֵ
	bool IsEmpty()const { return first->link == NULL ? true : false; }//�жϱ�շ񣿿��򷵻�true
	void output();//���
	void inputRear();//��巨
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

int List::Length()const
{
	ListNode* p = first->link;//���ָ��pָʾ��һ�����
	int count = 0;
	while (p != NULL)//��������
	{
		p = p->link;
		count++;
	}
	return count;
}

ListNode* List::Search(string x)const//����������x��Ԫ��
{
	//�ڱ�������������x�Ľ�㣬�����ɹ�ʱ�������ظý���ַ�����򷵻�NULLֵ
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
	cout << "��������Ҫ���ҵĿ�������:";
	cin >> x;
	ListNode* p = Search(x);
	if (p == NULL) {
		cout << "δ���ҵ��ÿ�������������!" << endl;
		return false;
	}
	else
	{
		cout << "���ҵ���ϢΪ��";
		cout << p->number << " ";
		cout << p->name << " ";
		cout << p->sex << " ";
		cout << p->age << " ";
		cout << p->sort << " ";
		cout << endl;
		return true;

	}
}

bool List::getData()const//ȡ����i��Ԫ�ص�ֵ
{
	string x;//Ҫȡ���ı��
	//if (i <= 0)return NULL;
	cout << "����������ҿ����Ŀ���:";
	cin >> x;
	ListNode* current = Search(x);
	if (current == NULL)
	{
		cout << "����Ŀ�������!" << endl;
		return false;
	}
	else
	{
		cout << current->number;
		cout << current->name;
		cout << current->sex;
		cout << current->age;
		cout << current->sort;//�������������ֵ
		return true;
	}
}

void List::setData()//�޸�
{
	string x;//Ҫ�޸ĵı��
	string m_number;
	string m_name;
	string m_sex;
	string m_age;
	string m_sort;
	cout << "��������Ҫ�޸ĵı��:" ;
	cin >> x;
	//if (i <= 0)return;
	ListNode* current = Search(x);
	if (current == NULL)
	{
		cout << "�ÿ��������ڣ���������!" << endl;
		return;
	}
	else
	{
		cout << "���������뿼�����š��������Ա����䡢�������" << endl;
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
	string x;//Ҫ�����λ��
	string m_number;
	string m_name;
	string m_sex;
	string m_age;
	string m_sort;
	ListNode* p = first->link;
	cout << "��������Ҫ�����λ��:";
	cin >> x;
	ListNode* current = Search(x);

	if (current == NULL)
	{
		cout << "�ò���λ�ò�����!" << endl;
		return false;//���벻�ɹ�
	}
	else
	{
		cout << "���������뿼�����š��������Ա����䡢�������" << endl;
		cin >> m_number;
		cin >> m_name;
		cin >> m_sex;
		cin >> m_age;
		cin >> m_sort;
	}
	ListNode* newNode = new ListNode(m_number, m_name, m_sex, m_age, m_sort);
	if (newNode == NULL)
	{
		cout << "�洢�������" << endl;
		exit(-1);
	}
	newNode->link = current->link;//������current֮��
	current->link = newNode;
	length++;
	return true;//����ɹ�
}

bool List::Remove()
{
	string x;//Ҫɾ���ı��
	cout << "��������Ҫɾ������Ϣ:";
	cin >> x;
	ListNode* current = first->link;
	ListNode* prior = first;
	int flag = 0;
	while ((flag == 0) && (current != NULL))
	{
		if (current == Search(x))
		{
			flag = 1;
			length--;//���ȼ�һ
			prior->link = current->link;
			cout << "��Ҫɾ������Ϣ�ǣ�";
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
	cout << "δ���ҵ������Ա���������룡" << endl;
	return false;
}

void List::output()//���
{
	cout << "����" << "	";
	cout << "����" << "	";
	cout << "�Ա�" << "	";
	cout << "����" << "	";
	cout << "�������" << endl;
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

void List::inputRear()//��巨
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
			cout << "�洢�������" << endl;
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
	cout << "�뽨����Ϣ��" << endl;
	cout << "�����뽨������������";
	cin >> n;
	while (1)
	{	
		if (n > 0)break;
		cout << "�����������������������������" << endl;
		cout << "�����뽨������������";
		cin >> n;
	}
	List number("", "", "", "", "", n);
	cout << "���������뿼�����š��������Ա����䡢�������" << endl;
	number.inputRear();
	cout << "��������Ϣ��Ϊ��" << endl;
	number.output();
	cout << endl;
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊ�˳���:";
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
			cout << "����ѡ�����!" << endl;
			break; 
		}
		}

		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊ�˳���:";
		cin >> optionnumber;
	}
	return 0;
}