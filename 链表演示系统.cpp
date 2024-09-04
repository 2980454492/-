#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct LNode { //单链表（链式结构）结点的定义
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

status InitList(LinkList &L) {
//初始条件：线性表不存在
//操作结果：构造一个空的线性表L
	if (L != NULL) { //线性表不为空则返回ERROR
		return ERROR;
	}
	L = (LinkList)malloc(sizeof(LNode)); //动态分配空间
	L->data = 0; //初始值设为0；
	L->next = NULL; //空表的首结点指向空
	return OK;
}

status DestroyList(LinkList &L) {
//初始条件：线性表L已存在
//操作结果：删除线性表
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	LinkList ne, q = L->next; //前后结点
	while (q) { //前结点不为空
		ne = q->next; //后结点赋值
		free(q); //删除前结点
		q = ne;
	}
	free(L); //将线性表释放空间
	L = NULL; //将线性表释放空间
	return OK;
}

status ClearList(LinkList &L) {
//初始条件：线性表L已存在
//操作结果：将L重置为空表
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	LinkList p = L->next, ne; //前后结点
	while (p) { //前结点不为空
		ne = p->next; //后结点赋值
		free(p); //删除前结点
		p = ne;
	}
	L->next = NULL; //将线性表首结点指向空
	return OK;
}

status ListEmpty(LinkList L) {
//初始条件：线性表L已存在
//操作结果：若L为空表，返回OK，否则返回ERROR
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	if (L->next == NULL) { //首结点为空
		return OK;
	}
	return ERROR;
}

int ListLength(LinkList L) {
//初始条件：线性表L已存在
//操作结果：返回L中数据元素的个数
	if (L == NULL) { //线性表不存在
		return -1;
	}
	int len = 0; //初始化长度
	LinkList p = L->next;
	while (p) { //未到尾指针则循环
		len++;
		p = p->next;
	}
	return len;
}

status GetElem(LinkList L, int i, ElemType &e) {
//初始条件：线性表L已存在，1<=i<=ListLength(L)
//操作结果：用e返回L中的第i个元素的值
	if (L == NULL) {
		return ERROR;
	}
	if (i < 1 || i > ListLength(L)) { //i的值不正确，返回ERROR
		return ERROR;
	}
	LinkList p = L;

	while (i > 0) { //找到第i个元素
		i--;
		p = p->next;
	}
	e = p->data; //将第i个元素赋值给e
	return OK;
}

status LocateElem(LinkList L, ElemType e) {
//初始条件：线性表L已存在
//操作结果：返回e的结点位置
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	int i = 1;
	LinkList p = L->next;
	while (p) { //未到尾指针
		if (p->data == e) //找到了待找元素则返回结点位置
			return i;
		i++;
		p = p->next;
	}
	return ERROR; //未找到结点位置返回ERROR
}

status PriorElem(LinkList L, ElemType e, ElemType &pre) {
//初始条件：线性表L已存在
//操作结果：获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	LinkList p = L, ne = L->next; //前后结点
	while (ne) {
		if (e == ne->data) { //找到了待找元素
			if (p == L) //e是第一个元素，没有前驱
				return ERROR;
			pre = p->data; //将前驱信息赋值给pre
			return OK;
		}
		p = ne;
		ne = p->next;
	}
	return ERROR; //未找到元素e
}

status NextElem(LinkList L, ElemType e, ElemType &next) {
//初始条件：线性表L已存在
//操作结果：获取线性表L中元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	LinkList p = L->next, ne;
	if (p == NULL) //线性表是空表
		return ERROR;
	ne = p->next;
	while (ne) { //后元素存在
		if (e == p->data) { //找到了待找元素
			next = ne->data;
			return OK;
		}
		p = ne;
		ne = p->next;
	}
	return ERROR; //未找到元素e
}

status ListInsert(LinkList &L, int i, ElemType e) {
//初始条件：线性表L已存在，1<=i<=ListLength(L)+1
//操作结果：在L中第i个位置之前插入新的元素数据e，L的长度+1
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	if (i < 1 || i > ListLength(L) + 1) { //i的值不正确，返回ERROR
		return ERROR;
	}
	LinkList p = L, t = (LinkList)malloc(sizeof(LNode)); //动态分配一个新空间
	t->data = e;
	while (i-- > 1) { //寻找位置i
		p = p->next;
	}
	t->next = p->next; //修改指针位置
	p->next = t;
	return OK;
}

status ListDelete(LinkList &L, int i, ElemType &e) {
//初始条件：线性表L已存在且非空，1<=i<=ListLength(L)
//操作结果：删除L中第i个数据元素，用e返回其值，L的长度-1
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	if (i < 1 || i > ListLength(L)) { //i的值不正确，返回ERROR
		return ERROR;
	}
	LinkList p = L;
	while (i-- > 1) { //寻找位置i的前驱结点
		p = p->next;
	}
	LinkList t = p->next; //t为位置i的结点指针
	if (t == NULL) {
		return ERROR;
	}
	e = t->data;
	p->next = t->next;
	free(t);
	return OK;
}

status ListTraverse(LinkList L) {
//初始条件：线性表L已存在
//操作结果：依次访问L中的每个元素
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	LinkList p = L->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

status reverseList(LinkList &L) {
//初始条件：线性表L已存在
//操作结果：将L翻转
	if (L == NULL) {  //线性表不存在
		return ERROR;
	}
	LinkList p1 = L->next, p2 = p1->next, p3 = p1;
	p1->next = NULL; //首先将第一个元素置于末尾
	while (p2 != NULL) {
		p1 = p2;
		p2 = p2->next;
		p1->next = p3;
		p3 = p1;
	}
	L->next = p1; //将最后一个元素置于开头
	return OK;
}

status RemoveNthFromEnd(LinkList L, int n) {
//初始条件：线性表L已存在且非空
//操作结果：该链表中倒数第n个结点
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	int len = ListLength(L);
	if (n > len || n < 1) { //n的值不正确
		return ERROR;
	}
	LinkList p = L->next;
	for (int i = 0; i < len - n; i++) { //找到倒数第n个结点
		p = p->next;
	}
	return p->data;
}

status sortList(LinkList &L) {
//初始条件：线性表L已存在
//操作结果：将L由小到大排序
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	int flag = 0; //快速退出功能
	LinkList p1 = L, p2 = p1->next;
	while (1) { //采用冒泡排序的方法
		flag = 0; //还原flag的值

		while (p2->next != NULL) {
			if (p2->data > p2->next->data) {
				flag = 1; //表示有元素的位置要改变
				p1->next = p2->next; //实现两指针翻转
				p2->next = p1->next->next;
				p1->next->next = p2;
				p2 = p1->next;
			}
			p1 = p2;
			p2 = p2->next;
		}
		if (flag == 0) //已经完成排序操作，直接返回OK，节省时间
			break;
		p1 = L; //一趟排序结束后重新回到头结点进行下一趟排序
		p2 = p1->next;
	}
	return OK;
}

int main() {
	LinkList L = NULL;
	int op = 1;
	int j;
	ElemType i, e, pre, next;
	while (op) {
		system("cls");
		printf("\n");
		printf("     Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList（线性表的创建）\n");
		printf("    	  2. DestroyList（销毁线性表）\n");
		printf("    	  3. ClearList（清空线性表）\n");
		printf("    	  4. ListEmpty（线性表判空）\n");
		printf("    	  5. ListLength（求线性表长度）\n");
		printf("    	  6. GetElem（获取元素）\n");
		printf("          7. LocateElem（查找元素）\n");
		printf("          8. PriorElem（获取前驱元素）\n");
		printf("          9. NextElem（获取后继元素）\n");
		printf("          10.ListInsert（插入元素）\n");
		printf("          11.ListDelete（删除元素）\n");
		printf("          12.ListTrabverse（遍历线性表）\n");
		printf("          13.reverseList（链表翻转）\n");
		printf("          14.RemoveNthFromEnd（倒数第n个结点）\n");
		printf("          15.sortList（链表排序）\n");
		printf("          0. Exit（退出菜单）\n");
		printf("-------------------------------------------------\n");
		printf("     请选择你的操作[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList(L);
				if (j == OK)
					printf("线性表创建成功！\n");
				else
					printf("线性表创建失败！\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList(L);
				if (j == OK)
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
				if ( j == OK)
					printf("线性表为空！\n");
				else if (j == ERROR)
					printf("线性表不为空！\n");
				else
					printf("线性表不存在！\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength(L);
				if (j == -1)
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
				if (j == ERROR)
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
				if (j == ERROR)
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
				ListTraverse(L);
				getchar();
				getchar();
				break;
			case 13:
				reverseList(L);
				printf("翻转成功\n");
				getchar();
				getchar();
				break;
			case 14:
				printf("请输入想要获得的倒数第n个元素\n");
				scanf("%d", &i);
				j = RemoveNthFromEnd(L, i);
				if (j == ERROR)
					printf("n的值错误\n", i);
				else
					printf("倒数第%d个元素为%d\n", i, j);
				getchar();
				getchar();
				break;
			case 15:
				j = sortList(L);
				printf("排序成功\n");
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