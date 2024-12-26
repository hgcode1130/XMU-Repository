#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVALUE  100000        //����ַ�����
#define MAXLEAF   256           //���ͬ�ַ�����
#define MAXBIT    MAXLEAF-1
#define MAXNODE   MAXLEAF*2-1
typedef struct {
	float weight;
	int parent;
	int lchild;
	int rchild;
} HNodeType;
typedef struct {
	int bit[MAXBIT];
	int start;
} HCodeType;
void str_input(char str[]) {
	gets(str);
}
int TextStatistics(char text[], char ch[], float weight[]) {
	int text_index = 0,ch_index = 0,weight_index = 0;
	while(text[text_index]!='\0') {
		char* pos = strchr(ch,text[text_index]);
		if(ch[0]==NULL  || pos == NULL ) {//���ch���޸��ַ�������chΪ�ա��ͽ�text[text_index]���뵽ch��
			ch[ch_index] = text[text_index];
			weight[ch_index] += 1;
			ch_index++;
		}
		else {
			weight_index = pos - ch ;
			weight[weight_index] += 1;
		}
		text_index++;
	}
	ch[ch_index] = '\0';
	int index=0;
	while(weight[index]!=0) {
		weight[index]/=text_index;
		index++;
	}
	return ch_index;
}
void select(HNodeType HuffNodes[],int range,int *s1,int *s2) {
	float min1 = 5;
	for(int index1=0; index1<=range; index1++) {
		if(HuffNodes[index1].weight < min1 && HuffNodes[index1].parent ==-1) {
			min1 = HuffNodes[index1].weight;
			*s1 = index1 ;
		}
	}
	float min2 = 5;
	for(int index2=0; index2<=range ; index2++) {
		if(HuffNodes[index2].weight < min2 && HuffNodes[index2].parent ==-1 && index2!=*s1) {
			min2 = HuffNodes[index2].weight;
			*s2 = index2 ;
		}
	}
}

void HuffmanTree(HNodeType HuffNodes[], float weight[], int n) {
	if(n>MAXLEAF) {
		printf("����Ҷ����������!\n");
		return;
	}
	if(n<=1) return;
	int m = 2*n-1;//����ܸ���
	int node_index = 0;
	//�����Ҷ�ڵ�
	for(; node_index < n; node_index++) {
		HuffNodes[node_index].weight = weight[node_index];
		HuffNodes[node_index].parent = -1;
		HuffNodes[node_index].lchild = -1;
		HuffNodes[node_index].rchild = -1;
	}
	//�����Ҷ�ڵ�
	for(; node_index<m; node_index++) {
		HuffNodes[node_index].weight = 0;
		HuffNodes[node_index].parent = -1;
		HuffNodes[node_index].lchild = -1;
		HuffNodes[node_index].rchild = -1;
	}
	//����Huffmantree
	int s1,s2;//��Сֵ����
	for(int i = n; i < m; i++) {
		select(HuffNodes,i-1,&s1,&s2);
		HuffNodes[s1].parent = i;
		HuffNodes[s2].parent = i;
		HuffNodes[i].lchild = s1;
		HuffNodes[i].rchild = s2;
		HuffNodes[i].weight = HuffNodes[s1].weight + HuffNodes[s2].weight;
	}

}
void HuffmanCode(HNodeType HuffNodes[], HCodeType HuffCodes[], int n) {
	//����Huffman���룬Huffman��������HuffCodes��
	int start;
	for(int i =0 ; i<n; i++) {
		start = n-2;
		for(int c = i , f=HuffNodes[i].parent ; f!=-1; c =f,f=HuffNodes[f].parent) {
			if(c == HuffNodes[f].lchild) HuffCodes[i].bit[start--]=0;
			else HuffCodes[i].bit[start--]=1;
		}
		HuffCodes[i].start = start+1;
	}
}
int MidOrderTraverse(HNodeType HuffNodes[], float result[], int root, int resultIndex) {
	//Huffman�������������������������result�У�������һ��resultλ������
	if (root!=-1) {
		resultIndex = MidOrderTraverse( HuffNodes,result,HuffNodes[root].lchild,resultIndex);
		result[resultIndex++] = HuffNodes[root].weight;
		resultIndex = MidOrderTraverse( HuffNodes,result,HuffNodes[root].rchild,resultIndex);
	}
	return resultIndex;
}
int main() {
	HNodeType HuffNodes[MAXNODE];
	HCodeType HuffCodes[MAXLEAF];
	char text[MAXVALUE+1], ch[MAXLEAF];
	float weight[MAXLEAF], result[MAXNODE];
	int i, j, n, resultIndex;
	printf("������Ҫ��������������ַ�����\n");
	str_input(text);
	n = TextStatistics(text, ch, weight);

	HuffmanTree(HuffNodes, weight, n);
	HuffmanCode(HuffNodes, HuffCodes, n);
	for (i=0; i<n; i++) {
		printf("%c��Huffman�����ǣ�", ch[i]);
		for(j=HuffCodes[i].start; j<n-1; j++)
			printf("%d", HuffCodes[i].bit[j]);
		printf("\n");
	}

	resultIndex = MidOrderTraverse(HuffNodes, result, 2*n-2, 0);
	printf("\nHuffman���������������ǣ�");
	for (i=0; i<resultIndex; i++)
		if (i < resultIndex-1)
			printf("%.4f, ", result[i]);
		else
			printf("%.4f\n", result[i]);
}
