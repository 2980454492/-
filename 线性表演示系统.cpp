#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct { //顺序表（顺序结构）的定义
	ElemType *elem;
	int length;
	int listsize;
} SqList;

status InitList(SqList &L) {
	if (L.elem != NULL) {
		return INFEASIBLE;
	}
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList &L)

// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	L.elem = NULL;
	free(L.elem);
	return OK;
	/********** End **********/
}

status ClearList(SqList &L)

// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = 0;
	}
	L.length = 0;
	return OK;
	/********** End **********/
}

status ListEmpty(SqList L)

// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
	/********** End **********/
}

status ListLength(SqList L)

// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	return L.length;
	/********** End **********/
}

status GetElem(SqList L, int i, ElemType &e)

// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i > L.length || i < 1) {
		return ERROR;
	}
	e = L.elem[i - 1];
	return OK;
	/********** End **********/
}

int LocateElem(SqList L, ElemType e)

// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			return i;
		}
	}
	return 0;
	/********** End **********/
}

status PriorElem(SqList L, ElemType e, ElemType &pre)

// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务

	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			if (i == 1)
				return ERROR;
			else {
				pre = L.elem[i - 2];
				return OK;
			}
		}
	}
	return ERROR;
	/********** End **********/
}

status NextElem(SqList L, ElemType e, ElemType &next)

// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			if (i == L.length)
				return ERROR;
			else {
				next = L.elem[i];
				return OK;
			}
		}
	}
	return ERROR;
	/********** End **********/
}

status ListInsert(SqList &L, int i, ElemType e)

// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i < 1 || i > L.length + 1) {
		return ERROR;
	}
	(int *)realloc(L.elem, sizeof(int *) * 11);
	int x;

	for (int x = L.length; x >= i; x--) {
		L.elem[x] = L.elem[x - 1];
	}
	L.elem[i - 1] = e;
	L.length++;
	return OK;
	/********** End **********/
}

status ListDelete(SqList &L, int i, ElemType &e)

// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i < 1 || i > L.length) {
		return ERROR;
	}
	e = L.elem[i - 1];
	for (int x = i - 1; x < L.length - 1; x++) {
		L.elem[x] = L.elem[x + 1];
	}
	L.length--;
	return OK;
	/********** End **********/
}

status ListTraverse(SqList L)

// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	printf("遍历线性表：");
	for (int i = 0; i < L.length; i++) {
		printf("%d", L.elem[i]);
		if (i < L.length - 1)
			printf(" ");
	}
	return OK;
	/********** End **********/
}

status MaxSubArray(SqList L) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	int sum = 0, result = 0;
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] >= 0) {
			sum += L.elem[i];
		} else {
			if (sum > result) {
				result = sum;
			}
			sum = 0;
		}
	}
	if (sum > result) {
		result = sum;
	}
	return result;
}

status SubArrayNum(SqList L, int k) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	int count = 0;
	for (int i = 0; i < L.length; i++) {
		int sum = 0;
		for (int j = i; j < L.length; j++) {
			sum += L.elem[j];
			if (sum == k)
				count++;
		}
	}
	return count;
}

status sortList(SqList &L) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length - 1; i++) {
		for (int j = i + 1; j < L.length; j++) {
			if (L.elem[i] > L.elem[j]) {
				int temp = L.elem[i];
				L.elem[i] = L.elem[j];
				L.elem[j] = temp;
			}
		}
	}
	return OK;
}

status  SaveList(SqList L, char FileName[])

// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	FILE *fp = fopen(FileName, "w");
	if (fp == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	for (int i = 0; i < L.length; i++) {
		fprintf(fp, "%d", L.elem[i]);
		fprintf(fp, " ");
	}
	fclose(fp);
	return OK;
	/********** End **********/
}

status  LoadList(SqList &L, char FileName[])

// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L.elem != NULL) {
		return INFEASIBLE;
	}
	L.elem = (ElemType *)malloc(sizeof(ElemType) * L.listsize);
	FILE *fp = fopen(FileName, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	for (int i = 0; i < L.length; i++) {
		fscanf(fp, "%d", &L.elem[i]);
	}
	fclose(fp);
	return OK;
	/********** End **********/
}

int main( ) {
	SqList L;
	L.elem = NULL;
	int op = 1;
	int j;
	ElemType i, e, pre, next;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("        1. InitList（线性表的创建）\n");
		printf("        2. DestroyList（销毁线性表）\n");
		printf("    	3. ClearList（清空线性表）\n");
		printf("        4. ListEmpty（线性表判空）\n");
		printf("    	5. ListLength（求线性表长度）\n");
		printf("        6. GetElem（获取元素）\n");
		printf("    	7. LocateElem（查找元素）\n");
		printf("        8. PriorElem（获取前驱元素）\n");
		printf("    	9. NextElem（获取后继元素）\n");
		printf("        10.ListInsert（插入元素）\n");
		printf("    	11.ListDelete（删除元素）\n");
		printf("        12.ListTrabverse（遍历线性表）\n");
		printf("        13.MaxSubArray（获取最大和）\n");
		printf("        14.SubArrayNum（求和个数）\n");
		printf("        15.sortList（线性表排序）\n");
		printf("        0. Exit（退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("    请选择你的操作[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList(L);
				if ( j == OK)
					printf("线性表创建成功！\n");
				else
					printf("线性表创建失败！\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList(L);
				if ( j == OK)
					printf("线性表销毁成功！\n");
				else
					printf("线性表销毁失败！\n");
				getchar();
				getchar();
				break;
			case 3:
				j = ClearList(L);
				if (j == OK)
					printf("线性表清空成功！\n");
				else
					printf("线性表清空失败！\n");
				getchar();
				getchar();
				break;
			case 4:
				j = ListEmpty(L);
				if (j == TRUE)
					printf("线性表为空！\n");
				else if (j == FALSE)
					printf("线性表不为空！\n");
				else
					printf("线性表不存在！\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength(L);
				if ( j == INFEASIBLE)
					printf("线性表不存在！\n");
				else
					printf("线性表长度为%d\n", ListLength(L));
				getchar();
				getchar();
				break;
			case 6:
				printf("输入要获取的元素的位置\n");
				scanf("%d", &i);
				j = GetElem(L, i, e);
				if ( j == INFEASIBLE)
					printf("线性表不存在！\n");
				else if (j == ERROR)
					printf("获取元素失败！\n");
				else
					printf("链表中第%d个元素是%d\n", i, e);
				getchar();
				getchar();
				break;
			case 7:
				printf("请输入要查找的元素\n");
				scanf("%d", &e);
				j = LocateElem(L, e);
				if (j == 0)
					printf("该元素不存在！\n");
				else
					printf("该元素的位置序号是%d\n", j);
				getchar();
				getchar();
				break;
			case 8:
				printf("请输入要查找的元素\n");
				scanf("%d", &e);
				j = PriorElem(L, e, pre);
				if (j == ERROR)
					printf("查找失败，%d为第一个元素或%d不存在！\n", e, e);
				else
					printf("%d的前驱元素是%d\n", e, pre);
				getchar();
				getchar();
				break;
			case 9:
				printf("请输入要查找的元素\n");
				scanf("%d", &e);
				j = NextElem(L, e, next);
				if (j == ERROR)
					printf("查找失败，%d为最后一个元素或%d不存在！\n", e, e);
				else
					printf("%d的后继元素是%d\n", e, next);
				getchar();
				getchar();
				break;
			case 10:
				printf("输入要插入的元素的位置以及元素值\n");
				scanf("%d %d", &i, &e);
				j = ListInsert(L, i, e);
				if (j == OK)
					printf("插入成功！\n");
				else
					printf("插入失败！\n");
				getchar();
				getchar();
				break;
			case 11:
				printf("请输入要删除元素的位置\n");
				scanf("%d", &i);
				j = ListDelete(L, i, e);
				if (j == ERROR)
					printf("删除失败！\n");
				else
					printf("删除成功！\n");
				getchar();
				getchar();
				break;
			case 12:
				if (ListTraverse(L) == INFEASIBLE)
					printf("线性表不存在！\n");
				getchar();
				getchar();
				break;
			case 13:
				j = MaxSubArray(L);
				printf("最大和为%d\n", j);
				getchar();
				getchar();
				break;
			case 14:
				printf("请输入连续子数组的和\n");
				scanf("%d", &i);
				j = SubArrayNum(L, i);
				printf("该数组中和为%d的连续子数组的个数为%d\n", i, j);
				getchar();
				getchar();
				break;
			case 15:
				sortList(L);
				getchar();
				getchar();
				break;
			case 0:
				break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main()