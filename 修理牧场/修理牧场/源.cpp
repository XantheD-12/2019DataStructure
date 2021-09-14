#include<iostream>
#include<string>
using namespace std;

//��������
//�������ȼ����н�����
  
//��С���ȼ�����
template<class Type>
class PQueue {
public:
	PQueue(int sz);//���캯��
	~PQueue() { delete[]pqelements; }//��������
	bool Insert(const Type& x);//����Ԫ�ز��뵽��β
	bool RemoveMin(Type& x);//����ͷԪ��ɾȥ
	bool getFront(Type& x)const;//��ȡ��ͷ������С����Ȩ����ֵ
	void makeEmpty() { count = 0; }//�����ȼ�����Ϊ��
	bool IsEmpty()const { return (count == 0) ? true : false; }//�ж϶��пշ�
	bool IsFull()const { return (count == maxSize) ? true : false; }//�ж϶�������
	int getSize()const { return count; }//�����ȼ�������Ԫ�ظ���
protected:
	Type* pqelements;//���ȼ���������
	int count;//��ǰԪ�ظ��������ȣ�
	int maxSize;//������������Ԫ�ظ���
	void adjust();//���е���
};

template<class Type>
PQueue<Type>::PQueue(int sz) :maxSize(sz), count(0) {
	pqelements = new Type[maxSize];//�������пռ�
	//�ж϶�̬�洢�����Ƿ�ɹ�
	if (pqelements == NULL)
	{
		cout << "�ڴ����ʧ��!" << endl;
	}
}

template<class Type>
bool PQueue<Type>::Insert(const Type& x)
{
	//�����ȼ����в�������Ԫ��x���뵽�ö��еĶ�β�����������
	if (count == maxSize)
	{
		cout << "����������" << endl;
		return false;
	}//����������������
	pqelements[count++] = x;//����x����β
	adjust();//������Ȩ���е���
	return true;
}

template<class Type>
void PQueue<Type>::adjust()
{
	//����βԪ�ذ�������Ȩ��С�������ʵ�λ�ã���������Ԫ�ذ�����Ȩ��С��������
	Type temp = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--)
	{
		if (pqelements[j] <= temp)break;//�����б�temp��С����ȵ�pqelements[j]������ѭ��
		else pqelements[j + 1] = pqelements[j];//��temp���Ԫ��pqelements[j]����
	}
	pqelements[j + 1] = temp;//���뵽�ʵ�λ��
}

template<class Type>
bool PQueue<Type>::RemoveMin(Type& x)
{
	//�����ȼ����в����������ظö��о����������Ȩ��ֵ��С��Ԫ�ص�ֵ��ͬʱ����Ԫ��ɾ��
	if (count == 0)
	{
		cout << "�����ѿգ�" << endl;
		return false;//�����пգ���������
	}
	x = pqelements[0];
	for (int i = 1; i < count; i++)
	{
		pqelements[i - 1] = pqelements[i];
	}
	count--;//���ȼ�����Ԫ�ظ�����һ
	return true;//ɾ���ɹ�������true
}

template<class Type>
bool PQueue<Type>::getFront(Type& x)const
{
	//�����ȼ����в����������ض��о�����С����ȨԪ�ص�ֵ
	if (count == 0)
	{
		cout << "" << endl;
		return false;//�����пգ���������
	}
	else
	{
		x = pqelements[0];
		return true;//���ؾ���С����ȨԪ�ص�ֵ
	}
}

int main()
{
	int n;//�����С
	int* wood;//ÿ��ľͷ����
	//cout << "������ľͷ������";
	cin >> n;
	PQueue<int> length(n);
	int x;
	int x1;
	int x2;
	int sum=0;
	//cout << "������ÿ��ľͷ���ȣ�";
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
