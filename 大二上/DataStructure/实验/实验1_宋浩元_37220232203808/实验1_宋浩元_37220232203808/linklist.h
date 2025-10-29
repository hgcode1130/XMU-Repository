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
	LinkList();             //���캯��������������
	~LinkList();			//����������ɾ����ռ�
	void CreateList(int n); //��������n��Ԫ�ص���������
	void Insert(int i, T e);//�ڱ��е�i��λ�ò���Ԫ��
	T Delete(int i);        //ɾ�����е�i��Ԫ��
	T GetElem(int i);       //��λ���ң���ȡ��i��Ԫ�ص�ֵ
	int Locate(T e);        //�������в���Ϊe��Ԫ��
	int Empty();			//����
	int Length();			//���
	void Clear();			//��ձ�
	void ListDisplay();		//�����������Ԫ��
	Node<T>* Gethead();
	void CreateList(char a[], int size);
};

template<class T>
LinkList<T>::LinkList() {
	//���캯��������������
	head = new Node<T>;
	head->next = NULL;
}

template<class T>
LinkList<T>::~LinkList() {
	//����������ɾ����ռ�
	while (head) {
		Node<T>* p = head;
		head = head->next;
		delete p;
	}
	head = NULL;
}

template<class T>
void LinkList<T>::CreateList(int n) {
	//��������n��Ԫ�ص���������
	//β�巨
	Node<T>* p, * s;
	p = head;
	for (int i = 0; i < n; i++) {
		s = new Node<T>;
		cout << "�������" << (i + 1) << "��λ�õ�Ԫ��ֵ��" << endl;
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
	//�ڱ��е�i��λ�ò���Ԫ��
	Node<T>* p = head;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
		throw "����λ���쳣!";
	else {
		Node<T>* s = new Node<T>;
		s->data = e;
		s->next = p->next;
		p->next = s;
	}
}

template<class T>
T LinkList<T>::Delete(int i) {
	//ɾ�����е�i��Ԫ��
	T x;
	Node<T>* p, * q;
	p = head;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1)
		throw "ɾ��λ���쳣��";
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
	//��λ���ң���ȡ��i��Ԫ�ص�ֵ
	Node<T>* p;
	p = head->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)
		throw "����λ���쳣��";
	else
		return p->data;
}

template<class T>
int LinkList<T>::Locate(T e) {
	//�������в���Ϊe��Ԫ��
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
	//����
	if (!head->next)
		return 1;
	return 0;
}

template<class T>
int LinkList<T>::Length() {
	//���
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
	//��ձ�
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
	//�����������Ԫ��
	Node<T>* p;
	p = head->next;
	int n = 1;
	if (!p)
		throw "����û��Ԫ��";
	while (p) {
		cout << "���е�" << n << "��Ԫ��Ϊ��" << p->data << endl;
		p = p->next;
		n++;
	}
}

template<class T>
inline Node<T>* LinkList<T>::Gethead()
{
	return head;
}
