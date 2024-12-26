#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MGraph.h"
/*�ڽӾ����8������������������*/
int LocateVex(MGraph G,VertexType u) {
	//��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
	// �����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
	int i;
	for(i=0; i<G.vexnum; ++i)
		if(strcmp(u,G.vexs[i]) == 0)
			return i;   // VertexType��char [16]����
	return -1;
}

VertexType* GetVex(MGraph G,int v) {
	// ��ʼ������ͼG���ڣ�v��G��ĳ���������š��������������v��ֵ
	if( v>=G.vexnum || v<0 )
		exit(0);
	return &(G.vexs[v]);
}

void visit(VertexType i) {
	printf("%s ",i);
}

int FirstAdjVex(MGraph G,VertexType v) {
	// ��ʼ������ͼG���ڣ�v��G��ĳ������
	// �������������v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
	int i,j=0,k;
	k=LocateVex(G,v); // kΪ����v��ͼG�е����
	if(G.kind%2) // ��
		j=INFINITY;
	for(i=0; i<G.vexnum; i++)
		if(G.arcs[k][i].adj!=j)
			return i;
	return -1;
}

int NextAdjVex(MGraph G,VertexType v,VertexType w) {
	// ��ʼ������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ���
	// �������������v��(�����w��)��һ���ڽӶ������ţ���w��v�����һ���ڽӶ��㣬�򷵻�-1
	int i,j=0,k1,k2;
	k1=LocateVex(G,v); // k1Ϊ����v��ͼG�е����
	k2=LocateVex(G,w); // k2Ϊ����w��ͼG�е����
	if(G.kind%2) // ��
		j=INFINITY;
	for(i=k2+1; i<G.vexnum; i++)
		if(G.arcs[k1][i].adj!=j)
			return i;
	return -1;
}

void CreateGraphF(MGraph &G) {
	// ��������(�ڽӾ���)��ʾ�������ĵ�����������G
	int i,j,k,w;
	VertexType va,vb;
	printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,��Ȩ��ͨͼ:3): \n");
	scanf("%d",&G.kind);
	printf("ͼ�Ķ���ĸ���n:\n");
	scanf("%d",&G.vexnum);
	printf("ͼ�ıߵ�����m:\n");
	scanf("%d",&G.arcnum);
	printf("n�����������:\n");
	for(i=0; i<G.vexnum; ++i)            // ���춥��ʸ��
		scanf("%s",G.vexs[i]);
	printf("m���ߵ�����:\n");
	for(i=0; i<G.vexnum; ++i)            // ��ʼ���ڽӾ���
		for(j=0; j<G.vexnum; ++j) {
			if(G.kind%2)                 // ��
				G.arcs[i][j].adj=INFINITY;
			else                         // ͼ
				G.arcs[i][j].adj=0;
		}
	for(k=0; k<G.arcnum; ++k) {
		if(G.kind%2)                 // ��
			scanf("%s%s%d",va,vb,&w);
		else                         // ͼ
			scanf("%s%s",va,vb);

		i=LocateVex(G,va);
		j=LocateVex(G,vb);
		if(G.kind == 0)              // ����ͼ
			G.arcs[i][j].adj =1;
		else if(G.kind == 1)
			G.arcs[i][j].adj=w;      // ������
		else   if(G.kind == 2)       // ����ͼ
			G.arcs[i][j].adj =  G.arcs[j][i].adj=1;
		else
			G.arcs[i][j].adj =  G.arcs[j][i].adj = w;
	}
}

void DestroyGraph(MGraph &G) {
	// ��ʼ������ͼG���ڡ��������������ͼG
	int i,j,k=0;
	if(G.kind%2) // ��
		k=INFINITY; // kΪ������֮���ޱ߻�ʱ�ڽӾ���Ԫ�ص�ֵ
	G.vexnum=0; // ������Ϊ0
	G.arcnum=0; // ����Ϊ0
}

void Display(MGraph G) {
	// ����ڽӾ���洢��ʾ��ͼG
	int i,j;
	switch(G.kind) {
		case DG:
			printf("����ͼ\n");
			break;
		case DN:
			printf("������\n");
			break;
		case UDG:
			printf("����ͼ\n");
			break;
		case UDN:
			printf("��Ȩ��ͨͼ\n");
	}
	printf("%d������%d���ߡ�����������: ",G.vexnum,G.arcnum);
	for(i=0; i<G.vexnum; ++i)       // ���G.vexs
		printf("%s ",G.vexs[i]);
	printf("\nͼ���ڽӾ���:\n");     // ���G.arcs.adj

	for(i=0; i<G.vexnum; i++) {
		for(j=0; j<G.vexnum; j++)
			if(G.kind%2) {
				if(G.arcs[i][j].adj==INFINITY)
					printf("%s\t","��");
				else
					printf("%d\t",G.arcs[i][j].adj);
			} else
				printf("%d\t",G.arcs[i][j].adj);
		printf("\n");
	}
}

