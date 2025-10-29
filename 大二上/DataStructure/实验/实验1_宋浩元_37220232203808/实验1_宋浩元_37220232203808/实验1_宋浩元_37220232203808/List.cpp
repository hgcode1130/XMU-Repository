#include"List.h"

template<typename T>
void menu()        //�˵�
{
	cout << "************************" << endl;
	cout << "*****  1.����      *****" << endl;
	cout << "*****  2.����Ԫ��  *****" << endl;
	cout << "*****  3.ɾ��Ԫ��  *****" << endl;
	cout << "*****  4.��λ����  *****" << endl;
	cout << "*****  5.��ֵ����  *****" << endl;
	cout << "*****  6.����    *****" << endl;
	cout << "*****  7.��      *****" << endl;
	cout << "*****  8.���      *****" << endl;
	cout << "*****  9.��ӡ��    *****" << endl;
	cout << "*****  0.�˳�      *****" << endl;
	cout << "************************" << endl;
}

template<typename T>
void createList(LinkList<T>* list)  //����
{
	system("cls");
	cout << "*****  1.����      *****" << endl;
	cout << "����Ҫ��������Ԫ�أ�" << endl;
	int n;
	cin >> n;
	list->CreateList(n);
	cout << "�����ɹ���" << endl;
}

template<typename T>
void add(LinkList<T>* list)		    //����Ԫ��
{
	system("cls");
	cout << "*****  2.����Ԫ��  *****" << endl;
	int i;
	T e;
	cout << "�����Ԫ������ڵڼ�λ��" << endl;
	cin >> i;
	cout << "������ӵ�Ԫ���ǣ�" << endl;
	cin >> e;
	list->Insert(i, e);
	cout << "��ӳɹ���" << endl;
}

template<typename T>
void dele(LinkList<T>* list)	    //ɾ��Ԫ��
{
	system("cls");
	cout << "*****  3.ɾ��Ԫ��  *****" << endl;
	int i;
	cout << "����ɾ���ڼ�λԪ�أ�" << endl;
	cin >> i;
	T e = list->Delete(i);
	cout << "�ѳɹ�ɾ����" << i << "λԪ�أ�" << e << endl;
}

template<typename T>
void get(LinkList<T>* list)			//��λ����
{
	system("cls");
	cout << "*****  4.��λ����  *****" << endl;
	int i;
	cout << "��Ҫ������һλ��" << endl;
	cin >> i;
	T e = list->GetElem(i);
	cout << "���е�" << i << "λԪ��Ϊ��" << e << endl;
}

template<typename T>
void locate(LinkList<T>* list)		//��ֵ����
{
	system("cls");
	cout << "*****  5.��ֵ����  *****" << endl;
	T e;
	cout << "�����ڱ��в����ĸ�Ԫ�أ�" << endl;
	cin >> e;
	int i = list->Locate(e);
	if (i) {
		cout << "Ԫ��" << e << "�ڱ��е�" << i << "λ" << endl;
	}
	else {
		cout << "δ�ҵ���Ԫ��" << endl;
	}
}

template<typename T>
void empty(LinkList<T>* list)		//����
{
	system("cls");
	cout << "*****  6.����    *****" << endl;
	if (list->Empty())
		cout << "���" << endl;
	else
		cout << "��ǿ�" << endl;
}

template<typename T>
void length(LinkList<T>* list)		//���
{
	system("cls");
	cout << "*****  7.��      *****" << endl;
	cout << "��Ϊ��" << list->Length() << endl;
}

template<typename T>
void clear(LinkList<T>* list)		//���
{
	system("cls");
	cout << "*****  8.���      *****" << endl;
	cout << "�Ƿ�ȷ�����?����1��ȷ�ϣ�������ȡ������" << endl;
	char c = _getch();
	if (c == '1') {
		list->Clear();
		cout << "�����" << endl;
	}
	else {
		cout << "ȡ�������ɹ�" << endl;
	}
}

template<typename T>
void print(LinkList<T>* list)		//��ӡ��
{
	system("cls");
	cout << "*****  9.��ӡ��    *****" << endl;
	list->ListDisplay();
}