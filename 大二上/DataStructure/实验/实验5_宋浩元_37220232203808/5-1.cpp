#include <stdio.h>
#define N 10000 
int main()
{
	int a[N],n;
	scanf("%d",&n);
	for (int i=0; i<n; i++)
		scanf("%d",&a[i]);
	int m;
	scanf("%d",&m);
	while (m--)
	{
		int x;
		scanf("%d",&x);
		int low =0, high =n-1,mid;   // �������ֵ
		while (low<=high)
		{
			mid = (low+high)/2 ;
			if (x == a[mid])   break;           // �ҵ������¼
			else if (x<a[mid])  high=mid-1;   // ������ǰ��������м���
			else  low=mid+1;                      // �����ں��������м���
		}
		if (low<=high)       // �ҵ������¼
			printf("%d���±�λ%d��λ��\n",x,mid);
		else
			printf("δ�ҵ���\n");
	}
	return 0;
}
