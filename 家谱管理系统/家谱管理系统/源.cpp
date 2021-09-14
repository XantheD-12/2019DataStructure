#include<iostream>
#include<string>
using namespace std;

//家谱建立
//树的建立

template<class Type>class Tree;
template<class Type>
class Node {
	friend class Tree<Type>;
private:
	Type data;
	Node<Type>* next;//兄弟
	Node<Type>* link;//第一个子女
public:
	Node(Type m_data) :data(m_data), next(nullptr), link(nullptr) {}
};

template<class Type>
class Tree
{
	//本项目的实质是完成兑家谱成员信息的建立
	//查找，插入，修改，删除，更改
private:
	Node<Type>* root, * current;
	void Find(Node<Type>* p, Type target);//在以p为根的树中搜索tatget,找到后令该结点成为当前结点，否则当前结点不变
public:
	Tree() { root = current = NULL; }
	void add(Type x);//添加祖先
	void add(Type father, Type x);//添加家庭成员
	void Delete(Type famliyname); //删除以p为根的子树
	void update(Type name, Type newname);//更改家庭成员姓名
	void output(Type name);//输出
	bool IsEmpty() { return root == NULL; }//判断树是否为空，若为空则返回1
	Type Getroot()
	{
		current = root;
		return current->data;
	}
	bool Find(Type name);
	bool Isvalid(Type name);//名字合理返回0，不合理返回1
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
	current = NULL;//初始设置current为空
	Find(root, father);//找到父亲结点,current现在为父亲结点
	if (current == NULL || current->data == "-1")
	{
		cout << "该家庭不存在！请检查输入！" << endl;
		return;
	}//输入家庭不存在的错误处理
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
		}//如果第一个孩子是空就退出循环，如果不是空的就逐个检查该孩子的兄弟，直至遇见空孩子
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
		cout << " 该家庭不存在！请检查输入！" << endl;
		return;
	}
	current->data = "-1";
	//处理该成员的家庭
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
		cout << " 该家庭不存在！请检查输入！" << endl;
		return;
	}
	Node<Type>* cur = current;
	cur->data = newname;
}

template<class Type>
void Tree<Type>::output(Type name)
{
	int n = 0;//子女总数
	current = NULL;
	Find(root, name);
	if (current == NULL || current->data == "-1")
	{
		cout << " 该家庭不存在！请检查输入！ " << endl;
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
		cout << "无";
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
		cout << "该家庭成员不存在！" << endl;
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
		cout << "存在重复名字！" << endl;
		return 1;
	}
}

int main()
{

	cout << "**          家谱管理系统          **" << endl;
	cout << "=====================================" << endl;
	cout << "**          请选择要执行的操作    **" << endl;
	cout << "**          A---完善家谱          **" << endl;
	cout << "**          B---添加家庭成员      **" << endl;
	cout << "**          C---解散局部家庭      **" << endl;
	cout << "**          D---更改家庭成员姓名  **" << endl;
	cout << "**          E---查找家庭成员      **" << endl;
	cout << "**          F---退出程序          **" << endl;
	cout << "=====================================\t" << endl;

	Tree<string> family;
	string fathername;//父亲名字
	string name;//子女名字
	string newname;//新名字
	int num;//子女数量
	cout << "首先请建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	cin >> fathername;
	family.add(fathername);
	cout << "此家谱的祖先为：" << family.Getroot() << endl;
	cout << endl;
	//执行操作
	char op;
	cout << "请选择要执行的操作:";
	cin >> op;
	while (op != NULL)
	{
		switch (op)
		{
		case 'A'://完善家谱
			cout << "请输入要建立家庭的人的姓名：";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//判断该家庭成员是否存在
			cout << "请输入" << fathername << "的子女个数：";
			cin >> num;
			cout << "请依次输入子女的姓名：";
			for (int i = 0; i < num; i++)
			{
				cin >> name;				
				if(!family.Isvalid(name))
				{
					family.add(fathername, name);
				}
			}
			cout << fathername << "的第一代子女为";
			family.output(fathername);
			cout << endl;
			break;
		case'B'://添加家庭成员
			cout << "请输入要添加儿子（或女儿）的人的姓名：";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//判断该家庭成员是否存在
			//需要判断输入相同成员吗？
			cout << "请输入" << fathername << "新添加儿子（或女儿）的姓名：";
			cin >> name;
			if (!family.Isvalid(name))//名字输入合理，添加儿子（或女儿）
			{
				family.add(fathername, name);
				cout << fathername << "的第一代子女：";
				family.output(fathername);
			}		
			cout << endl;
			break;
		case'C'://解散局部家庭
			cout << "请输入要解散家庭的人的姓名：";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//判断该家庭成员是否存在
			
			cout << "要解散的家庭为：" << fathername<<endl;
			cout << fathername << "的第一代子女为";
			family.output(fathername);
			family.Delete(fathername);
			cout << endl;
			break;
		case'D'://更改家庭成员姓名
			cout << "请输入要更改姓名的人的原姓名：";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//判断该家庭成员是否存在
			cout << "请输入更改后的姓名：";
			cin >> newname;
			if (!family.Isvalid(newname))//名字输入合理,不能输入相同的名字
			{
				family.update(fathername, newname);
				cout <<fathername<< "已更改为" <<newname<< endl;
			}
			cout << endl;
			break;
		case'E'://查找家庭成员
			cout << "请输入要查找的人的姓名：";
			cin >> fathername;
			if (!family.Find(fathername))
			{
				cout << endl;
				break;
			}//判断该家庭成员是否存在
			//需要判断输入相同成员吗？
			cout << fathername << "的第一代子女:";
			family.output(fathername);
			cout << endl;
			break;
		case'F'://退出程序 
			cout << endl;
			return 0;
			break;
		default:
			cout << "输入错误！" << endl;
			cout << endl;
			break;
		}
		cout << "请选择要执行的操作:";
		cin >> op;
	}
	return 0;
}