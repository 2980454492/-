#include "stdio.h"
#include "stdlib.h"

void print(int a[], int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int compare(const void *a, const void *b) {
	return (*(int *)a - * (int *)b); // ������������
}

void InsertSort(int a[], int n) { //ֱ�Ӳ�������
	for (int i = 2; i <= n; i++) {
		if (a[i] < a[i - 1]) {
			a[0] = a[i]; //����Ϊ�ڱ�
			int j;
			for (j = i - 1; j > 0 && a[0] < a[j]; j--)
				a[j + 1] = a[j]; //��¼����
			a[j + 1] = a[0]; //���뵽��ȷλ��
		}
	}
}

void BInsertSort(int a[], int n) { //�۰��������
	for (int i = 2; i <= n; i++) {
		a[0] = a[i];
		int low = 1, high = i - 1;
		while (low <= high) {
			int mid = (low + high) / 2; //�۰�
			if (a[0] > a[mid]) //�������midǰ��
				low = mid + 1;
			else //�������mid����
				high = mid - 1;
		}
		int j;
		for (j = i - 1; j >= low; j--) {
			a[j + 1] = a[j]; //��¼����
		}
		a[j + 1] = a[0]; //����
	}
}

void ShellSort(int a[], int n) { //ϣ������
	int dk = n / 2; //һ��������Ĭ��ÿ������ȡһ��
	while (dk > 0) {
		for (int i = 1 + dk; i <= n; i++) {
			a[0] = a[i]; //�ݴ�
			int j;
			for (j = i - dk; a[j] > a[0] && j > 0; j -= dk) {
				a[j + dk] = a[j];
			}
			a[j + dk] = a[0];
		}
		dk /= 2;
	}
}

void BubbleSort(int a[], int n) { //ð������
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= n; j++) {
			if (a[j] < a[j - 1]) {
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}

void QSort(int a[], int low, int high) { //��������
	int begin = low, end = high;
	a[0] = a[low]; //�����¼�ؼ���
	while (low < high) { //�ӱ����˽������м�ɨ��
		while (low < high && a[high] >= a[0]) {
			high--;
		}
		a[low] = a[high]; //��������С�ļ�¼�Ƶ��Ͷ�
		while (low < high && a[low] <= a[0]) {
			low++;
		}
		a[high] = a[low]; //���������ļ�¼�Ƶ��߶�
	}
	a[low] = a[0];
	if (begin < end) { //���ȴ���1
		QSort(a, begin, low - 1); //�Ե��ӱ�ݹ�����
		QSort(a, low + 1, end); //�Ը��ӱ�ݹ�����
	}
}

void swap(int a[], int i, int j) { //�����������±�Ϊi��j��Ԫ��
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void SelectSort(int a[], int n) { //��ѡ������
	for (int i = 1; i < n; i++) {
		int index = -1;
		a[0] = a[i];
		for (int j = i; j <= n; j++) { //ѡ������С�ļ�¼
			if (a[j] < a[0]) {
				a[0] = a[j];
				index = j;
			}
		}
		if (i != index && index != -1) //��С��Ԫ���±겻����δ��������ĵ�һ��
			swap(a, i, index);
	}
}

void HeapAdjust(int a[], int n) { //������ת��Ϊ�󶥶���ʽ
	for (int i = n / 2; i > 0; i--) {
		int j = 2 * i, begin = i, flag; //bigin����ԭ��i��ֵ��flag��־���й�Ԫ�ؽ�������
		do {
			flag = 0;
			if (j + 1 > n) {
				if (a[i] < a[j]) //û���Һ���
					swap(a, i, j);
			} else {
				if (a[j] < a[j + 1]) //����С���Һ���
					j++;
				if (a[i] < a[j]) { //���Ӵ��ڸ���
					swap(a, i, j);
					i = j; //��������Ѱ��
					j *= 2;
					flag = 1;
				}
			}
		} while (j <= n && flag == 1); //δ�������鳤�Ȳ�����Ԫ�ؽ����˽������������ѭ��
		i = begin; //��i��ԭ��ԭ��ֵ
	}
}

void HeapSort(int a[], int n) { //�����򣨴˷���Ĭ�ϴ󶥶ѣ�
	for (int i = n; i > 0; i--) {
		HeapAdjust(a, i); //������ת��Ϊ�󶥶���ʽ
		swap(a, 1, i); //���Ѷ�Ԫ�����ڶѵף�����ɴ�Ԫ������
	}
}

void Merge(int a[], int b[], int low, int high, int mid) {
//��midΪ�磬��a��������������鲢Ϊһ���������鲢�����b��
	int ia = low, ib = mid + 1;
	for (int i = low; i <= high; i++) {
		if (ia > mid) //ǰ��ֵ�꣬��ʣ��ĺ󲿷����鸳ֵ��b
			b[i] = a[ib++];
		else if (ib > high) //��ֵ�꣬��ʣ���ǰ�������鸳ֵ��b
			b[i] = a[ia++];
		else if (a[ia] <= a[ib]) //ǰС�ڵ��ں󣬽�ǰ���ָ�ֵ��b
			b[i] = a[ia++];
		else //��С��ǰ����
			b[i] = a[ib++];
	}
}

void MSort(int a[], int b[], int low, int high) { //�鲢����
	if (low == high) {
		b[low] = a[low];
		return;
	}
	int mid = (low + high) / 2;
	MSort(a, b, low, mid);
	MSort(a, b, mid + 1, high);
	Merge(a, b, low, high, mid);
	for (int i = low; i <= high; i++)
		a[i] = b[i];
}

void MergeSort(int a[], int n) { //�鲢����
	int b[n]; //��������
	MSort(a, b, 1, n);
}

int main() {
	printf("����������ĳ���\n");
	int n, op;
	scanf("%d", &n);
	int a[n + 1] = {0};
	printf("����������%d������\n", n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	printf("��ѡ��˵���Ŀ\n1.ֱ�Ӳ�������\n2.�۰��������\n3.ϣ����������\n4.ð������\n5.��������\n6.��ѡ������\n7.������\n8.�鲢����\n");
	scanf("%d", &op);
	switch (op) {
		case 1:
			InsertSort(a, n);
			break;
		case 2:
			BInsertSort(a, n);
			break;
		case 3:
			ShellSort(a, n);
			break;
		case 4:
			BubbleSort(a, n);
			break;
		case 5:
			QSort(a, 1, n);
			break;
		case 6:
			SelectSort(a, n);
			break;
		case 7:
			HeapSort(a, n);
			break;
		case 8:
			MergeSort(a, n);
			break;
	}
	print(a, n);
	return 0;
}