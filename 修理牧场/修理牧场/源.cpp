#include<iostream>
#include<string>
using namespace std;

//修理牧场
//利用优先级队列建立堆
  
//最小优先级队列
template<class Type>
class PQueue {
public:
	PQueue(int sz);//构造函数
	~PQueue() { delete[]pqelements; }//析构函数
	bool Insert(const Type& x);//将新元素插入到队尾
	bool RemoveMin(Type& x);//将队头元素删去
	bool getFront(Type& x)const;//读取队头（具最小优先权）的值
	void makeEmpty() { count = 0; }//置优先级队列为空
	bool IsEmpty()const { return (count == 0) ? true : false; }//判断队列空否
	bool IsFull()const { return (count == maxSize) ? true : false; }//判断队列满否
	int getSize()const { return count; }//求优先级队列中元素个数
protected:
	Type* pqelements;//优先级队列数组
	int count;//当前元素个数（长度）
	int maxSize;//队列最大可容纳元素个数
	void adjust();//队列调整
};

template<class Type>
PQueue<Type>::PQueue(int sz) :maxSize(sz), count(0) {
	pqelements = new Type[maxSize];//创建队列空间
	//判断动态存储分配是否成功
	if (pqelements == NULL)
	{
		cout << "内存分配失败!" << endl;
	}
}

template<class Type>
bool PQueue<Type>::Insert(const Type& x)
{
	//若优先级队列不满，则将元素x插入到该队列的队尾，否则出错处理
	if (count == maxSize)
	{
		cout << "队列已满！" << endl;
		return false;
	}//队列已满则函数返回
	pqelements[count++] = x;//插入x到队尾
	adjust();//按优先权进行调整
	return true;
}

template<class Type>
void PQueue<Type>::adjust()
{
	//将队尾元素按其优先权大小调整到适当位置，保持所有元素按优先权从小到大有序
	Type temp = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--)
	{
		if (pqelements[j] <= temp)break;//发现有比temp更小或相等的pqelements[j]，跳出循环
		else pqelements[j + 1] = pqelements[j];//比temp大的元素pqelements[j]后移
	}
	pqelements[j + 1] = temp;//插入到适当位置
}

template<class Type>
bool PQueue<Type>::RemoveMin(Type& x)
{
	//若优先级队列不空则函数返回该队列具有最大优先权（值最小）元素的值，同时将该元素删除
	if (count == 0)
	{
		cout << "队列已空！" << endl;
		return false;//若队列空，函数返回
	}
	x = pqelements[0];
	for (int i = 1; i < count; i++)
	{
		pqelements[i - 1] = pqelements[i];
	}
	count--;//优先级队列元素个数减一
	return true;//删除成功，返回true
}

template<class Type>
bool PQueue<Type>::getFront(Type& x)const
{
	//若优先级队列不空则函数返回队列具有最小优先权元素的值
	if (count == 0)
	{
		cout << "" << endl;
		return false;//若队列空，函数返回
	}
	else
	{
		x = pqelements[0];
		return true;//返回具最小优先权元素的值
	}
}

int main()
{
	int n;//数组大小
	int* wood;//每段木头长度
	//cout << "请输入木头数量：";
	cin >> n;
	PQueue<int> length(n);
	int x;
	int x1;
	int x2;
	int sum=0;
	//cout << "请输入每段木头长度：";
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		length.Insert(x);
	}
	while (length.getSize() != 1)
	{
		length.RemoveMin(x1);
		length.RemoveMin(x2);
		x = x1 + x2;
		sum = sum+x;
		length.Insert(x);
	}
	cout << sum << endl;
	return 0;
}
