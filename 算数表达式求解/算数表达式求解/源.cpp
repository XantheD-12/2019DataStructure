#include<iostream>
#include<string>
using namespace std;

class Stack;
class StackNode {
	friend class Stack;
private:
	int data;
	StackNode* link;
	StackNode(int d = 0, StackNode* l = NULL) :data(d), link(l) {}
};

class Stack {
public:
	Stack() :top(NULL) {}
	~Stack();
	void Push(const int& item);
	int Pop();
	int GetTop();
	void MakeEmpty();
	int IsEmpty()const { return top == NULL; }
private:
	StackNode* top;
};

Stack::~Stack()
{
	StackNode* p;
	while (top != NULL)
	{
		p = top;
		top = top->link;
		delete p;
	}
}

void Stack::MakeEmpty()
{
	StackNode* p;
	while (top != NULL)
	{
		p = top;
		top = top->link;
		delete p;
	}
}

void Stack::Push(const int& item)
{
	top = new StackNode(item, top);
	//�½������top֮ǰ������Ϊ��ջ��
}

int Stack::Pop()
{
	if (IsEmpty())
	{
		cout << "ջ�ѿգ�" << endl;
		return -1;
	}
	StackNode* p = top;
	int retvalue = p->data;
	top = top->link;
	delete p;
	return retvalue;
}

int Stack::GetTop()
{
	if (IsEmpty())
	{
		cout << "ջ�ѿգ�" << endl;
		return -1;
	}
	return top->data;
}

int isp(char a)
{
	if ('=' == a)
	{
		return 0;
	}
	else if ('(' == a)
	{
		return 1;
	}
	else if ('+' == a || '-' == a)
	{
		return 3;
	}
	else if ('*' == a || '/' == a || '%' == a)
	{
		return 5;
	}
	else if ('^' == a)
	{
		return 7;
	}
	else if (')' == a)
	{
		return 8;
	}
	return -1;
}//ջ��������

int icp(char a)
{
	if ('=' == a)
	{
		return 0;
	}
	else if ('(' == a)
	{
		return 8;
	}
	else if ('+' == a || '-' == a)
	{
		return 2;
	}
	else if ('*' == a || '/' == a || '%' == a)
	{
		return 4;
	}
	else if ('^' == a)
	{
		return 6;
	}
	else if (')' == a)
	{
		return 1;
	}
	return -1;
}//ջ��������

int pow(int x, int y)
{
	if (y == 0)return 1;
	else if (y == 1) return x;
	int temp = pow(x, y / 2);
	if (0 == y % 2)
	{
		return temp * temp;
	}
	else
	{
		return x * temp * temp;
	}
}

int abs0(int x)
{
	if (x >= 0) return x;
	return 0-x;
}

bool isvalid(char*str)
{
	int length = strlen(str);
	int opnum = 0;//���ŵ�����
	/*���¾���ͨ��ѭ���鿴���ʽÿһ���ַ����жϱ��ʽ�Ƿ�������漸����������Ϸ���
	�������Ӧ����ʾ��Ϣ�����Һ�������false����ʾ���ʽ����ֱ�����е������������ˣ��ŷ���true��
	��Ҫ���ѶȾ��Ƕԣ��������Ե��жϣ�����ͨ����������������ж��Ƿ��Ǻ���ı��ʽ���磺��������
	�߶�û���������ţ���⵽�������ź��ڸô���ߵ����������������������������Լ�������������֮��û�ж����ȡ�
    ��󣬵�����Ϊ��Ŀ�����������˫Ŀ��������������Ҳ��Ҫ���бȽ�ϸ�µķ������ۡ��ٶ�������������������Ƿ����*/
	for (int i = 0; i < length; i++)
	{
		//�ж�����ĺϷ��ԣ����������ַ����ڲ������Լ���������Χ�򱨴�
		if ('+'!=str[i]&& '-' != str[i]&&'*' != str[i]&& '/' != str[i]&& '%' != str[i]&& '^' != str[i]&& '=' != str[i]
			&& '(' != str[i]&& ')' != str[i]&&!(str[i]>='0'&&str[i]<='9'))
		{
			cout << "���ʽ���зǷ��ַ����������룡" << endl;
			return false;
		}
		if (str[length-1] != '=')
		{
			cout << "���ʽȱ�١�=�����������룡" << endl;
			return false;
		}
		if (i != length - 1 && str[i] == '=')
		{
			cout << "���ʽ�г��֡�=�����������룡" << endl;
			return false;
		}
		//�ж����ŵ���ȷ��
		if (str[i] == '(')
		{
			if (opnum < 0)
			{
				cout << "���ʽ��(���롰)����ƥ�䣬�������룡" << endl;
				return false;
			}
			opnum++;
		}
		if (str[i] == ')')
		{
			opnum--;
		}
		if(str[i] == '(' && str[i + 1] == ')')
		{
			cout << "���ʽ�г�����Ч��()�����������룡" << endl;
			return false;
		}
		//�ж�+��-
		if (str[i] == '+' || str[i] == '-')
		{
			if (i == 0 || str[i - 1] == '(')//Ϊ��Ŀ�����
				//Ϊ��Ŀ������������1.���ʽ��ͷ��2.ǰһ�������ǡ�(��
			{
				if(i+1<length&&(str[i+1]=='('|| (str[i+1] >= '0' && str[i+1] <= '9')))
				{ }
				else
				{
					cout << "���ʽ�д��ڴ����������룡" << endl;
					return false;
				}
			}
			else if (i + 1 < length && (str[i-1]==')'||(str[i-1] >= '0' && str[i-1] <= '9'))&&
				(str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))//Ϊ˫Ŀ�����
			{

			}
			else
			{
				cout << "���ʽ�д��ڲ�����ġ�+������-�����������룡" << endl;
				return false;
			}
		}

		//�ж�˫Ŀ���������ȷ��
		if (str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^')
		{
			if (i-1>=0&&i + 1 < length && (str[i - 1] == ')' || (str[i - 1] >= '0' && str[i - 1] <= '9')) &&
				(str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))
			{ }
			else
			{
				cout << "���ʽ���ڲ�������������*����/����%����^�����������룡" << endl;
				return false;
			}
		}

	}
	if (opnum)
	{
		cout << "���ʽ��(���롰)����ƥ�䣬�������룡" << endl;
		return false;
	}
	return true;
}//�ж������Ƿ�Ϸ�

bool culculate(int N,char*str)
{
	Stack a;//��ֵջ
	Stack b;//������
	char x;
	int temp;
	int a1, a2;//�ݴ��ջ�е����Ĳ�����
	int y;//�ݴ������
	int numflag = 0;//��¼��������Ĳ���������
	int num = 0;//�洢��λ��

	//�ж��Ƿ�Ϊ��Ŀ�����+/-
	//���������
	//1.�����ٱ��ʽ�ʼ��λ��
	//2.��һ���ַ�Ϊ'('�Ĳ�����
	char op = 0;//�洢��Ŀ�����
	int opflag = 0;//��¼�Ƿ�Ϊ��Ŀ�������-��������Ϊ1
	if (N && isvalid(str))
	{
		for (int i = 0; i < N; )
		{
			x = str[i];
			if (x >= 48 && x <= 57)
			{
				if (opflag)
				{
					a.Push(48 - x);
					//cout << 48 - x;//���
					i++;
					opflag = 0;
				}
				else
				{
					a.Push(x - 48);
					//cout << x;//���
					i++;
				}
				numflag++;
			}//ɨ�赽�������֣�ֱ��ѹ��ջ
			else//ɨ����ǲ�����
			{
				//��Ŀ����������
				if (i == 0)
				{
					if (x == '-')
					{
						op = x;
						i++;
						opflag = 1;
						continue;
					}
					else//'+'��Ӱ��
					{
						i++;
						continue;
					}
				}
				else if (str[i - 1] == '(' && (x == '-' || x == '+'))
				{
					if (x == '-')
					{
						op = x;
						i++;
						opflag = 1;
						continue;
					}
					else
					{
						i++;
						continue;
					}
				}
				if (numflag > 1)
				{
					for (int j = 0; j < numflag; j++)
					{
						int bit = a.Pop();
						if (bit < 0)opflag = 1;
						num = num + abs0(bit) * pow(10, j);
					}
					if (opflag)a.Push(0 - num);
					else a.Push(num);
					opflag = 0;
					num = 0;
				}//���������Ƕ�λ�����м�λ�ʹ�ջ�е��������������ѹ��ջ
				numflag = 0;
				if (b.IsEmpty() || icp(x) > isp(b.GetTop()))
				{
					b.Push(x);
					i++;
				}//���ջΪ�ջ��߲�������ջ�����������ȼ�����ѹ��ջ
				else if (icp(x) < isp(b.GetTop()))
				{
					temp = b.Pop();
					//cout << char(temp);
					//��ջ��������
					switch (temp)
					{
					case '+':
						a1 = a.Pop();
						a2 = a.Pop();
						y = a1 + a2;
						a.Push(y);
						break;
					case '-':
						a1 = a.Pop();
						a2 = a.Pop();
						y = a2 - a1;
						a.Push(y);
						break;
					case '*':
						a1 = a.Pop();
						a2 = a.Pop();
						y = a2 * a1;
						a.Push(y);
						break;
					case '/':
						a1 = a.Pop();
						a2 = a.Pop();
						y = a2 / a1;
						a.Push(y);
						break;
					case '%':
						a1 = a.Pop();
						a2 = a.Pop();
						y = a2 % a1;
						a.Push(y);
						break;
					case '^':
						a1 = a.Pop();
						a2 = a.Pop();
						y = pow(a2, a1);
						a.Push(y);
						break;
					default:break;
					}
				}
				else//���ȼ���ͬ
				{
					if (b.Pop() == '(')
					{
						i++;
					}
				}

			}
		}
		//cout << endl;
		cout << a.Pop();
		cout << endl;
		return true;
	}
	return false;
}

int main()
{
	//�������ȼ��ǵ���<����<�Ӽ�<�˳�ȡ��<�˷�
	//0-9(48-57)
	//+(43)
	//-(45)
	//*(42)
	///(47)
	//^(94)
	//%(37)
	//((40)
	//)(41)
	//=(61)

	int N;
	char str[100];
	char go;
	int flag=0;
	for (int i = 0; i < 100; i++)
	{
		str[i] = '\0';
	}
	while (true)
	{
		cout << "��������ʽ��" << endl;
		cin >> str;
		N = strlen(str);
		culculate(N, str);
		cout << "�Ƿ������y,n��?��yΪ������nΪ�˳���" << endl;
		cin >> go;
		if ('y' == go)continue;
		else if ('n' == go)break;
		else
		{
			cout << "��������Զ��˳���" << endl;
			break;
		}		
	}
	return 0;
}