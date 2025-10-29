#pragma once
#include"linkList.h"
#include<conio.h>
template<typename T>
void menu();        //菜单
template<typename T>
void createList(LinkList<T>* list);  //建表
template<typename T>
void add(LinkList<T>* list);		    //增加元素
template<typename T>
void dele(LinkList<T>* list);	    //删除元素
template<typename T>
void get(LinkList<T>* list);			//按位查找
template<typename T>
void locate(LinkList<T>* list);		//按值查找
template<typename T>
void empty(LinkList<T>* list);		//测表空
template<typename T>
void length(LinkList<T>* list);		//测表长
template<typename T>
void clear(LinkList<T>* list);		//清空
template<typename T>
void print(LinkList<T>* list);		//打印表