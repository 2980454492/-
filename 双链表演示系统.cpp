#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int status;
typedef int ElemType; //数据元素类型定义

//线性表的双向链表存储结构
typedef struct DuLNode {
	ElemType data; //结点数据
	struct DuLNode *prior; //上一结点指针
	struct DuLNode *next; //下一结点指针
} DuLNode, *DuLinkList;

status InitList_DuL(DuLinkList &L) {
//初始条件：双链表不存在
//操作结果：构造一个空的双链表L
	if (L != NULL) { //双链表不为空则返回ERROR
		return ERROR;
	}
	L = (DuLinkList)malloc(sizeof(DuLNode)); //动态分配空间
	L->data = 0; //初始值设为0；
	L->next = NULL; //空表的首结点指向空
	L->prior = NULL; //空表的首结点的上一结点指向空
	return OK;
}

status DestroyList_DuL(DuLinkList &L) {
//初始条件：双链表L已存在
//操作结果：删除双链表
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	DuLinkList ne, q = L->next; //前后结点
	while (q) { //前结点不为空
		ne = q->next; //后结点赋值
		free(q); //删除前结点
		q = ne;
	}
	free(L); //将双链表释放空间
	L = NULL; //将双链表释放空间
	return OK;
}

status ClearList_DuL(DuLinkList &L) {
//初始条件：双链表L已存在
//操作结果：将L重置为空表
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	DuLinkList p = L->next, ne; //前后结点
	while (p) { //前结点不为空
		ne = p->next; //后结点赋值
		free(p); //删除前结点
		p = ne;
	}
	L->next = NULL; //将双链表首结点指向空
	return OK;
}

status ListEmpty_DuL(DuLinkList L) {
//初始条件：双链表L已存在
//操作结果：若L为空表，返回OK，否则返回ERROR
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	if (L->next == NULL) { //首结点为空
		return OK;
	}
	return ERROR;
}

int ListLength_DuL(DuLinkList L) {
//初始条件：双链表L已存在
//操作结果：返回L中数据元素的个数
	if (L == NULL) { //双链表不存在
		return -1;
	}
	int len = 0; //初始化长度
	DuLinkList p = L->next;
	while (p) { //未到尾指针则循环
		len++;
		p = p->next;
	}
	return len;
}

status GetElem_DuL(DuLinkList L, int i, ElemType &e) {
//初始条件：双链表L已存在，1<=i<=ListLength_DuL(L)
//操作结果：用e返回L中的第i个元素的值
	if (L == NULL) {
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L)) { //i的值不正确，返回ERROR
		return ERROR;
	}
	DuLinkList p = L;
	while (i > 0) { //找到第i个元素
		i--;
		p = p->next;
	}
	e = p->data; //将第i个元素赋值给e
	return OK;
}

status LocateElem_DuL(DuLinkList L, ElemType e) {
//初始条件：双链表L已存在
//操作结果：返回e的结点位置
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	int i = 1;
	DuLinkList p = L->next;
	while (p) { //未到尾指针
		if (p->data == e) //找到了待找元素则返回结点位置
			return i;
		i++;
		p = p->next;
	}
	return ERROR; //未找到结点位置返回ERROR
}

status PriorElem_DuL(DuLinkList L, ElemType e, ElemType &pre) {
//初始条件：双链表L已存在
//操作结果：获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	DuLinkList p = L->next;
	while (p) { //元素存在
		if (e == p->data) { //找到了待找元素
			if (p->prior == L)
				return ERROR;
			pre = p->prior->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR; //未找到元素e
}

status NextElem_DuL(DuLinkList L, ElemType e, ElemType &next) {
//初始条件：双链表L已存在
//操作结果：获取双链表L中元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR
	if (L == NULL) { //双链表不存在
		return ERROR;
	}
	DuLinkList p = L->next;
	while (p) { //元素存在
		if (e == p->data) { //找到了待找元素
			if (p->next == NULL)
				return ERROR;
			next = p->next->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR; //未找到元素e
}

status ListInsert_DuL(DuLinkList &L, int i, ElemType e) {
//初始条件：双链表L已存在，1<=i<=ListLength(L)+1
//操作结果：在L中第i个位置之前插入新的元素数据e，L的长度+1
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L) + 1) { //i的值不正确，返回ERROR
		return ERROR;
	}
	DuLinkList p = L, t = (DuLinkList)malloc(sizeof(DuLNode)); //动态分配一个新空间
	t->data = e;
	while (i-- > 1) { //寻找位置i
		p = p->next;
	}
	t->next = p->next; //修改指针位置
	t->prior = p;
	if (t->next != NULL)
		p->next->prior = t;
	p->next = t;
	return OK;
}

status ListDelete_DuL(DuLinkList &L, int i, ElemType &e) {
//初始条件：双链表L已存在且非空，1<=i<=ListLength(L)
//操作结果：删除L中第i个数据元素，用e返回其值，L的长度-1
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L)) { //i的值不正确，返回ERROR
		return ERROR;
	}
	DuLinkList p = L;
	while (i-- > 0) { //寻找位置i的结点
		p = p->next;
	}
	e = p->data;
	if (p->next) {
		p->next->prior = p->prior;
	}
	p->prior->next = p->next;
	free(p);
	return OK;
}

status ListTraverse_DuL(DuLinkList L) {
//初始条件：双链表L已存在
//操作结果：依次访问L中的每个元素
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	DuLinkList p = L->next;
	printf("正序输出：");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

status ListReverseTraverse_DuL(DuLinkList &L) {
//初始条件：双链表L已存在
//操作结果：依次访问L中的每个元素
	if (L == NULL) { //线性表不存在
		return ERROR;
	}
	DuLinkList p = L;
	while (p->next != NULL) {
		p = p->next;
	}
	printf("逆序输出：");
	while (p != L) {
		printf("%d ", p->data);
		p = p->prior;
	}
	return OK;
}

status reverseList_DuL(DuLinkList &L) {
//初始条件：双链表L已存在
//操作结果：将L翻转
	if (L == NULL) {  //双链表不存在
		return ERROR;
	}
	DuLinkList p1 = L->next, p2 = p1->next, p3 = p1;
	p1->next = NULL; //首先将第一个元素置于末尾
	p1->prior = p2;
	while (p2 != NULL) {
		p1 = p2;
		p2 = p2->next;
		p1->next = p3;
		p1->prior = p2;
		p3 = p1;
	}
	L->next = p1; //将最后一个元素置于开头
	p1->prior = L;
	return OK;
}

int main() {
	DuLinkList L = NULL;
	int op = 1;
	int j;
	ElemType i, e, pre, next;
	while (op) {
		system("cls");
		printf("\n");
		printf("     Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList_DuL（双链表的创建）\n");
		printf("    	  2. DestroyList_DuL（销毁双链表）\n");
		printf("    	  3. ClearList_DuL（清空双链表）\n");
		printf("    	  4. ListEmpty_DuL（双链表判空）\n");
		printf("    	  5. ListLength_DuL（求双链表长度）\n");
		printf("    	  6. GetElem_DuL（获取元素）\n");
		printf("          7. LocateElem_DuL（查找元素）\n");
		printf("          8. PriorElem_DuL（获取前驱元素）\n");
		printf("          9. NextElem_DuL（获取后继元素）\n");
		printf("          10.ListInsert_DuL（插入元素）\n");
		printf("          11.ListDelete_DuL（删除元素）\n");
		printf("          12.ListTrabverse_DuL（正序遍历双链表）\n");
		printf("          13.ListReverseTrabverse_DuL（逆序遍历双链表）\n");
		printf("          14.reverseList_DuL（双链表翻转）\n");
		printf("          0. Exit（退出菜单）\n");
		printf("-------------------------------------------------\n");
		printf("     请选择你的操作[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList_DuL(L);
				if (j == OK)
					printf("双链表创建成功！\n");
				else
					printf("双链表创建失败！\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList_DuL(L);
				if (j == OK)
					printf("双链表销毁成功！\n");
				else
					printf("双链表销毁失败！\n");
				getchar();
				getchar();
				break;
			case 3:
				j = ClearList_DuL(L);
				if (j == OK)
					printf("双链表清空成功！\n");
				else
					printf("双链表清空失败！\n");
				getchar();
				getchar();
				break;
			case 4:
				j = ListEmpty_DuL(L);
				if ( j == OK)
					printf("双链表为空！\n");
				else if (j == ERROR)
					printf("双链表不为空！\n");
				else
					printf("双链表不存在！\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength_DuL(L);
				if (j == -1)
					printf("双链表不存在！\n");
				else
					printf("双链表长度为%d\n", ListLength_DuL(L));
				getchar();
				getchar();
				break;
			case 6:
				printf("输入要获取的元素的位置\n");
				scanf("%d", &i);
				j = GetElem_DuL(L, i, e);
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
				j = LocateElem_DuL(L, e);
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
				j = PriorElem_DuL(L, e, pre);
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
				j = NextElem_DuL(L, e, next);
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
				j = ListInsert_DuL(L, i, e);
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
				j = ListDelete_DuL(L, i, e);
				if (j == ERROR)
					printf("删除失败！\n");
				else
					printf("删除成功！\n");
				getchar();
				getchar();
				break;
			case 12:
				ListTraverse_DuL(L);
				getchar();
				getchar();
				break;
			case 13:
				ListReverseTraverse_DuL(L);
				getchar();
				getchar();
				break;
			case 14:
				reverseList_DuL(L);
				printf("翻转成功\n");
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