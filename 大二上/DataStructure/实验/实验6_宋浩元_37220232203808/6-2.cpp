#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;
char name[20][25];
void Names(char A[][25],int n)
{
	srand(time(0));
	int i,j,k;
	for(i=0;i<n;i++)
	{
		k=2*(rand()%10+3);	//��������
		for(j=0;j<k;j++)
			A[i][j]=rand()%30+176; //������
		A[i][j]='\0';
	}
}
void NameSort(char name[][25], int n) {
  // ѭ�� n-1 ��
  for (int i = 0; i < n - 1; i++) {
    // ѭ�� n-1-i �Σ�ÿ�ΰ��������ŵ����
    for (int j = 0; j < n - 1 - i; j++) {
      // ���ǰһ�������ں�һ�������ͽ�������
      if (strcmp(name[j], name[j + 1]) > 0) {
        char temp[25];
        strcpy(temp, name[j]);
        strcpy(name[j], name[j + 1]);
        strcpy(name[j + 1], temp);
      }
    }
  }
}
int main(){
	Names(name,20);
	cout << "����ǰ��" << endl; 
	for(int i=0;i<20;i++)cout << name[i] << endl;
	NameSort(name,20);
	cout << "\n\n�����" << endl; 
	for(int i=0;i<20;i++)cout << name[i] << endl;
}
