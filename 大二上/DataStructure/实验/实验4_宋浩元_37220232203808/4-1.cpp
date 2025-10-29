#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "MGraph.cpp"
#include "MGraph.h"

typedef struct min { //��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
	VertexType adjvex;
	VRType lowcost;
} minside[MAX_VERTEX_NUM];

int minimum(minside SZ,MGraph G) { //��SZ.lowcost����С��ֵ������������SZ�е����
	int i=0,j,k,min;
	while(!SZ[i].lowcost)
		i++;
	min=SZ[i].lowcost;                         // ��һ����Ϊ0��ֵ
	k=i;
	for(j=i+1; j<G.vexnum; j++)
		if(SZ[j].lowcost>0&&min>SZ[j].lowcost) { // �ҵ��µĴ���0����Сֵ
			min=SZ[j].lowcost;
			k=j;
		}
	return k;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u) {	// ��Prim�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
	int i,j,k;
	minside closedge;
	k=LocateVex(G,u);
	for(j=0; j<G.vexnum; ++j) {
		strcpy(closedge[j].adjvex,u);
		closedge[j].lowcost=G.arcs[k][j].adj;
	}
	closedge[k].lowcost=0;
	printf("��С�����������ĸ�����Ϊ:\n");
	for(i=1; i<G.vexnum; ++i) {
		k=minimum(closedge,G);
		printf("��(%s,%s),ȨֵΪ%d\n",closedge[k].adjvex,G.vexs[k],closedge[k].lowcost);
		closedge[k].lowcost=0;
		for(j=0; j<G.vexnum; ++j)
			if(G.arcs[k][j].adj<closedge[j].lowcost) {
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].lowcost=G.arcs[k][j].adj;
			}
	}
}

int main() {
	MGraph g;
	int n;
	CreateGraphF(g);  // ���������ĵ���������ͼ
	Display(g);      // �������ͼ
	printf("�����빹����С����������㣺\n");
	scanf("%d",&n);
	printf("������ķ�㷨��g�ĵ�%d��������������С�������ĸ�����:\n",n);
	MiniSpanTree_PRIM(g,g.vexs[n]);  // Prim�㷨�ӵ�1�����㹹����С������
	return 0;
}

/*
3
5
8
0
1
2
3
4
0 1 1
0 2 3
0 3 4
0 4 7
1 2 2
2 3 5
2 4 8
3 4 6
0
*/
