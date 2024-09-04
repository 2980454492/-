#include "stdio.h"
#include "stdlib.h"

void print(int a[], int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int compare(const void *a, const void *b) {
	return (*(int *)a - * (int *)b); // 进行升序排序
}

void InsertSort(int a[], int n) { //直接插入排序
	for (int i = 2; i <= n; i++) {
		if (a[i] < a[i - 1]) {
			a[0] = a[i]; //复制为哨兵
			int j;
			for (j = i - 1; j > 0 && a[0] < a[j]; j--)
				a[j + 1] = a[j]; //记录后移
			a[j + 1] = a[0]; //插入到正确位置
		}
	}
}

void BInsertSort(int a[], int n) { //折半插入排序
	for (int i = 2; i <= n; i++) {
		a[0] = a[i];
		int low = 1, high = i - 1;
		while (low <= high) {
			int mid = (low + high) / 2; //折半
			if (a[0] > a[mid]) //插入点在mid前面
				low = mid + 1;
			else //插入点在mid后面
				high = mid - 1;
		}
		int j;
		for (j = i - 1; j >= low; j--) {
			a[j + 1] = a[j]; //记录后移
		}
		a[j + 1] = a[0]; //插入
	}
}

void ShellSort(int a[], int n) { //希尔排序
	int dk = n / 2; //一趟增量，默认每次增量取一半
	while (dk > 0) {
		for (int i = 1 + dk; i <= n; i++) {
			a[0] = a[i]; //暂存
			int j;
			for (j = i - dk; a[j] > a[0] && j > 0; j -= dk) {
				a[j + dk] = a[j];
			}
			a[j + dk] = a[0];
		}
		dk /= 2;
	}
}

void BubbleSort(int a[], int n) { //冒泡排序
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

void QSort(int a[], int low, int high) { //快速排序
	int begin = low, end = high;
	a[0] = a[low]; //枢轴记录关键字
	while (low < high) { //从表两端交替向中间扫描
		while (low < high && a[high] >= a[0]) {
			high--;
		}
		a[low] = a[high]; //将比枢轴小的记录移到低端
		while (low < high && a[low] <= a[0]) {
			low++;
		}
		a[high] = a[low]; //将比枢轴大的记录移到高端
	}
	a[low] = a[0];
	if (begin < end) { //长度大于1
		QSort(a, begin, low - 1); //对低子表递归排序
		QSort(a, low + 1, end); //对高子表递归排序
	}
}

void swap(int a[], int i, int j) { //交换数组中下标为i和j的元素
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void SelectSort(int a[], int n) { //简单选择排序
	for (int i = 1; i < n; i++) {
		int index = -1;
		a[0] = a[i];
		for (int j = i; j <= n; j++) { //选择最最小的记录
			if (a[j] < a[0]) {
				a[0] = a[j];
				index = j;
			}
		}
		if (i != index && index != -1) //最小的元素下标不是在未排序数组的第一个
			swap(a, i, index);
	}
}

void HeapAdjust(int a[], int n) { //将数组转化为大顶堆形式
	for (int i = n / 2; i > 0; i--) {
		int j = 2 * i, begin = i, flag; //bigin保存原来i的值，flag标志进行过元素交换操作
		do {
			flag = 0;
			if (j + 1 > n) {
				if (a[i] < a[j]) //没有右孩子
					swap(a, i, j);
			} else {
				if (a[j] < a[j + 1]) //左孩子小于右孩子
					j++;
				if (a[i] < a[j]) { //大孩子大于父亲
					swap(a, i, j);
					i = j; //继续向下寻找
					j *= 2;
					flag = 1;
				}
			}
		} while (j <= n && flag == 1); //未超出数组长度并且有元素进行了交换操作则继续循环
		i = begin; //将i还原至原来值
	}
}

void HeapSort(int a[], int n) { //堆排序（此方法默认大顶堆）
	for (int i = n; i > 0; i--) {
		HeapAdjust(a, i); //将数组转化为大顶堆形式
		swap(a, 1, i); //将堆顶元素置于堆底，即完成大元素排序
	}
}

void Merge(int a[], int b[], int low, int high, int mid) {
//以mid为界，将a的两个有序数组归并为一个有序数组并存放在b中
	int ia = low, ib = mid + 1;
	for (int i = low; i <= high; i++) {
		if (ia > mid) //前赋值完，将剩余的后部分数组赋值到b
			b[i] = a[ib++];
		else if (ib > high) //后赋值完，将剩余的前部分数组赋值到b
			b[i] = a[ia++];
		else if (a[ia] <= a[ib]) //前小于等于后，将前部分赋值到b
			b[i] = a[ia++];
		else //后小于前，将
			b[i] = a[ib++];
	}
}

void MSort(int a[], int b[], int low, int high) { //归并操作
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

void MergeSort(int a[], int n) { //归并排序
	int b[n]; //辅助数组
	MSort(a, b, 1, n);
}

int main() {
	printf("请输入数组的长度\n");
	int n, op;
	scanf("%d", &n);
	int a[n + 1] = {0};
	printf("请依次输入%d个数据\n", n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	printf("请选择菜单项目\n1.直接插入排序\n2.折半插入排序\n3.希尔插入排序\n4.冒泡排序\n5.快速排序\n6.简单选择排序\n7.堆排序\n8.归并排序\n");
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