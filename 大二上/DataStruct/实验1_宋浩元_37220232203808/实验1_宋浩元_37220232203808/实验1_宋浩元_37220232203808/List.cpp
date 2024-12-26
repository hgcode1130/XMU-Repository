#include"List.h"

template<typename T>
void menu()        //菜单
{
	cout << "************************" << endl;
	cout << "*****  1.建表      *****" << endl;
	cout << "*****  2.增加元素  *****" << endl;
	cout << "*****  3.删除元素  *****" << endl;
	cout << "*****  4.按位查找  *****" << endl;
	cout << "*****  5.按值查找  *****" << endl;
	cout << "*****  6.测表空    *****" << endl;
	cout << "*****  7.表长      *****" << endl;
	cout << "*****  8.清空      *****" << endl;
	cout << "*****  9.打印表    *****" << endl;
	cout << "*****  0.退出      *****" << endl;
	cout << "************************" << endl;
}

template<typename T>
void createList(LinkList<T>* list)  //建表
{
	system("cls");
	cout << "*****  1.建表      *****" << endl;
	cout << "您需要创建几个元素？" << endl;
	int n;
	cin >> n;
	list->CreateList(n);
	cout << "创建成功！" << endl;
}

template<typename T>
void add(LinkList<T>* list)		    //增加元素
{
	system("cls");
	cout << "*****  2.增加元素  *****" << endl;
	int i;
	T e;
	cout << "您想把元素添加在第几位？" << endl;
	cin >> i;
	cout << "您想添加的元素是？" << endl;
	cin >> e;
	list->Insert(i, e);
	cout << "添加成功！" << endl;
}

template<typename T>
void dele(LinkList<T>* list)	    //删除元素
{
	system("cls");
	cout << "*****  3.删除元素  *****" << endl;
	int i;
	cout << "您想删除第几位元素？" << endl;
	cin >> i;
	T e = list->Delete(i);
	cout << "已成功删除第" << i << "位元素：" << e << endl;
}

template<typename T>
void get(LinkList<T>* list)			//按位查找
{
	system("cls");
	cout << "*****  4.按位查找  *****" << endl;
	int i;
	cout << "您要查找哪一位？" << endl;
	cin >> i;
	T e = list->GetElem(i);
	cout << "表中第" << i << "位元素为：" << e << endl;
}

template<typename T>
void locate(LinkList<T>* list)		//按值查找
{
	system("cls");
	cout << "*****  5.按值查找  *****" << endl;
	T e;
	cout << "您想在表中查找哪个元素？" << endl;
	cin >> e;
	int i = list->Locate(e);
	if (i) {
		cout << "元素" << e << "在表中第" << i << "位" << endl;
	}
	else {
		cout << "未找到该元素" << endl;
	}
}

template<typename T>
void empty(LinkList<T>* list)		//测表空
{
	system("cls");
	cout << "*****  6.测表空    *****" << endl;
	if (list->Empty())
		cout << "表空" << endl;
	else
		cout << "表非空" << endl;
}

template<typename T>
void length(LinkList<T>* list)		//测表长
{
	system("cls");
	cout << "*****  7.表长      *****" << endl;
	cout << "表长为：" << list->Length() << endl;
}

template<typename T>
void clear(LinkList<T>* list)		//清空
{
	system("cls");
	cout << "*****  8.清空      *****" << endl;
	cout << "是否确认清空?按“1”确认，其他键取消操作" << endl;
	char c = _getch();
	if (c == '1') {
		list->Clear();
		cout << "已清空" << endl;
	}
	else {
		cout << "取消操作成功" << endl;
	}
}

template<typename T>
void print(LinkList<T>* list)		//打印表
{
	system("cls");
	cout << "*****  9.打印表    *****" << endl;
	list->ListDisplay();
}