#include "mymap.h"
#include "mysql.h"
#include "point.h"
#include "base.h"
#include "libpoint.h"
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFile>
#ifndef INFI
//#define INFI 6555
#define MATSIZE 10000
#endif


/**************libpoint 相关操作方法*************/
/*****************************************/

void LibPoint::Test(){

    qDebug() << "test finished!";
}


LibPoint::LibPoint()
{
    Head = _POS();
    End = Head;

}

int LibPoint::get_position(QVector<QPoint> V,QPoint val){
    for (int i = 0;i < V.size();i++){
        if (V.at(i) == val){
            return i+1;
        }
    }
    return 0;
}

QVector<QPoint> LibPoint::get_min_path(QPoint A, QPoint B) {
    QVector<QPoint> AP = getALLQPoints();
    GSize = AP.size() + 1;

    // 初始化邻接矩阵和辅助数组
    for (int i = 0; i < MATSIZE; i++) {
        Length[i] = INFI;
        FLAG[i] = 1;
        for (int j = 0; j < MATSIZE; j++) {
            GMat[i][j] = INFI;
        }
    }

    qDebug() << "总点数：" << AP.size();
    init_GMat(AP);

    // 获取起点和终点的索引
    int index1 = get_position(AP, A);
    int index2 = get_position(AP, B);

    qDebug() << "A 的位置：" << index1;
    qDebug() << "B 的位置：" << index2;

    // 判断起点或终点是否有效
    if (index1 == 0 || index2 == 0) {
        qDebug() << "警告：起点或终点未找到";
        QMessageBox::warning(nullptr, "警告", "起点或终点无效，请检查！");
        return QVector<QPoint>();
    }

    // 初始化 Dijkstra 算法参数
    Length[index2] = 0;
    Path[index2] = index2;
    FLAG[index2] = 0;
    Dijsk(index2);

    QVector<QPoint> retval;

    // 检查是否有通路
    if (Path[index1] == INFI) {
        qDebug() << "不可达";
        QMessageBox::information(nullptr, "提示", "起点与终点之间无通路！");
        return retval;
    }

    // 特殊情况：起点直接连到终点
    if (index1 == index2) {
        qDebug() << "起点直接到终点";
        retval.append(AP.at(index1 - 1)); // 起点
        retval.append(AP.at(index2 - 1)); // 终点
        return retval;
    }

    // 构建路径
    int index = Path[index1];
    retval.append(AP.at(index1 - 1)); // 添加起点
    qDebug() << "路径起点：" << index;

    int i = 0;
    while (index != index2) {
        index = Path[index];
        qDebug() << "路径点：" << index;

        if (index == INFI) {
            qDebug() << "此路不通";
            QMessageBox::information(nullptr, "提示", "起点与终点之间无通路！");
            return QVector<QPoint>();
        }

        retval.append(AP.at(index - 1)); // 添加路径中的点
        i++;

        if (i > 10000) {
            qDebug() << "错误：路径过深，可能存在死循环！";
            QMessageBox::critical(nullptr, "错误", "路径计算失败：递归过深！");
            break;
        }
    }

    retval.append(AP.at(index2 - 1)); // 添加终点
    return retval;
}



void LibPoint::Dijsk(int p){
    FLAG[p] = 0;
    qDebug() << "以" << p << "为基点";
    QVector<int> val = QVector<int> ();
    for (int i = 0 ; i < MATSIZE;i++){
        if (GMat[p][i] < INFI ){ //联通
            if (Length[p] + GMat[p][i]  < Length[i]){ //新路劲更短
                Length[i] = Length[p] + GMat[p][i];
                Path[i] = p;
                Dijsk(i);
            }
            val.append(i);
        }
    }
    for (auto i :val){
        if (FLAG[i]){ //遍历该点为基准点
            Dijsk(i);
        }
    }

}

void LibPoint:: init_GMat(QVector<QPoint> P){
    QVector<Point> V = getAllLines();
    for (auto val : V){
        int index1 = get_position(P,val.toQPoint());
        int index2 = get_position(P,val.next_to_point());
        GMat[index1][index2] = get_dis_int( val.x.toInt(),val.y.toInt(),val.next_x.toInt(),val.next_y.toInt());
    }

}



void LibPoint::init_from_sql(){
    MySQL sql;
    QVector<Point> val = sql.getAllPoints();
    for(auto tmp : val){
        qDebug() << "info:append point:" << tmp.to_string();
        SPos spos = _SPos();
        spos->x = tmp.x.toInt();
        spos->y = tmp.y.toInt();
        append(tmp.x.toInt(),tmp.y.toInt());
    }
   qDebug() << "info:append point finished!";
    QVector<Point> val2 = sql.getAllLines();
    qDebug() << "info:clear!";
    for(auto tmp : val2){
        qDebug() << "info:append edge:" << tmp.to_string();
        append_edge(tmp.x.toInt(),tmp.y.toInt(),tmp.next_x.toInt(),tmp.next_y.toInt());
    }
}

POS LibPoint::append(SPos P){
    POS res = find(P->x,P->y);
    if (res != NULL){
        return res;
    }
    End->next = _POS(P);
    End = End->next;
    End->point = P;
    return End;
}
POS LibPoint::append(int x,int y){
    POS res = find(x,y);
    if (res != NULL){
        return res;
    }
    End->next = _POS(x,y);
    End = End->next;
    return End;
}

POS LibPoint::find(int x,int y){
    POS val = Head->next;
    while (val) {
        if (val->point->x >= x - RANGE && val->point->x <= x + RANGE &&
                val->point->y >= y - RANGE && val->point->y <= y + RANGE){
            return val;
        }
        val = val->next;
    }
    return NULL;
}

POS LibPoint::valueAt(int x,int y){
    POS val = Head->next;
    while (val) {
        if (val->point->x == x  && val->point->y == y){
            return val;
        }
        val = val->next;
    }
    return NULL;
}// 有value表明是精准匹配 xy，否则是模糊查找点
/**
 * @brief LibPoint::append_edge
 * 根据四个坐标插入相邻的点，如果第一个点不存在，则创建第一个点
 * 查找是否已经存在，存在结束，否则插入
 * @param x 点 x
 * @param y 点 y
 * @param nx 相邻点 x
 * @param ny 相邻点 y
 */
void LibPoint::append_edge(int x,int y,int nx,int ny){
    POS res = find(x,y);
    if (res == NULL){
        qDebug() << "info:hava not found x:" << x <<",y:"<<y<<".apend it";
        res = append(x,y);
    }
    POS_appendEdge(res,nx,ny);
    res = find(nx,ny);
    if (res == NULL){
        qDebug() << "info:hava not found x:" << x <<",y:"<<y<<".apend it";
        res = append(x,y);
    }
    POS_appendEdge(res,x,y);
}
void LibPoint::remove(int x,int y){
    POS pos = find(x,y);
    if (pos == NULL){return;}
    removeValue(pos);
    pos = Head->next;
    while (pos) {
        POS_removeEdge(pos,pos->point->x,pos->point->y);
        pos = pos->next;
    }
}
void LibPoint::removeValue(int x,int y){
    POS pos = Head;
    if (pos == NULL){qDebug() << "Error:head null";}
    while (pos->next) {
        if (pos->next == NULL){
        qDebug() << "Error:next null;";
        }
        if (pos->next->point->x == x && pos->next->point->y == y){
            POS tmp = pos->next;
            pos->next = pos->next->next;
            free_pos(tmp);
            return;
        }
        pos = pos->next;
    }
}
void LibPoint::removeValue(POS pos){
    POS pos_ = Head;
    while (pos_->next) {
        if (pos_->next == pos){
            pos_->next = pos->next;
            free(pos);
        }
        pos_ = pos_->next;
    }
}

/**
 * @brief nearDisFind
 * 用坐标模糊查询 dis
 * @param x
 * @param y
 * @param nx
 * @param ny
 * @return
 */
int LibPoint::nearDisFind(int x,int y,int nx,int ny){
    POS pos = find(x,y);
    return POS_nearDisFind(pos,nx,ny);
}



void LibPoint::showAll(){
    qDebug() << "info:showAll!";
    POS pos = Head->next;
    while (pos) {
        qDebug() << POS_toString(pos);
        pos = pos->next;
    }
}

QVector<QPoint> LibPoint::getALLQPoints(){
    QVector<QPoint> retval = QVector<QPoint>();
    POS val = Head->next;
    while (val) {
        retval.append(QPoint(val->point->x,val->point->y));
        val = val->next;
    }
    return retval;
}

QVector<Point> LibPoint::getAllLines(){
    QVector<Point> retval = QVector<Point>();
    POS val = Head->next;
    while (val) {
        Edge edge = val->edge;
        while (edge) {
            retval.append(Point(val->point->x,val->point->y,edge->end->x,edge->end->y));
            edge = edge->next;
        }
       val = val->next;
    }
    return retval;
}

/**************POS 相关操作方法*************/
/*****************************************/

/** 构造方法
 * @brief LibPoint::_POS
 * @return
 */
POS  LibPoint::_POS(){
    POS retval = (POS)malloc(sizeof (SPOS));
    retval->edge = NULL;
    retval->next = NULL;
    retval->point = _SPos();
    return retval;
}
POS  LibPoint::_POS(int x,int y){
    POS retval = (POS)malloc(sizeof (SPOS));
    retval->edge = NULL;
    retval->next = NULL;
    retval->point = _SPos(x,y);
    return retval;
}
POS  LibPoint::_POS(SPos P){
    POS retval = (POS)malloc(sizeof (SPOS));
    retval->edge = NULL;
    retval->next = NULL;
    retval->point = P;
    return retval;
}

void LibPoint::free_pos(POS p){
    free_spos(p->point);
    free_edge(p->edge);
}
/**
 * @brief LibPoint::inser_near
 * 在已知pos 处插入邻接点 x，y
 * @param pos
 * @param next_x
 * @param next_y
 */
void  LibPoint::POS_appendEdge(POS pos,int next_x, int next_y){
    qDebug() << "func:POS_appendEdge!";
    if (pos == NULL){ //第一个点不存在，省去查询dis
        qDebug() << "Error: nullptr:inser to POS but pos is NULL";
        return;
    }else if (POS_nearDisFind(pos,next_x,next_y) > 0){ //dis不为0，则已存在，结束；
        qDebug() << "info:dis exist!";
        return;
    }
    qDebug() << "new Edge!";
    Edge edge = _Edge();
    edge->end = _SPos(next_x,next_y);
    edge->dis = get_dis_int(pos->point->x,pos->point->y,next_x,next_y);
    edge->next = pos->edge;
    pos->edge = edge;
}
void LibPoint::POS_removeEdge(POS pos,int nx,int ny){
    if (pos == NULL){ //第一个点不存在，省去查询dis
        qDebug() << "Error: nullptr:inser to POS but pos is NULL";
        return;
    }else if (POS_nearDisFind(pos,nx,ny) == 0){ //dis为0，则不存在，结束；
        return;
    }
    Edge edge = pos->edge;
    Edge tmp;
    if (edge->end->x <= nx + RANGE && edge->end->x >= nx - RANGE &&
            edge->end->y <= ny + RANGE && edge->end->y >= ny - RANGE){
        tmp = edge;
        pos->edge = pos->edge->next;
        free(tmp);
        return;
    }
    while (edge->next) {
        if (edge->end->x <= nx + RANGE && edge->end->x >= nx - RANGE &&
                edge->end->y <= ny + RANGE && edge->end->y >= ny - RANGE){
            tmp = edge->next;
            edge->next = edge->next->next;
            free(tmp);
            return;
        }
        edge = edge->next;
    }
}
void LibPoint::POS_removeEdgeValueAt(POS pos,int nx,int ny){
    if (pos == NULL){ //第一个点不存在，省去查询dis
        qDebug() << "Error: nullptr:inser to POS but pos is NULL";
        return;
    }else if (POS_nearDisValueAt(pos,nx,ny) == 0){ //dis为0，则不存在，结束；
        return;
    }
    Edge edge = pos->edge;
    Edge tmp;
    if (edge->end->x == nx  && edge->end->y == ny){
        tmp = edge;
        pos->edge = pos->edge->next;
        free(tmp);
    }
    while (edge->next) {
        if (edge->end->x == nx  && edge->end->y == ny){
            tmp = edge->next;
            edge->next = edge->next->next;
            free(tmp);
        }
        edge = edge->next;
    }
}
QVector<Edge> LibPoint::POS_getEdges(POS pos){
    QVector<Edge> retval = QVector<Edge>();
    if (pos == NULL){
        qDebug() << "Error: nullptr:option to POS but pos is NULL";
        return retval;
    }
    Edge edge = pos->edge;
    while (edge) {
        retval.append(edge);
        edge = edge->next;
    }
    return retval;
}
/**
 * @brief nearDisValueAt
 * 精确查找 邻点坐标 的dis
 * @param pos
 * @param nx
 * @param ny
 * @return
 */
int LibPoint::POS_nearDisValueAt(POS pos,int nx,int ny){
    if (pos == NULL){return -1;}
    Edge edge = pos->edge;
    while (edge) {
        if (edge->end->x == nx && edge->end->y == ny){
            return edge->dis;
        }
        edge = edge->next;
    }
    return 0;
}
/**
 * @brief nearDisFind
 * 模糊查找 邻点坐标 dis
 * @param pos
 * @param nx
 * @param ny
 * @return
 */
int LibPoint::POS_nearDisFind(POS pos ,int nx,int ny){
    if (pos == NULL){return -1;}
    Edge edge = pos->edge;
    while (edge) {
        if (edge->end->x >= nx - RANGE && edge->end->y >= ny - RANGE &&
                edge->end->x <= nx + RANGE && edge->end->y <= ny + RANGE){
            return edge->dis;
        }
        edge = edge->next;
    }
    return 0;
}

QString LibPoint::POS_toString(POS pos){
    if (pos == NULL){return "NULL";}
    return  "{point:" + SPos_toString(pos->point) +
            ",Edge:" + Edge_toString(pos->edge) +
            "}";
}





/********* SPos 操作方法 ****************/
/***************************************/

/** 构造方法
 * @brief LibPoint::_SPos
 * @return
 */
SPos LibPoint::_SPos(){
    SPos retval =  (SPos)malloc(sizeof (SSPos));
    retval->x = 0;
    retval->y = 0;
    retval->build = 0;
    return retval;
}
SPos LibPoint::_SPos(int x,int y){
    SPos retval =  (SPos)malloc(sizeof (SSPos));
    retval->x = x;
    retval->y = y;
    QString name ;
    QString about;
    retval->build = 0;
    return retval;
}

void LibPoint::free_spos(SPos p){
//    free(p->name);
//    free(p->about);
    free(p);

}

QString LibPoint::SPos_toString(SPos spos){
    if (spos == NULL){return "NULL";}
    return "{x:" +
            QString::number(spos->x) +
            ",y:" +
            QString::number(spos->y) +
            ",build:" +
            QString::number(1) +
            "}";

}













/*****************************************/

/*********  Edge 操作方法****************/
/***************************************/

Edge LibPoint:: _Edge(){
    Edge retval = (Edge)malloc(sizeof (SEdge));
    retval->dis = 0;
    retval->end = NULL;
    retval->next = NULL;
    return retval;
}

Edge LibPoint:: _Edge(int nx,int ny){
    Edge retval = (Edge)malloc(sizeof (SEdge));
    retval->dis = 0;
    retval->end = _SPos(nx,ny);
    retval->next = NULL;
    return retval;
}
QString LibPoint::Edge_toString(Edge edge){
    if (edge == NULL){return "NULL";}
    int n = 1;
    QString retval = "{";
    Edge tmp = edge;
    while (tmp) {
        retval.append("{No." + QString::number(n) +
                      ",dis:" +
                      QString::number(tmp->dis) +
                      ",end:" +
                      SPos_toString(tmp->end) +
                      "}");
        tmp = tmp->next;
        n++;
    }
    retval.append("}");

    return retval;
}


void LibPoint::free_edge(Edge edge){
    if (edge->next == NULL){
        free(edge);
        return;
    }
    free_edge(edge->next);
    free(edge);
}

/*****************************************/

