#pragma once
#include"linkList.h"
#include<conio.h>
template<typename T>
void menu();        //�˵�
template<typename T>
void createList(LinkList<T>* list);  //����
template<typename T>
void add(LinkList<T>* list);		    //����Ԫ��
template<typename T>
void dele(LinkList<T>* list);	    //ɾ��Ԫ��
template<typename T>
void get(LinkList<T>* list);			//��λ����
template<typename T>
void locate(LinkList<T>* list);		//��ֵ����
template<typename T>
void empty(LinkList<T>* list);		//����
template<typename T>
void length(LinkList<T>* list);		//���
template<typename T>
void clear(LinkList<T>* list);		//���
template<typename T>
void print(LinkList<T>* list);		//��ӡ��