#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100   //��󶨵㶥���� 
#define INFINITF 65535  //�� 65535����ʾ���� 
#define	MAX 100
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0 
#define OK 1 
#define ERROR 0
typedef int Boolean;	//Boolean�ǲ������ͣ���ֵ��TRUE��FALSE 
Boolean visited[MAX];
typedef struct{
	char vexs[MAXVEX];  //����� 
	int arc[MAXVEX][MAXVEX];  //�ڽӾ��󣬿ɿ����߱�
	int numVertexes,numEdges;  //ͼ�е�ǰ�Ķ����� 
	int GraphType; //ͼ������ 
}MGraph;
typedef struct{
	int data[MAXSIZE];
	int front;     //ͷָ�� 
	int rear; //βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� 
}SqQueue;
//��ʼ��һ���ն���
int InitQueue(SqQueue *Q)
{
	Q->front=0;
	Q->rear=0;
	return OK;
}
int QueueEmpty(SqQueue Q)
{
	if(Q.rear==Q.front)
		return TRUE;
	else
		return FALSE;
}
//ѭ����������в��� 
int EnQueue(SqQueue *Q,int e) 
{
	if ((Q->rear+1)%MAXSIZE == Q->front);  //���������ж�
		return ERROR;
	Q->data[Q->rear]=e;  //��Ԫ��e��ֵ����β
	Q->rear=(Q->rear+1)%MAXSIZE; //rearָ�������һλ��,���������ת������ͷ��
	return OK; 
}
// ѭ�����г����в���
int DeQueue(SqQueue *Q,int *e)
{
	if (Q->front == Q->rear)
		return ERROR; //���пյ��ж�
	*e = Q->data[Q->front];  //����ͷԪ�ظ�ֵ��e 
	Q->front=(Q->front+1)%MAXSIZE; //frontָ�������һλ��
	return OK; 
} 
void CreateMGraph (MGraph *G)
{
	int i,j,k,w;
	printf("���붥�����ͱ�����\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges); //���붥�����ͱ���
	fflush(stdin);
	for(i=0;i<G->numVertexes;i++)
	{
		printf("��%d�����㣺",i+1);
		scanf("%c",&G->vexs[i]);
		getchar(); 
	}
	for(i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
			G->arc[i][j]=INFINITF ; //�ڽӾ����ʼ�� 
	for(k=0;k<G->numEdges;k++)
	{
		printf("�����(vi,vj)�ϵ��ϱ�i,�±�j��ȨW:");
		scanf("%d %d %d",&i,&j,&w); //�����(vi,vj)�ϵ�ȨW
		G->arc[i][j]=w;
		if(G->GraphType==0)
		G->arc[j][i]=G->arc[i][j];  //��Ϊ������ͼ������Գ� 
	}
}
  //����ڽӾ���
void output(MGraph *G) 
{
	int i,j,count=0;
	for (i=0;i<G->numVertexes;i++)
		printf("\t%c",G->vexs[i]);	
	printf("\n");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("%4c",G->vexs[i]);
		for(j=0;j<G->numVertexes;j++)
		{
			printf("\t%d",G->arc[i][j]);
			count++;
			if(count%G->numVertexes==0)
			printf("\n");
		}
	}
}
//�ڽӾ����������ȵݹ��㷨 
void DFS (MGraph G,int i)
{
	int j;
	visited[i]=TRUE;
	printf("%c ",G.vexs[i]);  //��ӡ����
	for(j=0;j<G.numVertexes;j++)
	{
		if(G.arc[i][j]==1&&!visited[j])
		DFS(G,j);  //��δ���ʵ��ڽӶ���ݹ���� 
	}	 
} 
//�ڽӾ������ȱ�������
void DFSTraverse(MGraph G)
{
	int i;
	for(i=0;i<G.numVertexes;i++)
		visited[i]=FALSE;  //��ʼ�����ж���״̬����δ���ʹ�״̬ 
	for(i=0;i<G.numVertexes;i++)
		if(!visited[i])   //��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ�� 
		DFS(G,i); 
} 
void BFSTraverse(MGraph G)
{
	int i,j;
	SqQueue Q;
	for(i=0;i<G.numVertexes;i++)
		visited[i]=FALSE;
	InitQueue(&Q);  //��ʼ��һ�����õĶ���
	for(i=0;i<G.numVertexes;i++)  //��ÿ��������ѭ�� 
	{
		if(!visited[i])  //����δ���ʹ��ʹ��� 
		{
			visited[i]=TRUE;  //���õ�ǰ������ʹ� 
			printf("%c ",G.vexs[i]);  //��ӡ����
			EnQueue(&Q,i);	 //���˶�������� 
			while(!QueueEmpty(Q)) //����ǰ���в�Ϊ�� 
			{
				DeQueue(&Q,&i); //������Ԫ�س����У���ֵ��i 
				for(j=0;j<G.numVertexes;j++)
				{
					//�ж�����������뵱ǰ���������δ���ʹ� 
					if(G.arc[i][j] == 1&& !visited[j])
					{
						visited[j]=TRUE;  //���ҵ��Ĵ˶�����Ϊ�ѷ��� 
						printf("%c ",G.vexs[j]);  //��ӡ���� 
						EnQueue(&Q,j); //���ҵ��Ĵ˶�������� 
					}
				}
			} 
		} 
	} 
}
int main()
{
	MGraph G;
	int i,j;
	printf("����ͼ�����ͣ�����ͼ0/����ͼ1����");
	scanf("%d",&G.GraphType); 
	CreateMGraph (&G);
	printf("�ڽӾ����������£�\n");
	output(&G); 
	printf("\n");
	printf("ͼ��������ȱ�������:\n");
	DFSTraverse(G);
	printf("\nͼ�Ĺ�����ȱ������£�\n");
	BFSTraverse(G);
	return 0;
}
