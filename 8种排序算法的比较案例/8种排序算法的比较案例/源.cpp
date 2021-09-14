#include<iostream>
#include<vector>
#include<ctime>
#include <cstdlib>
using namespace std;

//冒泡排序
//选择排序
//直接插入排序
//希尔排序
//快速排序
//堆排序
//归并排序
//基数排序


class SortCompare {
private:

	vector<int> vex;//待排序数组
public:
	string sort[9] = { "","冒泡排序","选择排序","直接插入排序","希尔排序","快速排序","堆排序","归并排序","基数排序" };
	SortCompare(int n)
	{
		//srand((int)time(0));
		//生成随机数
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
			int flag = 0;//假设未进行交换
			for (int j = temp.size() - 1; j >= i; j--)
			{
				if (temp[j - 1] > temp[j])
				{
					swap(temp[j - 1], temp[j]);
					Exchange++;
					flag = 1;
				}
			}
			if (flag == 0)break;//冒泡一次，未进行交换，则排序完成
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
			gap = gap == 2 ? 1 : (int)(gap / 2.2); //修改
		}
	}

	int Partition(vector<int>& temp, const int low, const int high, long long& Exchange)
	{
		int pivotpos = low; //基准位置
		int pivot = temp[low];
		for (int i = low + 1; i <= high; i++)
		{
			if (temp[i] < pivot && ++pivotpos != i)
			{
				swap(temp[pivotpos], temp[i]);
				Exchange++;
			} // 小于基准对象的交换到区间的左侧去
		}
		if (low != pivotpos)//基准位置发生改变
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
			int pivotpos = Partition(temp, left, right, Exchange); //划分
			QuickSort(temp, left, pivotpos - 1, Exchange);
			//在左子区间递归进行快速排序
			QuickSort(temp, pivotpos + 1, right, Exchange);
			//在左子区间递归进行快速排序
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
	}//最大堆向下调整算法

	void HeapSort(long long& Exchange)
	{
		vector<int>temp = vex;
		int n = temp.size();
		//将表转换成堆
		for (int i = (n - 2) / 2; i >= 0; i--)
		{
			FilterDown(temp, i, n - 1, Exchange);
		}
		//进行堆排序
		for (int i = n - 1; i >= 1; i--)
		{
			swap(temp[0], temp[i]);
			Exchange++;
			FilterDown(temp, 0, i - 1, Exchange);
		}
	}

	//归并排序不进行交换操作，进行比较操作
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
		vector<int>aux(n);//辅助数组
		MergeSort(temp, aux, 0, n - 1, Exchange);
	}

	int getlength(vector<int>& temp)//获得vector中元素的最大位数
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
		int length = getlength(temp);//temp中元素的最大位数
		int base = 1;
		for (int i = 0; i < length; i++)
		{
			vector<int>count(11);//0-9位，各位有多少个元素
			for (int j = 0; j < n; j++)
			{
				int r = (temp[j] / base) % 10;
				count[r + 1]++;
			}
			for (int j = 0; j < 10; j++)
			{
				count[j + 1] = count[j + 1] + count[j];
			}//记录0-9位开始排序的位置
			for (int j = 0; j < n; j++)
			{
				int r = (temp[j] / base) % 10;
				aux[count[r]] = temp[j];
				count[r]++;
			}//开始排序
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
	cout << "**          排序算法比较          **" << endl;
	cout << "====================================" << endl;
	cout << "**          1---冒泡排序          **" << endl;
	cout << "**          2---选择排序          **" << endl;
	cout << "**          3---直接插入排序      **" << endl;
	cout << "**          4---希尔排序          **" << endl;
	cout << "**          5---快速排序          **" << endl;
	cout << "**          6---堆排序            **" << endl;
	cout << "**          7---归并排序          **" << endl;
	cout << "**          8---基数排序          **" << endl;
	cout << "**          9---退出程序          **" << endl;
	cout << "====================================" << endl;
	int n;//随机数个数
	long long exchange = 0;
	double time = 0;
	char op;
	cout << "请输入随机数个数：";
	cin >> n;
	while (n <= 0)
	{
		cout << "随机数输入不合理！" << endl;
		cout << "请重新输入随机数个数：";
		cin >> n;
	}
	SortCompare sort(n);
	cout << endl;
	cout << "请选择排序算法：";
	cin >> op;
	int opnum = op - 48;
	while (opnum != 9)
	{
		sort.test(opnum, time, exchange);
		if (op != 7)
		{
			cout << sort.sort[opnum] << "交换次数：" << exchange << endl;
			cout << sort.sort[opnum] << "所用时间：" << time << endl;
			cout << endl;
		}
		else
		{
			cout << sort.sort[opnum] << "比较次数：" << exchange << endl;
			cout << sort.sort[opnum] << "所用时间：" << time << endl;
			cout << endl;
		}
		exchange = 0;
		time = 0;
		cout << "请选择排序算法：";
		cin >> op;
		opnum = op - 48;
	}

	return 0;
}