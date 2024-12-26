#pragma once
#include<iostream>
using namespace std;

template<class T>
struct Node {
	T data;
	Node* next;
};

template<class T>
class LinkList {
private:
	Node<T>* head;
public:
	LinkList();             //构造函数，创建空链表
	~LinkList();			//析构函数，删除表空间
	void CreateList(int n); //创建具有n个元素的线性链表
	void Insert(int i, T e);//在表中第i个位置插入元素
	T Delete(int i);        //删除表中第i个元素
	T GetElem(int i);       //按位查找，获取第i个元素的值
	int Locate(T e);        //在链表中查找为e的元素
	int Empty();			//测表空
	int Length();			//测表长
	void Clear();			//清空表
	void ListDisplay();		//遍历输出表中元素
	Node<T>* Gethead();
	void CreateList(char a[], int size);
};

template<class T>
LinkList<T>::LinkList() {
	//构造函数，创建空链表
	head = new Node<T>;
	head->next = NULL;
}

template<class T>
LinkList<T>::~LinkList() {
	//析构函数，删除表空间
	while (head) {
		Node<T>* p = head;
		head = head->next;
		delete p;
	}
	head = NULL;
}

template<class T>
void LinkList<T>::CreateList(int n) {
	//创建具有n个元素的线性链表
	//尾插法
	Node<T>* p, * s;
	p = head;
	for (int i = 0; i < n; i++) {
		s = new Node<T>;
		cout << "请输入第" << (i + 1) << "个位置的元素值：" << endl;
		cin >> s->data;
		s->next = p->next;
		p->next = s;
		p = s;
	}
}
template<class T>
void LinkList<T>::CreateList(char a[] , int size) {
	Node<T>* p, * s;
	p = head;
	for (int i = 0; i < size; i++) {
		s = new Node<T>;
		s->data = a[i];
		s->next = p->next;
		p->next = s;
		p = s;
	}
}

template<class T>
void LinkList<T>::Insert(int i, T e) {
	//在表中第i个位置插入元素
	Node<T>* p = head;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
		throw "插入位置异常!";
	else {
		Node<T>* s = new Node<T>;
		s->data = e;
		s->next = p->next;
		p->next = s;
	}
}

template<class T>
T LinkList<T>::Delete(int i) {
	//删除表中第i个元素
	T x;
	Node<T>* p, * q;
	p = head;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1)
		throw "删除位置异常！";
	else {
		q = p->next;
		p->next = q->next;
		x = q->data;
		delete q;
		return x;
	}
}

template<class T>
T LinkList<T>::GetElem(int i) {
	//按位查找，获取第i个元素的值
	Node<T>* p;
	p = head->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)
		throw "查找位置异常！";
	else
		return p->data;
}

template<class T>
int LinkList<T>::Locate(T e) {
	//在链表中查找为e的元素
	Node<T>* p;
	p = head->next;
	int i = 1;
	while (p && p->data != e) {
		p = p->next;
		i++;
	}
	if (p)
		return i;
	else
		return 0;
}

template<class T>
int LinkList<T>::Empty() {
	//测表空
	if (!head->next)
		return 1;
	return 0;
}

template<class T>
int LinkList<T>::Length() {
	//测表长
	Node<T>* p;
	p = head;
	int n = 0;
	while (p->next) {
		p = p->next;
		n++;
	}
	return n;
}

template<class T>
void LinkList<T>::Clear() {
	//清空表
	Node<T>* p, * q;
	p = head->next;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
	head->next = NULL;
}

template<class T>
void LinkList<T>::ListDisplay() {
	//遍历输出表中元素
	Node<T>* p;
	p = head->next;
	int n = 1;
	if (!p)
		throw "表中没有元素";
	while (p) {
		cout << "表中第" << n << "个元素为：" << p->data << endl;
		p = p->next;
		n++;
	}
}

template<class T>
inline Node<T>* LinkList<T>::Gethead()
{
	return head;
}
