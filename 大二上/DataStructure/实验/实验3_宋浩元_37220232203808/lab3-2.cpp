#include <stdio.h>
#include <malloc.h>
#define INF 32767      //INF��ʾ�����,����

typedef int InfoType;
#define MAXV 100       //��󶥵����

//�����ڽӾ�������
typedef struct{
	int no;          //������
	InfoType info;   //����������Ϣ
}VertexType;       //��������

typedef struct{            //ͼ�Ķ���
	int edges[MAXV][MAXV]; //�ڽӾ���
	int vexnum,arcnum;     //������������
	VertexType vexs[MAXV]; //��Ŷ�����Ϣ
}MGraph;                   //ͼ���ڽӾ�������

//�����ڽӱ�����
typedef struct ANode{         //���Ľ��ṹ����
	int adjvex;               //�û����յ�λ�� 
	struct ANode *nextarc;     //ָ����һ������ָ��
	InfoType info;             //���������Ϣ,�������Ȩֵ
}ArcNode;
typedef int Vertex;
typedef struct Vnode{      //�ڽӱ�ͷ��������
	Vertex data;           //������Ϣ
	ArcNode *firstarc;     //ָ���һ����
}VNode;
typedef VNode AdjList[MAXV]; //AdjList���ڽӱ�����
typedef struct{
	AdjList adjlist;     //�ڽӱ�
	int n,e;             //ͼ�ж�����n�ͱ���
}ALGraph;                //ͼ���ڽӱ�����

//���ڽӾ���gת���ڽӱ�G
void MatToList(MGraph g,ALGraph *&G){
	int i,j,n=g.vexnum;                //nΪ������
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));  
	for(i=0;i<n;i++)                       //���ڽӱ�������ͷ����ָ�����ó�ֵ
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<n;i++)                    //����ڽӾ����е�ÿ��Ԫ��
		for (j=n-1;j>=0;j--)
			if (g.edges[i][j]!=0)        //�ڽӾ���ĵ�ǰԪ�ز�Ϊ0
			{
				p=(ArcNode *)malloc(sizeof(ArcNode));  //����һ�����*p
				p->adjvex=j;
				p->info=g.edges[i][j];
				p->nextarc=G->adjlist[i].firstarc;   //��*p���ӵ��������
				G->adjlist[i].firstarc=p;
			}
			G->n=n; G->e=g.arcnum;
}

//���ڽӱ�Gת��Ϊ�ڽӾ���g
void ListToMat(ALGraph *G,MGraph &g){
	int i,j,n=G->n;
	ArcNode *p;
	for(i=0;i<n;i++)          //g.edges[i][j]����ֵ0
		for(j=0;j<n;j++)
			g.edges[i][j]=0;
	for (i=0;i<n;i++)
	{
		p=G->adjlist[i].firstarc;
		while(p!=NULL){
			g.edges[i][p->adjvex]=p->info;
			p=p->nextarc;
		}			
	}
	g.vexnum=n; g.arcnum=G->e;
		
}

//����ڽӾ���g
void DispMat(MGraph g){
	int i,j;
	for (i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
			if(g.edges[i][j]==INF)
				printf("%3s","��");
			else
				printf("%3d",g.edges[i][j]);
		printf("\n");
	}

}

//����ڽӱ�G
void DispAdj(ALGraph *G){
	int i;
	ArcNode *p;
	for (i=0;i< G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		if(p!=NULL) printf("%3d: ",i);
		while (p!=NULL)
		{
			printf("%3d",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");

	}

}



int visited[MAXV];
//��ͨͼ��������ȱ���
void DFS(ALGraph *G,int v){ //Gָ��ĳ���ڽӱ�v����ʼ����
	ArcNode *p;
	visited[v]=1;                         //�ѷ��ʣ�����1
	printf("%3d",v);					  //��������ʶ���ı��
	p=G->adjlist[v].firstarc;             //pָ�򶥵�v�ĵ�һ�����Ļ�ͷ���
	while (p!=NULL)                     
	{
		if(visited[p->adjvex]==0)        //��p->adjvex����δ���ʣ��ݹ������
			DFS(G,p->adjvex);
		p=p->nextarc;                   //pָ�򶥵�v����һ�����Ļ�ͷ���
	}
	
}

//��ͨͼ��������ȱ���(�ǵݹ�)
void DFS1(ALGraph *G,int v){
	ArcNode *p;
	ArcNode *St[MAXV];
	int top=-1,w,i;
	for(i=0;i< G->n;i++)
		visited[i]=0;
	printf("%3d",v);
	visited[v]=1;
	top++;
	St[top]=G->adjlist[v].firstarc;
	while (top > -1)
	{	
		p=St[top]; top--;
		while (p!=NULL)
		{
			w=p->adjvex;
			if (visited[w]==0)
			{
				printf("%3d",w);
				visited[w]=1;
				top++;
				St[top]=G->adjlist[w].firstarc;
				break;
			}
			p=p->nextarc;
		}
		
	}
	printf("\n");
}

//��ͨͼ�Ĺ�����ȱ���
void BFS(ALGraph *G,int v){ //Gָ��ĳ���ڽӱ�,v����ʼ����
	ArcNode *p;
	int queue[MAXV],front=0,rear=0;      //����ѭ�����в���ʼ��
	int visited[MAXV];                   //�����Ž��ķ��ʱ�־������
	int w,i;
	for(i=0;i< G->n;i++) visited[i]=0;   //���ʱ�־�����ʼ��
	printf("%3d",v);                     //��������ʶ���ı��
	visited[v]=1;                        //���ѷ��ʱ��
	rear=(rear+1)%MAXV;
	queue[rear]=v;                      //v����
	while (front!=rear)                 //�����в���ʱѭ��
	{
		front=(front+1)%MAXV;
		w=queue[front];                //���Ӳ�����w
		p=G->adjlist[w].firstarc;      //���붥��w�ڽӵĵ�һ������
		while (p!=NULL)
		{
			if (visited[p->adjvex]==0)  //����ǰ�ڽӶ���δ����
			{
				printf("%3d",p->adjvex); //�������ڶ���
				visited[p->adjvex]=1;    //�øö����ѱ����ʵı�־
				rear=(rear+1)%MAXV;      //�ö������
				queue[rear]=p->adjvex;
			}
			p=p->nextarc;             //����һ���ڽӶ���
		}
	}
	printf("\n");
}

int main()
{
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[6][6]={
		{0,5,0,5,5,0},
		{0,0,4,0,4,0},
		{0,0,0,0,0,9},
		{0,0,0,0,0,0},
		{0,0,5,7,0,7},
		{0,0,0,0,0,0}
	};

	g.vexnum=6; g.arcnum=10;
	for (i=0;i<g.vexnum;i++)
		for(j=0;j<g.vexnum;j++)
			g.edges[i][j]=A[i][j];
	printf("\n");
	printf(" ����ͼG���ڽӾ���: \n");
	DispMat(g);

	G=(ALGraph *)malloc(sizeof(ALGraph));
	printf(" ͼG���ڽӾ���ת��Ϊ�ڽӱ�: \n");
	MatToList(g,G);
	DispAdj(G);

// 	printf(" ͼG���ڽӱ�ת��Ϊ�ڽӾ���: \n");
// 	ListToMat(G,g1);
// 	DispMat(g1);
// 	printf("\n");

	printf("������ȱ�����\n");
	DFS(G,0);
	printf("\n");

	printf("������ȱ�����\n");
	BFS(G,0);
	printf("\n");


}


