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
	//新结点链入top之前，并成为新栈顶
}

int Stack::Pop()
{
	if (IsEmpty())
	{
		cout << "栈已空！" << endl;
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
		cout << "栈已空！" << endl;
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
}//栈内优先数

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
}//栈外优先数

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
	int opnum = 0;//括号的数量
	/*大致就是通过循环查看表达式每一个字符来判断表达式是否符合上面几条，如果不合法，
	就输出对应的提示信息，并且函数返回false，表示表达式有误，直到所有的条件都满足了，才返回true。
	主要的难度就是对（）合理性的判断，于是通过许多条件限制来判断是否是合理的表达式，如：左括号右
	边都没出现右括号；检测到了右括号后，在该处左边的右括号数量大于左括号数量；以及左括号右括号之中没有东西等。
    随后，当±作为单目运算符，或者双目运算符的相关讨论也需要进行比较细致的分类讨论。再对其他运算符进行讨论是否合理。*/
	for (int i = 0; i < length; i++)
	{
		//判断输入的合法性，如果输入的字符不在操作符以及操作数范围则报错
		if ('+'!=str[i]&& '-' != str[i]&&'*' != str[i]&& '/' != str[i]&& '%' != str[i]&& '^' != str[i]&& '=' != str[i]
			&& '(' != str[i]&& ')' != str[i]&&!(str[i]>='0'&&str[i]<='9'))
		{
			cout << "表达式含有非法字符，请检查输入！" << endl;
			return false;
		}
		if (str[length-1] != '=')
		{
			cout << "表达式缺少“=”，请检查输入！" << endl;
			return false;
		}
		if (i != length - 1 && str[i] == '=')
		{
			cout << "表达式中出现“=”，请检查输入！" << endl;
			return false;
		}
		//判断括号的正确性
		if (str[i] == '(')
		{
			if (opnum < 0)
			{
				cout << "表达式“(”与“)”不匹配，请检查输入！" << endl;
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
			cout << "表达式中出现无效“()”，请检查输入！" << endl;
			return false;
		}
		//判断+、-
		if (str[i] == '+' || str[i] == '-')
		{
			if (i == 0 || str[i - 1] == '(')//为单目运算符
				//为单目运算符的情况：1.表达式开头，2.前一个符号是“(”
			{
				if(i+1<length&&(str[i+1]=='('|| (str[i+1] >= '0' && str[i+1] <= '9')))
				{ }
				else
				{
					cout << "表达式中存在错误，请检查输入！" << endl;
					return false;
				}
			}
			else if (i + 1 < length && (str[i-1]==')'||(str[i-1] >= '0' && str[i-1] <= '9'))&&
				(str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))//为双目运算符
			{

			}
			else
			{
				cout << "表达式中存在不合理的“+”、“-”，请检查输入！" << endl;
				return false;
			}
		}

		//判断双目运算符的正确性
		if (str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^')
		{
			if (i-1>=0&&i + 1 < length && (str[i - 1] == ')' || (str[i - 1] >= '0' && str[i - 1] <= '9')) &&
				(str[i + 1] == '(' || (str[i + 1] >= '0' && str[i + 1] <= '9')))
			{ }
			else
			{
				cout << "表达式存在不合理的运算符“*”或“/”或“%”或“^”，请检查输入！" << endl;
				return false;
			}
		}

	}
	if (opnum)
	{
		cout << "表达式“(”与“)”不匹配，请检查输入！" << endl;
		return false;
	}
	return true;
}//判断输入是否合法

bool culculate(int N,char*str)
{
	Stack a;//数值栈
	Stack b;//操作符
	char x;
	int temp;
	int a1, a2;//暂存从栈中弹出的操作数
	int y;//暂存计算结果
	int numflag = 0;//记录连续存入的操作数个数
	int num = 0;//存储多位数

	//判断是否为单目运算符+/-
	//共两种情况
	//1.出现再表达式最开始的位置
	//2.上一个字符为'('的操作符
	char op = 0;//存储单目运算符
	int opflag = 0;//记录是否为单目运算符“-”，是则为1
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
					//cout << 48 - x;//输出
					i++;
					opflag = 0;
				}
				else
				{
					a.Push(x - 48);
					//cout << x;//输出
					i++;
				}
				numflag++;
			}//扫描到的是数字，直接压入栈
			else//扫描的是操作符
			{
				//单目运算符的情况
				if (i == 0)
				{
					if (x == '-')
					{
						op = x;
						i++;
						opflag = 1;
						continue;
					}
					else//'+'无影响
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
				}//如果输入的是多位数，有几位就从栈中弹出进行运算后再压入栈
				numflag = 0;
				if (b.IsEmpty() || icp(x) > isp(b.GetTop()))
				{
					b.Push(x);
					i++;
				}//如果栈为空或者操作符比栈顶操作符优先级高则压入栈
				else if (icp(x) < isp(b.GetTop()))
				{
					temp = b.Pop();
					//cout << char(temp);
					//退栈并计算结果
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
				else//优先级相同
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
	//其中优先级是等于<括号<加减<乘除取余<乘方
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
		cout << "请输入表达式：" << endl;
		cin >> str;
		N = strlen(str);
		culculate(N, str);
		cout << "是否继续（y,n）?（y为继续，n为退出）" << endl;
		cin >> go;
		if ('y' == go)continue;
		else if ('n' == go)break;
		else
		{
			cout << "输入错误，自动退出！" << endl;
			break;
		}		
	}
	return 0;
}