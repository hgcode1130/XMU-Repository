#ifndef   __MGraph_H__
#define   __MGraph_H__
typedef int VRType;    // �����ϵ����
typedef char VertexType[20]; // ��������
// ͼ������(�ڽӾ���)�洢��ʾ
#define INFINITY 4270000 // ���������ֵ����� 
#define MAX_VERTEX_NUM 20 // ��󶥵���� 
typedef enum {DG,DN,UDG,UDN} GraphKind; // {����ͼ,������,����ͼ,������}

typedef struct {
	VRType adj; // �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // ��ά����

typedef struct {    // ͼ������(�ڽӾ���)�洢
	VertexType vexs[MAX_VERTEX_NUM]; // ����ʸ��
	AdjMatrix arcs; // �ڽӾ���
	int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind; // ͼ�������־
} MGraph;

/*�ڽӾ����8������������������*/
int LocateVex(MGraph G,VertexType u);//��ͼG�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
VertexType* GetVex(MGraph G,int v);// ����ͼG��ĳ����������v�����ظö����ֵ
void visit(VertexType i);// ������������ֵ
int FirstAdjVex(MGraph G,VertexType v);// v��ͼG��ĳ�����㣬����v�ĵ�һ���ڽӶ������š�������v��G��û���ڽӶ��㣬�򷵻�-1
int NextAdjVex(MGraph G,VertexType v,VertexType w);//v��ͼG��ĳ�����㣬w��v���ڽӶ��㣬����v��(�����w��)��һ���ڽӶ������ţ���w��v�����һ���ڽӶ��㣬�򷵻�-1
void CreateGraphF(MGraph &G);//��������(�ڽӾ���)��ʾ�������ĵ�����������G
void DestroyGraph(MGraph &G);//����ͼG
void Display(MGraph G);//����ڽӾ���洢��ʾ��ͼG
#endif

