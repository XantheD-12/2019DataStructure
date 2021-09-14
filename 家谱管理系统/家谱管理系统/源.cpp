#include<iostream>
#include<string>
using namespace std;

//���׽���
//���Ľ���

template<class Type>class Tree;
template<class Type>
class Node {
	friend class Tree<Type>;
private:
	Type data;
	Node<Type>* next;//�ֵ�
	Node<Type>* link;//��һ����Ů
public:
	Node(Type m_data) :data(m_data), next(nullptr), link(nullptr) {}
};

template<class Type>
class Tree
{
	//����Ŀ��ʵ������ɶҼ��׳�Ա��Ϣ�Ľ���
	//���ң����룬�޸ģ�ɾ��������
private:
	Node<Type>* root, * current;
	void Find(Node<Type>* p, Type target);//����pΪ������������tatget,�ҵ�����ý���Ϊ��ǰ��㣬����ǰ��㲻��
public:
	Tree() { root = current = NULL; }
	void add(Type x);//�������
	void add(Type father, Type x);//��Ӽ�ͥ��Ա
	void Delete(Type famliyname); //ɾ����pΪ��������
	void update(Type name, Type newname);//���ļ�ͥ��Ա����
	void output(Type name);//���
	bool IsEmpty() { return root == NULL; }//�ж����Ƿ�Ϊ�գ���Ϊ���򷵻�1
	Type Getroot()
	{
		current = root;
		return current->data;
	}
	bool Find(Type name);
	bool Isvalid(Type name);//���ֺ�����0����������1
};

template<class Type>
void Tree<Type>::Find(Node<Type>* p, Type target)
{
	if (p == NULL)
	{
		return;
	}
	if (p->data == target)
	{
		current = p;
		return;
	}
	Find(p->link, target);
	for (Node<Type>* temp = p->next; temp != NULL; temp = temp->next)
	{
		Find(temp, target);
	}
}

template<class Type>
void Tree<Type>::add(Type x)
{
	root = new Node<Type>(x);
}

template<class Type>
void Tree<Type>::add(Type father, Type x)
{
	Node<Type>* temp = new Node<Type>(x);
	current = NULL;//��ʼ����currentΪ��
	Find(root, father);//�ҵ����׽��,current����Ϊ���׽��
	if (current == NULL || current->data == "-1")
	{
		cout << "�ü�ͥ�����ڣ��������룡" << endl;
		return;
	}//�����ͥ�����ڵĴ�����
	Node<Type>* curChild = current->link;
	if (curChild == NULL)
	{
		curChild = temp;
		current->link = curChild;
	}

	else {
		while (curChild->next != NULL)
		{
			curChild = curChild->next;
		}//�����һ�������ǿվ��˳�ѭ����������ǿյľ�������ú��ӵ��ֵܣ�ֱ�������պ���
		curChild->next = temp;
	}
}

template<class Type>
void Tree<Type>::Delete(Type famliyname)
{
	current = NULL;
	Find(root, famliyname);
	if (current == NULL || current->data == "-1")
	{
		cout << " �ü�ͥ�����ڣ��������룡" << endl;
		return;
	}
	current->data = "-1";
	//����ó�Ա�ļ�ͥ
	current = current->link;
	while (current != NULL)
	{
		Node<Type>* x = current;
		while (current != NULL)
		{
			current->data = "-1";
			current = current->next;
		}
		current = x->link;
	}
}

template<class Type>
void Tree<Type>::update(Type name, Type newname)
{
	current = NULL;
	Find(root, name);
	if (current == NULL || current->data == "-1")
	{
		cout << " �ü�ͥ�����ڣ��������룡" << endl;
		return;
	}
	Node<Type>* cur = current;
	cur->data = newname;
}

template<class Type>
void Tree<Type>::output(Type name)
{
	int n = 0;//��Ů����
	current = NULL;
	Find(root, name);
	if (current == NULL || current->data == "-1")
	{
		cout << " �ü�ͥ�����ڣ��������룡 " << endl;
		return;
	}
	for (Node<Type>* x = current->link; x != NULL; x = x->next)
	{
		if (x->data != "-1")
		{
			n++;
			cout << x->data;
			if (x->next != NULL)
			{
				cout << " ";
			}
		}
	}
	if (0 == n)
	{
		cout << "��";
	}
	cout << endl;
}

template<class Type>
bool Tree<Type>::Find(Type name)
{
	current = NULL;
	Find(root, name);
	if (current == NULL || current->data == "-1")
	{
		cout << "�ü�ͥ��Ա�����ڣ�" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

template<class Type>
bool Tree<Type>::Isvalid(Type name)
{
	current = NULL;
	Find(root, name);
	if (current == NULL || current->data == "-1")
	{
		return 0;
	}
	else
	{
		cout << "�����ظ����֣�" << endl;
		return 1;
	}
}

int main()
{

	cout << "**          ���׹���ϵͳ          **" << endl;
	cout << "=====================================" << endl;
	cout << "**          ��ѡ��Ҫִ�еĲ���    **" << endl;
	cout << "**          A---���Ƽ���          **" << endl;
	cout << "**          B---��Ӽ�ͥ��Ա      **" << endl;
	cout << "**          C---��ɢ�ֲ���ͥ      **" << endl;
	cout << "**          D---���ļ�ͥ��Ա����  **" << endl;
	cout << "**          E---���Ҽ�ͥ��Ա      **" << endl;
	cout << "**          F---�˳�����          **" << endl;
	cout << "=====================================\t" << endl;

	Tree<string> family;
	string fathername;//��������
	string name;//��Ů����
	string newname;//������
	int num;//��Ů����
	cout << "�����뽨��һ�����ף�" << endl;
	cout << "���������ȵ�������";
	cin >> fathername;
	family.add(fathername);
	cout << "�˼��׵�����Ϊ��" << family.Getroot() << endl;
	cout << endl;
	//ִ�в���
	char op;
	cout << "��ѡ��Ҫִ�еĲ���:";
	cin >> op;
	while (op != NULL)
	{
		switch (op)
		{
		case 'A'://���Ƽ���
			cout << "������Ҫ������ͥ���˵�������";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//�жϸü�ͥ��Ա�Ƿ����
			cout << "������" << fathername << "����Ů������";
			cin >> num;
			cout << "������������Ů��������";
			for (int i = 0; i < num; i++)
			{
				cin >> name;				
				if(!family.Isvalid(name))
				{
					family.add(fathername, name);
				}
			}
			cout << fathername << "�ĵ�һ����ŮΪ";
			family.output(fathername);
			cout << endl;
			break;
		case'B'://��Ӽ�ͥ��Ա
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//�жϸü�ͥ��Ա�Ƿ����
			//��Ҫ�ж�������ͬ��Ա��
			cout << "������" << fathername << "����Ӷ��ӣ���Ů������������";
			cin >> name;
			if (!family.Isvalid(name))//�������������Ӷ��ӣ���Ů����
			{
				family.add(fathername, name);
				cout << fathername << "�ĵ�һ����Ů��";
				family.output(fathername);
			}		
			cout << endl;
			break;
		case'C'://��ɢ�ֲ���ͥ
			cout << "������Ҫ��ɢ��ͥ���˵�������";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//�жϸü�ͥ��Ա�Ƿ����
			
			cout << "Ҫ��ɢ�ļ�ͥΪ��" << fathername<<endl;
			cout << fathername << "�ĵ�һ����ŮΪ";
			family.output(fathername);
			family.Delete(fathername);
			cout << endl;
			break;
		case'D'://���ļ�ͥ��Ա����
			cout << "������Ҫ�����������˵�ԭ������";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//�жϸü�ͥ��Ա�Ƿ����
			cout << "��������ĺ��������";
			cin >> newname;
			if (!family.Isvalid(newname))//�����������,����������ͬ������
			{
				family.update(fathername, newname);
				cout <<fathername<< "�Ѹ���Ϊ" <<newname<< endl;
			}
			cout << endl;
			break;
		case'E'://���Ҽ�ͥ��Ա
			cout << "������Ҫ���ҵ��˵�������";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//�жϸü�ͥ��Ա�Ƿ����
			//��Ҫ�ж�������ͬ��Ա��
			cout << fathername << "�ĵ�һ����Ů:";
			family.output(fathername);
			cout << endl;
			break;
		case'F'://�˳����� 
			cout << endl;
			return 0;
			break;
		default:
			cout << "�������" << endl;
			cout << endl;
			break;
		}
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin >> op;
	}
	return 0;
}