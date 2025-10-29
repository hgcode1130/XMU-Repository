//#include"linklist.h"
//#include"List.cpp"
//
//
//int main() {
//
//	//生成对象
//	LinkList<char> list;
//
//	while (true) {
//
//		system("cls");
//
//		//菜单
//		menu<int>();
//
//		//用户选择
//		char choice;
//		choice = _getch();
//
//		//系统接收
//		try {
//			switch (choice) {
//			case '1':
//				createList(&list);
//				break;
//
//			case '2':
//				add(&list);
//				break;
//
//			case '3':
//				dele(&list);
//				break;
//
//			case '4':
//				get(&list);
//				break;
//
//			case '5':
//				locate(&list);
//				break;
//
//			case '6':
//				empty(&list);
//				break;
//
//			case '7':
//				length(&list);
//				break;
//
//			case '8':
//				clear(&list);
//				break;
//
//			case '9':
//				print(&list);
//				break;
//
//			case '0':
//				system("cls");
//				cout << "再见！" << endl;
//				system("pause");
//				return 0;
//				break;
//			default:
//				continue;
//			}
//		}
//		catch (const char* s) {
//			cout << s << endl;
//		}
//
//		system("pause");
//
//	}
//
//	system("pause");
//	return 0;
//
//}