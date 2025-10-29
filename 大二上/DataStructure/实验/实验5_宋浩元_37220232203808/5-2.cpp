/* BST:Binary Sort Tree����������  */
/* ����������    �Ĳ��룬���ң�ɾ��  */


/*�������ӣ� 
*�����������Ľ�������12
*�����������Ľ����ֵ��70 67 46 105 100 99 104 103 115 110 108 112
*������������46 67 70 99 100 103 104 105 108 110 112 115
*��������Ҫ���ҵ���ֵ��70
*���ҳɹ���

*��������Ҫɾ������ֵ��105
*ɾ���ɹ���
*������������46 67 70 99 100 103 104 108 110 112 115 �밴���������. . .
 */
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

#define Status bool

//���Ľ��
typedef struct BiTNode
{
    ElemType data;
    struct  BiTNode *left,*right;
}BiTNode,*BiTree;

////��������
//typedef struct 
//{
//   BiTNode* root;
//}BiTree;


Status Delete(BiTNode* p);//����һ��

//����������������
void insert(BiTree& tree, int value)//������
{
    BiTNode* node=(BiTNode*)malloc(sizeof(BiTNode));//����һ���ڵ�
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    if (tree == NULL)//�ж����ǲ��ǿ���
    {
        tree = node;
    }
    else {//���ǿ���
        BiTNode* temp = tree;//��������ʼ
        while (temp != NULL)
        {
            if (value < temp->data)//С�ھͽ������
            {
                if (temp->left == NULL)
                {
                    temp->left = node;
                    return;
                }
                else {//�����ж�
                    temp = temp->left;
                }
            }
            else {//������Ҷ���
 
                if (temp->right == NULL)
                {
                    temp->right = node;
                    return;
                }
                else {//�����ж�
                    temp = temp->right;
                }
            }
        }
    }
    return;
}




// �ݹ���Ҷ���������T���Ƿ����key
// ָ��Fָ��T��˫�ף����ʼֵ����ֵΪNULL
// �����ҳɹ�����ָ��Pָ�������Ԫ�ؽ�㣬������TRUE
// ����ָ��Pָ�����·���Ϸ��ʵ����һ����㣬������FALSE
Status SearchBST(BiTNode* T,int key,BiTNode *f,BiTNode *p)
{
    if(!T)//���Ҳ��ɹ�
    {
        p = f;
        return false;
    }
    else if (key == T->data)//���ҳɹ�
    {
        p = T;
        return true;
    }
    else if(key <T->data)
    {
        return SearchBST(T->left,key,T,p);//���������ϼ�������
    }
    else
    {
        return SearchBST(T->right,key,T,p);//���������ϼ�������
    }
}

void inorder(BiTNode* node)//�����������
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d ",node->data);
        inorder(node->right);
    }
}

// bool SearchBST(BiTNode* T,int key)
// {
//     if(T == NULL)//���Ҳ��ɹ�
//     {
//         return false;
//     }
//     else if (key == T->data)//���ҳɹ�
//     {
//         return true;
//     }
//     else if(key <T->data)
//     {
//         return SearchBST(T->left,key);//���������ϼ�������
//     }
//     else
//     {
//         return SearchBST(T->right,key);//���������ϼ�������
//     }
// }



//ɾ�����
Status DeleteBST(BiTNode* T,int key)
{
    if(T == NULL)
    {
        printf("����Ϊ�գ�����ɾ����");
        return false;
    }
    else
    {
        if(key == T->data)
        {
            return Delete(T);
        }
        else if(key < T->data)
        {
            return DeleteBST(T->left,key);
        }
        else
        {
            return DeleteBST(T->right,key);
        }
    }
}

Status Delete(BiTNode* p)
{
    BiTNode* q;
    BiTNode* s;
    if(p->right == NULL)
    {
        //������Ϊ�յ�ʱ�򣬽�����������ȥ�����ˡ�
        q = p;
        p = p->left;
        free(q);
    }
    else if(p->left == NULL)
    {
        //������Ϊ�յ�ʱ�򣬽�����������ȥ�����ˡ�
        q = p;
        p = p->right;
        free(q);
    }
    else
    {
        //ֱ��ǰ��data�滻Ҫɾ�����data
        //ֱ��ǰ�����������ӵ�ԭֱ��ǰ������
        q = p;
        s = p->left;
        while(s->right)
        {
            //ͨ���������ҳ���s���������ֵ��������������
            q = s;
            s = s->right;
        }

        p->data = s->data;
        if(q != p)
        {
            //��ɾ�������������һ��б����
            q->right = s->left;
        }
        else
        {
            //��ɾ������������а�����������������ֱ��ǰ�������������ӵ�ֱ��ǰ����㸸�ڵ��������ϡ�
            q->left = s->left;  
        }
        free(s);
    }
    return true;
}

int main()
{

    BiTree tree;
    tree = NULL;//����һ������
    int n,key;
    bool flag,flag2;

    BiTNode *f,*p;
    printf("�����������Ľ�������");
    scanf("%d",&n);
    printf("�����������Ľ����ֵ��");
    for(int i=0;i<n;i++)//����n���������������
    {
        int temp;
        scanf("%d",&temp);
        insert(tree,temp);
    }
    printf("������������");
    inorder(tree);//�������

    printf("\n��������Ҫ���ҵ���ֵ��");
    scanf("%d",&key);
    flag = SearchBST(tree,key,f,p);
    // flag = SearchBST(tree.root,key);
    if(flag == true)
    {
        printf("���ҳɹ���\n");
    }
    else
    {
        printf("����ʧ�ܣ�\n");
    }
  

    printf("\n��������Ҫɾ������ֵ��");
    scanf("%d",&key);
    flag2 = DeleteBST(tree,key);
    if(flag == true)
    {
        printf("ɾ���ɹ���\n");
    }
    else
    {
        printf("ɾ��ʧ�ܣ�\n");
    }

    printf("������������");
    inorder(tree);//�������

    system("pause");
    return 0;
}





