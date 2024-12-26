
#include"linklist.h"
#include"List.cpp"
#include<stack>

using namespace std;

//������
template<class T>
 bool isPalindrome(Node<T> * head) {
	if (head == NULL || head->next == NULL) {
		return true;
	}
	Node<T>* right = head->next;  //rightָ�����ָ���е��ұߵ�һ���ڵ�
	Node<T>* cur = head;
	while (cur->next != NULL && cur->next->next != NULL) {
		right = right->next;
		cur = cur->next->next;
	}
	stack<Node<T>*> stack;
	while (right != NULL) {  //���Ұ벿�ַ���ջ��
		stack.push(right);
		right = right->next;
	}
	while (!stack.empty()) {  //ջ��Ϊ��ʱ
		Node<T> t = *stack.top();
		stack.pop();
		if (head->data != t.data) {  //ջ�е������Ľڵ��ԭ�����ͷ�ڵ㿪ʼ�Աȣ�ֱ��ջ����
			return false;
		}
		head = head->next;
	}
	return true;
}

int main()
{
	
	char s[100];
	while (cin >> s)
	{
		int t = strlen(s);
		bool f = 0;
		if (t < 81 && t > 0) {
			//˳���ʵ��
			for (int i = 0; i < t / 2; i++)
			{
				if (s[i] != s[t - i - 1])
				{
					f = 1;
					break;
				}
			}
			cout << "˳����ж�" << "\n";
			if (f)
			{
				cout << "���ǻ��Ĵ�" << "\n";
			}
			else cout << "�ǻ��Ĵ�" << "\n";


			//����ʵ��
			cout << "�����ж�" << "\n";
			LinkList<char> list;
			createList2(&list , s , t);
			if (isPalindrome(list.Gethead()->next))
			{
				cout << "�ǻ��Ĵ�" << "\n";
			}
			else cout << "�����ǻ��Ĵ�" << "\n"; 
		}
		else cout << "��������" << "\n";
	}

	return 0;
}