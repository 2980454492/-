#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACKINCREMENT 10 //存储空间的分配增量

typedef int status;
typedef int ElemType; //数据元素类型定义

//广义表拓展线性链表存储表示
typedef enum {ATOM, LIST} ElemTag; //ATOM=0：原子；LIST=1：子表
typedef struct GLNode {
	ElemTag tag; //公共部分，用于区分原子结点和表结点
	union {
		ElemType atom; //原子结点的值域
		struct GLNode *hp; //表结点的表头指针
	};
	struct GLNode *tp; //相当于链表中的next，指向下一元素结点
} *GList; //广义表类型

status InitGList(GList &L) {
//初始条件：栈不存在
//操作结果：构造一个空栈S
	if (S.base) //栈已存在
		return ERROR;
	S.base = (ElemType *)malloc(sizeof(ElemType) * STACKINCREMENT); //动态分配空间
	for (int i = 0; i < STACKINCREMENT; i++) //默认所有的元素大于0，当=0说明没有元素
		S.base[i] = 0;
	S.top = S.base;
	S.stacksize = STACKINCREMENT;
	return OK;
}

status CreateGList(GList &L, char *S) {
//初始条件：S是广义表的书写形式串
//操作结果：由S创建广义表L

}

status DestroyGList(GList &L) {
//初始条件：栈S已存在
//操作结果：销毁S，S将不存在
	if (!S.base) //栈不存在
		return ERROR;
	free(S.base); //释放队列空间
	S.base = NULL;
	S.top = NULL;
	return OK;
}

status CopyGList(GList &T, GList L) {
//初始条件：广义表L存在
//操作结果：由广义表L复制得到广义表T

}

int GListLength(GList L) {
//初始条件：栈S已存在
//操作结果：栈S的元素个数
	if (!S.base) //栈不存在
		return INFEASIBLE;
	return S.top - S.base;
}

int GListDepth(GList L) {
//初始条件：栈S已存在
//操作结果：栈S的元素个数
	if (!S.base) //栈不存在
		return INFEASIBLE;
	return S.top - S.base;
}

status GListEmpty(GList L) {
//初始条件：栈S已存在
//操作结果：若S为空栈，返回OK，否则返回ERROR
	if (!S.base) //栈不存在
		return INFEASIBLE;
	if (S.top == S.base) //栈为空
		return OK;
	return ERROR; //栈不为空
}

status GetHead(GList L) {
//初始条件：栈S已存在且非空
//操作结果：用e返回S的栈顶元素
	if (!S.base) //栈不存在
		return INFEASIBLE;
	if (StackEmpty(S)) //栈为空
		return ERROR;
	e = *(S.top - 1); //栈元素
	return OK;
}

status GetTail(GList L) {
//初始条件：栈S已存在且非空
//操作结果：用e返回S的栈顶元素
	if (!S.base) //栈不存在
		return INFEASIBLE;
	if (StackEmpty(S)) //栈为空
		return ERROR;
	e = *(S.top - 1); //栈元素
	return OK;
}

status InsertFirstGL(GList &L, ElemType e) {
//初始条件：广义表L存在
//操作结果：插入元素e作为广义表L的第一个元素

}

status DeleteFirstGL(GList &L, ElemType &e) {
//初始条件：广义表L存在
//操作结果：删除广义表L的第一个元素，并用e返回其值

}

status GListTraverse(GList L) {
//初始条件：栈S已存在且非空
//操作结果：从栈底到栈顶依次访问
	if (!S.base) //栈不存在
		return INFEASIBLE;
	printf("栈遍历:");
	for (ElemType *q = S.base; q != S.top; q++) {
		printf("%d ", *q);
	}
	return OK;
}

int main() {
	SqStack S;
	S.base = NULL;
	S.top = NULL;
	int op = 1, ans;
	ElemType  e;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("        1. InitGList （创建广义表）\n");
		printf("        2. DestroyGList （销毁广义表）\n");
		printf("        3. DestroyGList （销毁广义表）\n");
		printf("        4. CopyGList （复制广义表）\n")
		printf("    	5. GListLength （求广义表长度）\n");
		printf("        6. GListDepth （求广义表深度）\n")
		printf("        7. GListEmpty （广义表判空）\n");
		printf("        8. GetHead （获取广义表头元素）\n");
		printf("        9. GetTail （获取广义表尾元素）\n");
		printf("    	10.InsertGListGL （插入头元素）\n");
		printf("        11.DeleteGListGL （删除头元素）\n");
		printf("    	12.GListTraverse （广义表的遍历）\n");
		printf("        0. Exit（退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("    请选择你的操作[0~12]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				ans = InitStack(S);
				if (ans)
					printf("创建成功");
				else
					printf("创建失败，栈已存在");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroyStack(S);
				if (ans)
					printf("销毁成功");
				else
					printf("销毁失败");
				getchar();
				getchar();
				break;
			case 3:
				ans = ClearStack(S);
				if (ans)
					printf("清空成功");
				else
					printf("清空失败");
				getchar();
				getchar();
				break;
			case 4:
				ans = StackEmpty(S);
				if (ans == INFEASIBLE)
					printf("栈不存在");
				else if (ans == ERROR)
					printf("栈不为空");
				else
					printf("栈为空");
				getchar();
				getchar();
				break;
			case 5:
				ans = StackFull(S);
				if (ans == INFEASIBLE)
					printf("栈不存在");
				else if (ans == ERROR)
					printf("栈不为满");
				else
					printf("栈已满");
				getchar();
				getchar();
				break;
			case 6:
				ans = StackLength(S);
				if (ans == INFEASIBLE)
					printf("栈不存在");
				else
					printf("栈长度为%d", ans);
				getchar();
				getchar();
				break;
			case 7:
				ans = GetTop(S, e);
				if (ans == INFEASIBLE)
					printf("获取失败，栈不存在");
				else if (ans == ERROR)
					printf("获取失败，栈为空");
				else
					printf("获取成功，栈顶元素为%d", e);
				getchar();
				getchar();
				break;
			case 8:
				printf("请输入进栈的元素\n");
				scanf("%d", &e);
				ans = Push(S, e);
				if (ans == OK)
					printf("进栈成功");
				else if (ans == INFEASIBLE)
					printf("进栈失败，栈不存在");
				else
					printf("进栈失败，栈已满");
				getchar();
				getchar();
				break;
			case 9:
				ans = Pop(S, e);
				if (ans == INFEASIBLE)
					printf("出栈失败，栈不存在");
				else if (ans == ERROR)
					printf("出栈失败，栈为空");
				else
					printf("出栈成功，出栈元素为%d", e);
				getchar();
				getchar();
				break;
			case 10:
				ans = StackTraverse(S);
				if (ans == INFEASIBLE)
					printf("栈不存在\n");
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