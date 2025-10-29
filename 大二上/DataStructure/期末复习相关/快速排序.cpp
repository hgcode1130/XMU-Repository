#define _CRT_SECURE_NO_WARNINGS 1
#include"range.h"

void arrPrint(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

//����
void InsertRange(int a[], int n)
{
	
	//����
	for (int i = 0; i < n - 1; i++)
	{
		//��λ��
		int end = i;
		int temp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > temp)
			{
				a[end + 1] = a[end];//�Ѵ���������ץ
				end--;//����ƶ�
			}
			else {
				break;
			}
		}
		//����
		a[end + 1] = temp;
		arrPrint(a, n);
	}
	
}
void Test1()
{
	int a[] = { 4 ,5, 7, 6, 3, 2, 1 };
	//arrPrint(a, sizeof(a) / sizeof(a[0]));
	InsertRange(a, sizeof(a) / sizeof(a[0]));
	//arrPrint(a, sizeof(a) / sizeof(a[0]));
}

//ϣ������
void ShellSort(int a[], int n)
{
	int gap=n;
	//��gap==1ʱ�ͽ���������������ֱ�Ӳ����������
	while (gap > 1) {
		gap = gap/3+1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			while (end >= 0) {
				int temp = a[end + gap];

				if (a[end] > temp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}

				a[end + gap] = temp;
			}
		}
	}

}
void Test2()
{
	int a[] = { 4 ,5, 7, 6, 3, 2, 1 };
	arrPrint(a, sizeof(a) / sizeof(a[0]));
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	arrPrint(a, sizeof(a) / sizeof(a[0]));
}

//������
void Swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void AdjustDown(int a[], int size, int root)
{
	int parent = root;
	int child = 2*parent + 1;//Ĭ��Ϊ��child
	while (child < size)
	{
		//�����Һ��Ӵ����һ��
		//child+1<size�Ƿ�ֹû�С�����
		if (child + 1 < size && a[child] < a[child + 1])
		{
			child += 1;
		}
		if (a[child] > a[parent])
		{
			Swap(a + child, a + parent);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//������
void HeapSort(int a[], int size)
{
	//����

	for (int i = (size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, size, i);
	}
	arrPrint(a, size);
	//����
	//����һ���������һ����(end)�Ի���Ȼ���ٶ�ǰend������0Ϊroot�������µ���

	int end = size - 1;
	while (end>0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
	arrPrint(a, size);
}

void Test3()
{
	int a[] = { 1,5,6,3,2,4,8,4,5,6 };
	HeapSort(a, sizeof(a) / sizeof(a[0]));
}
//ֱ��ѡ������
void SelectSort(int a[], int size)
{
	int begin = 0, end = size - 1;
	while (begin < end)
	{
		int mini = begin;
		int maxi = end;
		for (int i = begin; i < end; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;	
			}
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
		}
		Swap(a + begin, a + mini);
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(a + end, a + maxi);
		end--;
		begin++;
	}
}
void Test4()
{
	int a[] = { 9,5,6,3,2,4,8,4,5,6 };
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	arrPrint(a, sizeof(a) / sizeof(a[0]));
}

int PartSort1(int a[], int left, int right)
{
	int begin = left, end = right;
	int pivot = begin;
	int key = a[begin];
	while (begin < end)
	{
		//�ұ���С
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		//���
		a[pivot] = a[end];
		pivot = end;
		//����Ҵ�
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		//�ſ�
		a[pivot] = a[begin];
		pivot = begin;
	}
	//���
	pivot = begin;
	a[pivot] = key;
	return pivot;
}

void QuickSort(int a[], int left,int right)
{
	if (left >= right)
	{
		return;
	}
	int keyindex = PartSort1(a, left, right);
	//�ݹ���������
	QuickSort(a, left, keyindex - 1);
	QuickSort(a, keyindex + 1, right);;
}

void Test5()
{
	int a[] = { 9,5,6,3,2,4,8,4,5,6 };
	QuickSort(a, 0,sizeof(a) / sizeof(a[0])-1);
	arrPrint(a, sizeof(a) / sizeof(a[0]));
}

void _MergeSort(int a[], int left, int right,int *temp)
{
	//�����ݹ�����
	if (left >= right)return;
	
	int mid = (left + right) >> 1;

	//��������
	_MergeSort(a, left, mid, temp);
	_MergeSort(a, mid+1, right, temp);
	
	//�鲢
	int end1 = mid, begin1 = left;
	int begin2 = mid+1, end2 = right;
	int index = left;
	while(begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			temp[index++] = a[begin1++];
		}
		else {
			temp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		temp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		temp[index++] = a[begin2++];
	}
	//������ȥ
	for (int i = left; i <= right; i++)
	{
		a[i] = temp[i];
	}


}
void MergeSort(int a[], int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1, temp);
	free(temp);
}

//ֱ�Ӳ�
void MergeSort2(int a[], int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			//�鲢
			//[i,i+gap-1][i+gap,i+2*gap-1]
			int end1 = i+gap-1, begin1 = i;
			int begin2 = i+gap, end2 = i+2*gap-1;
			int index = begin1;
			//�������������С��gapʱ
		//	if (end1 > n - 1)break;
			//���ұ����䲻����ʱ
			if (begin2 > n - 1)break;
				//���ұ����䲻��ʱ
			if (end2 > n - 1)end2 = n - 1;
			
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					temp[index++] = a[begin1++];
				}
				else {
					temp[index++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				temp[index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				temp[index++] = a[begin2++];
			}
			//������ȥ
			for (int i = begin1; i <= end2; i++)
			{
				a[i] = temp[i];
			}
		}
		gap *= 2;
	}

	free(temp);

}
void Test6()
{
	int a[] = { 9,5,6,3,2,4,8,4,5,6 };
	MergeSort(a, sizeof(a) / sizeof(a[0]) );
	arrPrint(a, sizeof(a) / sizeof(a[0]));
}

int main()
{
	//Test1();
	//Test2();
	/*Test3();
	Test4();
	Test5();
	Test6();*/
	Test6();
	return 0;
}