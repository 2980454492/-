#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define QUEUEINCREMENT 10 //存储空间的分配增量

typedef int status;
typedef int ElemType; //数据元素类型定义

//队列的顺序存储结构
typedef struct {
	ElemType *base; //初始化的动态分配存储空间
	int front; //头指针，若队列不空，则指向队头元素
	int rear;  //尾指针，若队列不空，则指向队尾元素的下一元素
} SqQueue;

status InitQueue(SqQueue &Q) {
//初始条件：队列不存在
//操作结果：构造一个空队列Q
	if (Q.base) //队列已存在
		return ERROR;
	Q.base = (ElemType *)malloc(sizeof(ElemType) * QUEUEINCREMENT); //动态分配空间
	for (int i = 0; i < QUEUEINCREMENT; i++) //默认所有的元素大于0，当=0说明没有元素
		Q.base[i] = 0;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

status DestroyQueue(SqQueue &Q) {
//初始条件：队列Q已存在
//操作结果：销毁Q，Q将不存在
	if (!Q.base) //队列不存在
		return ERROR;
	free(Q.base); //释放队列空间
	Q.base = NULL;
	Q.front = 0; //重置头尾指针
	Q.rear = 0;
	return OK;
}

status ClearQueue(SqQueue &Q) {
//初始条件：队列Q已存在
//操作结果：将Q清为空队列
	if (!Q.base) //队列不存在
		return ERROR;
	for (int i = 0; i < QUEUEINCREMENT; i++) //归零意味着清空
		Q.base[i] = 0;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

status QueueEmpty(SqQueue Q) {
//初始条件：队列Q已存在
//操作结果：若Q为空队列，返回OK，否则返回ERROR
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (Q.front == Q.rear && !Q.base[Q.front]) //队列为空
		return OK;
	return ERROR; //队列不为空
}

status QueueFull(SqQueue Q) {
//初始条件：队列Q已存在
//操作结果：若Q已满，返回OK，否则返回ERROR
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (Q.rear == Q.front && Q.base[Q.front]) //队列已满
		return OK;
	return ERROR; //队列不为满
}

int QueueLength(SqQueue Q) {
//初始条件：队列Q已存在
//操作结果：返回Q的元素个数
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (Q.rear == Q.front && Q.base[Q.front]) //队列已满
		return QUEUEINCREMENT;
	return (Q.rear - Q.front + QUEUEINCREMENT) % QUEUEINCREMENT;
}

status GetHead(SqQueue Q, int &e) {
//初始条件：队列Q已存在且非空
//操作结果：用e返回Q的队头元素
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (QueueEmpty(Q)) //队列为空
		return ERROR;
	e = Q.base[Q.front]; //队头元素
	return OK;
}

status EnQueue(SqQueue &Q, int e) {
//初始条件：队列Q已存在
//操作结果：插入元素e为Q的新的队尾元素
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (QueueFull(Q)) //队列已满
		return ERROR;
	Q.base[Q.rear++] = e; //新元素插入队尾，重置队尾指针
	Q.rear %= QUEUEINCREMENT; //循环队列
	return OK;
}

status DeQueue(SqQueue &Q, int &e) {
//初始条件：队列Q已存在且非空
//操作结果：删除Q的队头元素，并用e返回其值
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	if (QueueEmpty(Q)) //队列为空
		return ERROR;
	e = Q.base[Q.front]; //头元素赋值
	Q.base[Q.front++] = 0; //删除队头元素
	Q.front %= QUEUEINCREMENT;
	return OK;
}

status QueueTraverse(SqQueue Q) {
//初始条件：队列Q已存在且非空
//操作结果：从队头到队尾依次访问
	if (!Q.base) //队列不存在
		return INFEASIBLE;
	int i = Q.front;
	printf("队列遍历:");
	if (QueueEmpty(Q)) { //队列已满，首先将队头元素输出
		printf("%d ", Q.base[i]);
		i = (i + 1) % QUEUEINCREMENT;
	}
	while (i != Q.rear) {
		printf("%d ", Q.base[i]);
		i = (i + 1) % QUEUEINCREMENT;
	}
	return OK;
}

int main() {
	SqQueue Q;
	Q.base = NULL;
	int op = 1;
	int ans;
	ElemType  e;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("        1. InitQueue （创建队列）\n");
		printf("        2. DestroyQueue （销毁队列）\n");
		printf("    	3. ClearQueue （清空队列）\n");
		printf("        4. QueueEmpty （队列判空）\n");
		printf("        5. QueueFull （队列判满）\n");
		printf("    	6. QueueLength （求队列长度）\n");
		printf("        7. GetHead （获取队头元素）\n");
		printf("    	8. EnQueue （进队）\n");
		printf("        9. DeQueue （出队）\n");
		printf("    	10.QueueTraverse （队列的遍历）\n");
		printf("        0. Exit（退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("    请选择你的操作[0~10]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				ans = InitQueue(Q);
				if (ans)
					printf("创建成功");
				else
					printf("创建失败，队列已存在");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroyQueue(Q);
				if (ans)
					printf("销毁成功");
				else
					printf("销毁失败");
				getchar();
				getchar();
				break;
			case 3:
				ans = ClearQueue(Q);
				if (ans)
					printf("清空成功");
				else
					printf("清空失败");
				getchar();
				getchar();
				break;
			case 4:
				ans = QueueEmpty(Q);
				if (ans == INFEASIBLE)
					printf("队列不存在");
				else if (ans == ERROR)
					printf("队列不为空");
				else
					printf("队列为空");
				getchar();
				getchar();
				break;
			case 5:
				ans = QueueFull(Q);
				if (ans == INFEASIBLE)
					printf("队列不存在");
				else if (ans == ERROR)
					printf("队列不为满");
				else
					printf("队列已满");
				getchar();
				getchar();
				break;
			case 6:
				ans = QueueLength(Q);
				if (ans == INFEASIBLE)
					printf("队列不存在");
				else
					printf("队列长度为%d", ans);
				getchar();
				getchar();
				break;
			case 7:
				ans = GetHead(Q, e);
				if (ans == INFEASIBLE)
					printf("获取，队列不存在");
				else if (ans == ERROR)
					printf("获取失败，队列为空");
				else
					printf("获取成功，队头元素为%d", e);
				getchar();
				getchar();
				break;
			case 8:
				printf("请输入进队的元素\n");
				scanf("%d", &e);
				ans = EnQueue(Q, e);
				if (ans == OK)
					printf("进队成功");
				else if (ans == INFEASIBLE)
					printf("进队失败，队列不存在");
				else
					printf("进队失败，队列已满");
				getchar();
				getchar();
				break;
			case 9:
				ans = DeQueue(Q, e);
				if (ans == INFEASIBLE)
					printf("出队失败，队列不存在");
				else if (ans == ERROR)
					printf("出对失败，队列为空");
				else
					printf("出队成功，出队元素为%d", e);
				getchar();
				getchar();
				break;
			case 10:
				ans = QueueTraverse(Q);
				if (ans = INFEASIBLE)
					printf("队列不存在\n");
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