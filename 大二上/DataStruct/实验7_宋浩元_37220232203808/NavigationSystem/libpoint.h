#ifndef LIBPOINT_H
#define LIBPOINT_H

//#ifndef INFI
//#define INFI 6555
#define MATSIZE 10000
//#endif

#define MAXSIZE 100

// 本想直接写成类，但是为了凸显数据结构学科特点，特用结构体自己实现
typedef struct POINTS SPOS; //点集
typedef struct boder SEdge; //边
typedef struct sPoint SSPos;//点

typedef struct POINTS* POS; //点集
typedef struct boder *Edge; //边
typedef struct sPoint *SPos;//点

//POS
struct POINTS {
    SPos point;//点
    Edge edge;//这个点得边
    POS next;//下一个块
};

//SPos
struct sPoint{//有了点类，还要写成点结构体？？,点的类是设计在sql里面用的，自己用链表存不方便，重新写一个；
    int x;
    int y;
    int build;
    char *name;
    char *about;
};
//Edge
struct boder {
    //SPos start;
    int dis;
    SPos end;
    Edge next;
};

class LibPoint
{
public:

    void Test();

    int get_position(QVector<QPoint> V,QPoint val);
    QVector<QPoint> get_min_path(QPoint A,QPoint B);
    void init_GMat(QVector<QPoint> P);
    void Dijsk(QPoint P);
    void Dijsk(int p);


    /**************libpoint 相关方法*************/
    /*****************************************/
    LibPoint();
    void init_from_sql();
    POS append(SPos P);
    POS append(int x,int y);
    POS find(int x,int y);
    POS valueAt(int x,int y); // 有value表明是精准匹配 xy，否则是模糊查找点
    void append_edge(int x,int y,int nx,int ny);
    void remove(int x,int y);
    void removeValue(int x,int y);
    void removeValue(POS pos);
    int nearDisFind(int x,int y,int nx,int ny);
    void showAll();
    QVector<QPoint> getALLQPoints();
    QVector<Point> getAllLines();


    /**************POS 内相关操作方法*************/
    /*****************************************/
    POS _POS();
    POS _POS(int x,int y);
    POS _POS(SPos P);
    void POS_appendEdge(POS pos,int next_x, int next_y);
    void POS_removeEdge(POS pos,int x,int y);
    void POS_removeEdgeValueAt(POS pos,int x,int y);
    QVector<Edge> POS_getEdges(POS pos);
    int POS_nearDisValueAt(POS pos,int nx,int ny);
    int POS_nearDisFind(POS pos ,int nx,int ny);
    QString POS_toString(POS pos);
    void free_pos(POS p);

    /********* SPos 操作方法 ****************/
    /***************************************/
    SPos _SPos();
    SPos _SPos(int x,int y);
    QString SPos_toString(SPos spos);
    void free_spos(SPos p);

     /********* Edge 操作方法 ****************/
     /***************************************/
    Edge _Edge();
    Edge _Edge(int nx,int ny);
    Edge _Edge(SPos spos);
    QString Edge_toString(Edge edge);
    void free_edge(Edge edge);

public:

    POS Head; //所有点 链
    POS End; //最后一个节点
    int INFI = 6555;
    int GMat[MATSIZE][MATSIZE] = {INFI};
    int FLAG[MATSIZE] = {1};
    int GSize ;
    int Path[MATSIZE] = {INFI};
    int Length[MATSIZE] = {0};

};

#endif // LIBPOINT_H
