
#include"linklist.h"
#include"List.cpp"
#include<stack>

using namespace std;

//链表方法
template<class T>
 bool isPalindrome(Node<T> * head) {
	if (head == NULL || head->next == NULL) {
		return true;
	}
	Node<T>* right = head->next;  //right指针最后指向中点右边第一个节点
	Node<T>* cur = head;
	while (cur->next != NULL && cur->next->next != NULL) {
		right = right->next;
		cur = cur->next->next;
	}
	stack<Node<T>*> stack;
	while (right != NULL) {  //将右半部分放入栈中
		stack.push(right);
		right = right->next;
	}
	while (!stack.empty()) {  //栈不为空时
		Node<T> t = *stack.top();
		stack.pop();
		if (head->data != t.data) {  //栈中弹出来的节点和原链表从头节点开始对比，直到栈弹空
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
			//顺序表实现
			for (int i = 0; i < t / 2; i++)
			{
				if (s[i] != s[t - i - 1])
				{
					f = 1;
					break;
				}
			}
			cout << "顺序表判断" << "\n";
			if (f)
			{
				cout << "不是回文串" << "\n";
			}
			else cout << "是回文串" << "\n";


			//链表实现
			cout << "链表判断" << "\n";
			LinkList<char> list;
			createList2(&list , s , t);
			if (isPalindrome(list.Gethead()->next))
			{
				cout << "是回文串" << "\n";
			}
			else cout << "不是是回文串" << "\n"; 
		}
		else cout << "长度有误" << "\n";
	}

	return 0;
}