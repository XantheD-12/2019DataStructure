#include<iostream>
#include<vector>
#include<ctime>
#include <cstdlib>
using namespace std;

//ð������
//ѡ������
//ֱ�Ӳ�������
//ϣ������
//��������
//������
//�鲢����
//��������


class SortCompare {
private:

	vector<int> vex;//����������
public:
	string sort[9] = { "","ð������","ѡ������","ֱ�Ӳ�������","ϣ������","��������","������","�鲢����","��������" };
	SortCompare(int n)
	{
		//srand((int)time(0));
		//���������
		for (int i = 0; i < n; i++)
		{
			vex.push_back(rand());
		}
	}
	void test(int& op, double& time, long long& Exchange)
	{
		clock_t start = clock();
		switch (op)
		{
		case 1:
			BubbleSort(Exchange);
			break;
		case 2:
			ChooseSort(Exchange);
			break;
		case 3:
			InsertSort(Exchange);
			break;
		case 4:
			ShellSort(Exchange);
			break;
		case 5:
			QuickSort(Exchange);
			break;
		case 6:
			HeapSort(Exchange);
			break;
		case 7:
			MergeSort(Exchange);
			break;
		case 8:
			RadixSort(Exchange);
			break;
		default:
			break;
		}
		clock_t end = clock();
		time = ((double)end - (double)start)/ CLOCKS_PER_SEC;
	}
	void BubbleSort(long long& Exchange)
	{
		vector<int> temp(vex);
		int n = temp.size();
		for (int i = 1; i < n; i++)
		{
			int flag = 0;//����δ���н���
			for (int j = temp.size() - 1; j >= i; j--)
			{
				if (temp[j - 1] > temp[j])
				{
					swap(temp[j - 1], temp[j]);
					Exchange++;
					flag = 1;
				}
			}
			if (flag == 0)break;//ð��һ�Σ�δ���н��������������
		}
	}

	void ChooseSort(long long& Exchange)
	{
		vector<int> temp(vex);
		int n = temp.size();
		for (int i = 0; i < n - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < n; j++)
			{
				if (temp[min] > temp[j])
				{
					min = j;
				}
			}
			if (min != i)
			{
				swap(temp[i], temp[min]);
				Exchange++;
			}
		}
	}

	void InsertSort(long long& Exchange)
	{
		vector<int> temp = vex;
		int n = temp.size();
		for (int i = 1; i < n; i++)
		{
			for (int j = i; j > 0 && temp[j - 1] > temp[j]; j--)
			{
				swap(temp[j - 1], temp[j]);
				Exchange++;
			}
		}
	}

	void ShellSort(long long& Exchange)
	{
		vector<int>temp = vex;
		int n = temp.size();
		int gap = n / 2;
		while (gap)
		{
			for (int i = gap; i < n; i++)
			{
				for (int j = i; j >= gap && temp[j - gap] > temp[j]; j = j - gap)
				{
					swap(temp[j], temp[j - gap]);
					Exchange++;
				}
			}
			gap = gap == 2 ? 1 : (int)(gap / 2.2); //�޸�
		}
	}

	int Partition(vector<int>& temp, const int low, const int high, long long& Exchange)
	{
		int pivotpos = low; //��׼λ��
		int pivot = temp[low];
		for (int i = low + 1; i <= high; i++)
		{
			if (temp[i] < pivot && ++pivotpos != i)
			{
				swap(temp[pivotpos], temp[i]);
				Exchange++;
			} // С�ڻ�׼����Ľ�������������ȥ
		}
		if (low != pivotpos)//��׼λ�÷����ı�
		{
			swap(temp[low], temp[pivotpos]);
			Exchange++;
		}
		return pivotpos;
	}

	void QuickSort(vector<int>& temp, const int left, const int right, long long& Exchange)
	{
		if (left < right)
		{
			int pivotpos = Partition(temp, left, right, Exchange); //����
			QuickSort(temp, left, pivotpos - 1, Exchange);
			//����������ݹ���п�������
			QuickSort(temp, pivotpos + 1, right, Exchange);
			//����������ݹ���п�������
		}
	}

	void QuickSort(long long& Exchange)
	{
		vector<int> temp = vex;
		int n = temp.size();
		QuickSort(temp, 0, n - 1, Exchange);
	}

	void FilterDown(vector<int>& temp, const int start, const int EndOfHeap, long long& Exchange)
	{
		if (start > EndOfHeap)return;
		int current = start;
		int child = 2 * start + 1;
		while (child <= EndOfHeap)
		{
			if (child + 1 <= EndOfHeap && temp[child] < temp[child + 1])
			{
				child = child + 1;
			}
			if (temp[current] >= temp[child])break;
			else
			{
				swap(temp[current], temp[child]);
				Exchange++;
				current = child;
				child = 2 * child + 1;
			}
		}
	}//�������µ����㷨

	void HeapSort(long long& Exchange)
	{
		vector<int>temp = vex;
		int n = temp.size();
		//����ת���ɶ�
		for (int i = (n - 2) / 2; i >= 0; i--)
		{
			FilterDown(temp, i, n - 1, Exchange);
		}
		//���ж�����
		for (int i = n - 1; i >= 1; i--)
		{
			swap(temp[0], temp[i]);
			Exchange++;
			FilterDown(temp, 0, i - 1, Exchange);
		}
	}

	//�鲢���򲻽��н������������бȽϲ���
	void Merge(vector<int>& temp, vector<int>& aux, int left, int mid, int right, long long& Exchange)
	{
		for (int n = left; n <= right; n++)
		{
			aux[n] = temp[n];
		}
		int i = left;
		int j = mid + 1;
		int t = left;
		while (i <= mid && j <= right)
		{
			if (aux[i] < aux[j])
			{
				temp[t] = aux[i];
				t++;
				i++;
				Exchange++;
			}
			else
			{
				temp[t] = aux[j];
				t++;
				j++;
				Exchange++;
			}
		}
		if (i <= mid)
		{
			for (int n1 = t, n2 = i; n1 <= right && n2 <= mid; n1++, n2++)
			{
				temp[n1] = aux[n2];
			}
		}
		else
		{
			for (int n1 = t, n2 = j; n1 <= right && n2 <= right; n1++, n2++)
			{
				temp[n1] = aux[n2];
			}
		}
	}

	void MergeSort(vector<int>& temp, vector<int>& aux, int left, int right, long long& Exchange)
	{
		if (left >= right)return;
		int mid = (left + right) / 2;
		MergeSort(temp, aux, left, mid, Exchange);
		MergeSort(temp, aux, mid + 1, right, Exchange);
		Merge(temp, aux, left, mid, right, Exchange);
	}

	void MergeSort(long long& Exchange)
	{
		vector<int>temp = vex;
		int n = temp.size();
		vector<int>aux(n);//��������
		MergeSort(temp, aux, 0, n - 1, Exchange);
	}

	int getlength(vector<int>& temp)//���vector��Ԫ�ص����λ��
	{
		int length = 1;
		int base = 10;
		int n = temp.size();
		for (int i = 0; i < n; i++)
		{
			while (base <= temp[i])
			{
				base = base * 10;
				length++;
			}
		}
		return length;
	}

	void RadixSort(long long& Exchange)
	{
		vector<int>temp = vex;
		vector<int>aux = vex;

		int n = temp.size();
		int length = getlength(temp);//temp��Ԫ�ص����λ��
		int base = 1;
		for (int i = 0; i < length; i++)
		{
			vector<int>count(11);//0-9λ����λ�ж��ٸ�Ԫ��
			for (int j = 0; j < n; j++)
			{
				int r = (temp[j] / base) % 10;
				count[r + 1]++;
			}
			for (int j = 0; j < 10; j++)
			{
				count[j + 1] = count[j + 1] + count[j];
			}//��¼0-9λ��ʼ�����λ��
			for (int j = 0; j < n; j++)
			{
				int r = (temp[j] / base) % 10;
				aux[count[r]] = temp[j];
				count[r]++;
			}//��ʼ����
			for (int j = 0; j < n; j++)
			{
				temp[j] = aux[j];
			}
			base = base * 10;
		}
	}

	void swap(int& a, int& b)
	{
		int temp = b;
		b = a;
		a = temp;
	}
};

int main()
{
	cout << "**          �����㷨�Ƚ�          **" << endl;
	cout << "====================================" << endl;
	cout << "**          1---ð������          **" << endl;
	cout << "**          2---ѡ������          **" << endl;
	cout << "**          3---ֱ�Ӳ�������      **" << endl;
	cout << "**          4---ϣ������          **" << endl;
	cout << "**          5---��������          **" << endl;
	cout << "**          6---������            **" << endl;
	cout << "**          7---�鲢����          **" << endl;
	cout << "**          8---��������          **" << endl;
	cout << "**          9---�˳�����          **" << endl;
	cout << "====================================" << endl;
	int n;//���������
	long long exchange = 0;
	double time = 0;
	char op;
	cout << "�����������������";
	cin >> n;
	while (n <= 0)
	{
		cout << "��������벻����" << endl;
		cout << "���������������������";
		cin >> n;
	}
	SortCompare sort(n);
	cout << endl;
	cout << "��ѡ�������㷨��";
	cin >> op;
	int opnum = op - 48;
	while (opnum != 9)
	{
		sort.test(opnum, time, exchange);
		if (op != 7)
		{
			cout << sort.sort[opnum] << "����������" << exchange << endl;
			cout << sort.sort[opnum] << "����ʱ�䣺" << time << endl;
			cout << endl;
		}
		else
		{
			cout << sort.sort[opnum] << "�Ƚϴ�����" << exchange << endl;
			cout << sort.sort[opnum] << "����ʱ�䣺" << time << endl;
			cout << endl;
		}
		exchange = 0;
		time = 0;
		cout << "��ѡ�������㷨��";
		cin >> op;
		opnum = op - 48;
	}

	return 0;
}