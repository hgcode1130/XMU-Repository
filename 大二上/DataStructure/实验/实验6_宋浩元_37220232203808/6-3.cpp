#include <stdio.h>
#include <stdlib.h>

void fixtree(int* tree, int treeSize, int index) {
	// ���ӽڵ������
	int left = index * 2 + 1;
	// ���ӽڵ������
	int right = index * 2 + 2;
	// ��Сֵ����������ʼ��Ϊ��ǰ�ڵ�
	int min = index;
	// ������ӽڵ���ڣ����ұȵ�ǰ��СֵС��������Сֵ������
	if (left < treeSize && tree[left] < tree[min]) {
		min = left;
	}
	// ������ӽڵ���ڣ����ұȵ�ǰ��СֵС��������Сֵ������
	if (right < treeSize && tree[right] < tree[min]) {
		min = right;
	}
	// �����Сֵ�����������仯��˵���ӽڵ����бȶѶ�Ԫ�ظ�С��
	if (min != index) {
		// ������Ԫ�غ���Сֵ
		int temp = tree[index];
		tree[index] = tree[min];
		tree[min] = temp;
		fixtree(tree, treeSize, min);
	}
}

// ������ 
void buildtree(int* tree, int treeSize) {
	// �����һ����Ҷ�ӽڵ㿪ʼ����ǰ���δ��� 
	for (int i = treeSize / 2 - 1; i >= 0; i--) {
		fixtree(tree, treeSize, i);
	}
}

// ����ѡ������
void treeSelectSort(int* array, int size) {
	// ������ 
	buildtree(array, size);
	// ѭ��ȡ����Ԫ�أ���������С�� 1
	for (int i = size - 1; i >= 0; i--) {
		// ����Ԫ�����������һ��Ԫ�ؽ���
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		// �����Ĵ�С�� 1
		size--;
		// ���������� 
		fixtree(array, size, 0);
	}
}

int main(void) {
	int array[] = {5, 2, 9, 4, 7, 6, 1, 3, 8};
	int size = sizeof(array) / sizeof(int);
	// ��������ѡ�������㷨
	treeSelectSort(array, size);
	// ��������Ľ��
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
