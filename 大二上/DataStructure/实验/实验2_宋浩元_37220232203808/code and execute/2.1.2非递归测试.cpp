# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <queue>
# include <stack>
using namespace std;

typedef char Type;
//test input:abc##d#e##f## 

typedef struct BiTNode {
	Type data;  //������Type: �˴��û�����Ϊchar���� 
	struct BiTNode *lchild;  //��ָ����
	struct BiTNode *rchild;  //��ָ����
} BiTNode, *BiTree;

void InitBiTree(BiTree &T) {
	T = NULL;
}

void Visit(Type e) {
	if(e==NULL){
		return;
	}
	printf("%c ", e);
}

void DestoryBiTree(BiTree &T) {
	if (T) {
		DestoryBiTree(T->lchild);
		DestoryBiTree(T->rchild);
		free(T);
		T = NULL;
	}
}

void PreOrderTraverse(BiTree T) {
	if (T) {
		Visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		Visit(T->data);
		InOrderTraverse(T->rchild);
	}
}

void inOrderIter(BiTNode *root)
{
    stack<BiTNode *> s;
    while (root != NULL || !s.empty()) {
        if (root != NULL) {
            s.push(root);
            root = root->lchild;
        }
        else {
            root = s.top();
            cout << root->data << " ";  //��������������ŷ��ʸ����
            s.pop();
            root = root->rchild;        //����������
        }
    }
}

void PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		Visit(T->data);
	}
}

void LevelOrderTraverse(BiTree T) {
	queue<BiTree> q;
	BiTree a;
	if (T) {
		q.push(T);
		while (!q.empty()) {
			a = q.front();
			q.pop();
			Visit(a->data);
			if (a->lchild != NULL)
				q.push(a->lchild);
			if (a->rchild != NULL)
				q.push(a->rchild);
		}
		cout << endl;
	}
}

int BiTreeEmpty(BiTree T) {
	if (T)
		return 0;
	else
		return 1;
}

int BiTreeDepth(BiTree T) {
	int i, j;
	if (!T)
		return 0;
	i = BiTreeDepth(T->lchild);
	j = BiTreeDepth(T->rchild);
	return i > j? i + 1: j + 1;
}

Type Root(BiTree T) {
	if (BiTreeEmpty(T))
		return NULL;
	else
		return T->data;
}

Type Value(BiTree p) {
	return p->data;
}

void Assign(BiTree p, Type value) {
	p->data = value;
}

void CreateBiTree(BiTree &T) {
	Type ch;
	scanf("%c", &ch);
	if (ch == '#')
		T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(-1);
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

void Delete_Node(BiTree &T)  {
	if(T){
		Visit(T->data);
		cout << "delete?" << endl;
		char a;cin >> a;
		if(a=='y'){
			T->data = NULL;
			T->lchild = NULL;
			T->rchild = NULL;
			return;
		}
		Delete_Node(T->lchild);
		Delete_Node(T->rchild);
	}
}

int main() {
	BiTree T;
	InitBiTree(T);
	CreateBiTree(T);
	cout << endl << "ǰ�����: " << endl;
	PreOrderTraverse(T);
	cout << endl << "�������: " << endl;
	InOrderTraverse(T);
	cout << endl << "2" << endl;
	inOrderIter(T); 
	cout << endl << "�������: " << endl;
	PostOrderTraverse(T);
	cout << endl << "�������: " << endl;
	LevelOrderTraverse(T);
	Delete_Node(T);
	cout << endl << "ǰ�����: " << endl;
	PreOrderTraverse(T);
	cout << endl << "�������: " << endl;
	InOrderTraverse(T);
	cout << endl << "�������: " << endl;
	PostOrderTraverse(T);
	cout << endl << "�������: " << endl;
	LevelOrderTraverse(T);
	return 0;
}
