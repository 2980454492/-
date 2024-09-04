#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0

typedef int status;
typedef int KeyType;

typedef struct {
	KeyType key;
	char others[20];
} TElemType;

typedef struct BiTNode { //二叉链表结点的定义
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void visit(BiTree T) { //二叉树访问
	printf("%d ", T->data.key);
}

status CreateBiTree(BiTree &T, TElemType definition[], int begin) {
//初始条件：二叉树已存在
//操作结果：按definition构造二叉树T
	for (int i = 0; definition[i].key != -1; i++) {     //检查是否有关键字相同的结点
		for (int j = i + 1; definition[j].key != -1; j++) {
			if (definition[i].key == definition[j].key && definition[i].key != 0) {
				return ERROR;
			}
		}
	}
	static int k = 0;                  //静态变量保持在递归中k的值可以传回上层函数
	if (definition[k].key == -1) {
		return OK;
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	if (definition[k].key != 0) {          //下一个结点不为空
		T->data.key = definition[k].key;
		strcpy(T->data.others, definition[k].others);
		k++;
		CreateBiTree(T->lchild, definition, begin + 1);
		CreateBiTree(T->rchild, definition, begin + 1);
	} else {           //下一结点为空
		k++;
		T = NULL;
	}
	if (begin == 1)
		k = 0;
	return OK;
}

status DestroyBiTree(BiTree &T) {
//初始条件：二叉树T已存在
//操作结果：销毁二叉树T
	if (T == NULL)
		return OK;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}

status ClearBiTree(BiTree &T) {
//初始条件：二叉树T已存在
//操作结果：将二叉树T清空为空树
	if (T == NULL)
		return OK;
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	T->data.key = 0;
	strcpy(T->data.others, "\0");
	T->lchild = NULL;
	T->rchild = NULL;
	return OK;
}

status BiTreeEmpty(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：若T为空二叉树，则返回OK，否则返回ERROR
	if (T == NULL)
		return OK;
	else
		return ERROR;
}

int BiTreeDepth(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：返回T的深度
	if (T == NULL) {
		return 0;
	}
	int ldeep = 1 + BiTreeDepth(T->lchild);
	int rdeep = 1 + BiTreeDepth(T->rchild);
	return ldeep > rdeep ? ldeep : rdeep;
	/********** End **********/
}

int NodeDepth(BiTree T, KeyType e) {
//初始条件：二叉树T已存在，e是T中某个结点关键字
//操作结果：返回Node结点的深度
	if (T == NULL)
		return 0;
	if (T->data.key == e)
		return 1;
	int deep = NodeDepth(T->lchild, e) + NodeDepth(T->rchild, e);
	return deep == 0 ? 0 : deep + 1;
}

BiTNode *LocateNode(BiTree T, KeyType e) {
//初始条件：二叉树T已存在，e是T中某个结点关键字
//操作结果：返回该结点指针
	if (T == NULL) { //已经到了叶子结点，就返回空结点
		return NULL;
	}
	if (T->data.key == e) { //找到了，则返回该结点
		return T;
	} else { //没有找到，继续向下寻找
		BiTNode *leftResult = LocateNode(T->lchild, e);
		BiTNode *rightResult = LocateNode(T->rchild, e);
		if (leftResult != NULL) { //在左子树中说明找到了
			return leftResult; //返回刚刚找到的结点
		} else { //在左子树中未找到，如果右子树找到就返回找到的结点，未找到就返回空
			return rightResult;
		}
	}
}

BiTNode *LocateParent(BiTree T, KeyType e, int k) {
//初始条件：二叉树T已存在，e是T中某个结点关键字
//操作结果：返回父结点指针
	if (T == NULL)
		return NULL;
	if (T->data.key == e) { //k判断是否为头结点
		return k == 1 ? NULL : T;
	}
	BiTree Node = LocateNode(T, e);
	if (Node == NULL) //e的值不正确
		return NULL;
	BiTree leftNode = LocateParent(T->lchild, e, k + 1);
	if (leftNode != NULL) { //e在T的左子树中
		return T->lchild == Node ? T : leftNode;
	}
	BiTree rightNode = LocateParent(T->rchild, e, k + 1);
	if (rightNode != NULL) { //e在T的右子树中
		return T->rchild == Node ? T : rightNode;
	}
	return NULL;
}

BiTNode *LocateBrother(BiTree T, KeyType e) {
//初始条件：二叉树T已存在，e是T中某个结点关键字
//操作结果：返回值为兄弟结点的指针
	BiTree ParentNode = LocateParent(T, e, 1);
	if (!ParentNode) //e的父结点不存在，有可能是e的值不正确或e是头结点
		return NULL;
	BiTree Node = LocateNode(T, e); //e一定存在且不为头结点，也一定有兄弟结点
	if (Node == ParentNode->lchild)
		return ParentNode->rchild;
	else
		return ParentNode->lchild;
}

status UnExistNode(BiTree T, KeyType value) {
//初始条件：二叉树已存在
//操作结果：若value在T中存在，则返回ERROR，否则返回OK
	if (T == NULL) { //到了空结点
		return OK;
	}
	if (T->data.key == value) { //关键字存在
		return ERROR; //赋值失败，返回0
	}
	int ans = 1 * UnExistNode(T->lchild, value) * UnExistNode(T->rchild, value);
	//采用乘法，只要关键字存在就失败
	if (ans == 0) //关键字存在
		return ERROR;
	else //关键字不存在
		return OK;
}


status Assign(BiTree &T, KeyType e, TElemType value) {
//初始条件：二叉树T已存在，e是某个结点关键字，value的关键字与T不重复
//操作结果：用value代替e的结点数据
	BiTree Node = LocateNode(T, e); //找关键字为e的结点
	if (!Node) //e的值不正确，返回ERROR
		return ERROR;
	if (!UnExistNode(T, value.key) && value.key != Node->data.key) { //关键字重复且不是e
		return ERROR; //赋值失败，返回0
	}
	Node->data = value;
	return OK;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
//初始条件：二叉树T已存在，e是T中某个结点关键字，c中的关键字与T不重复
//操作结果：LR=0或1，插入c为e的左子树或右子树，e原有的左子树或右子树变为c的右子树
//LR=-1插入到头结点，原二叉树变为c的右子树
	if (LR == -1) { //插入的结点是头结点
		BiTree temp = (BiTree)malloc(sizeof(BiTNode));
		temp->data = c;
		temp->lchild = NULL;
		temp->rchild = T; //原来树是新结点的右子树
		T = temp;
		return OK;
	}
	BiTree Node = LocateNode(T, e); //找到需要插入结点的父结点
	if (!Node) //e的值错误
		return 0;
	if (!UnExistNode(T, c.key) && c.key != Node->data.key) { //关键字重复且不是e
		return ERROR; //赋值失败，返回0
	}
	BiTree temp = (BiTree)malloc(sizeof(BiTNode));
	temp->data = c;
	temp->lchild = NULL;
	if (LR == 0) { //左孩子
		temp->rchild = Node->lchild;
		Node->lchild = temp;
	} else if (LR == 1) { //右孩子
		temp->rchild = Node->rchild;
		Node->rchild = temp;
	}
	return OK;
}

status DeleteNode(BiTree &T, KeyType e, int k) {
//初始条件：二叉树T已存在，e是T中某个结点关键字
//操作结果：e是叶子结点，直接删除；只有左子树或右子树，用其左子树或右子树代替e的位置；
//既有左子树又有右子树，将左子树代替e，右子树插入到左子树的最右结点的右子树
	if (T == NULL)
		return 0;
	if (e == T->data.key) { //判断的结点就是需要删除的结点
		if (k == 1) { //k的作用是判断e是否为头结点
			int ans = DeleteNode(T, e, k + 1); //递归自己，假设头结点的孩子还是头结点
			if (ans == OK) { //头结点
				return OK;
			} else if (ans == 2) { //头结点就是孤立结点
				return OK;
			} else if (ans == 3) {
				BiTree temp = T;
				T = T->lchild;
				free(temp);
				temp = NULL;
				return OK;
			} else if (ans == 4) {
				BiTree temp = T;
				T = temp->rchild;
				free(temp);
				temp = NULL;
				return OK;
			}
		} else if (T->lchild == NULL && T->rchild == NULL) { //e是叶子结点
			free(T);
			T = NULL;
			return 2;
		} else if (T->lchild != NULL && T->rchild != NULL) { //e左右孩子都存在
			BiTree temp = T->lchild;
			while (temp->rchild) { //找到T左子树的最右侧，需要在后面接入T的右子树
				temp = temp->rchild;
			}
			temp->rchild = T->rchild;
			return 3;
		} else if (T->lchild == NULL) { //只有右孩子
			return 4;
		} else { //只有左孩子
			return 3;
		}
	}
	int lans = DeleteNode(T->lchild, e, k + 1); //左答案

	if (lans == OK) { //OK说明已经完成删除操作，只需一步步退出递归
		return OK;

	} else if (lans == 2) { //e是叶子结点，删除后T的左子树变为空
		T->lchild == NULL;
		return OK;

	} else if (lans == 3) { //需要将T的左子树变成e的左子树
		BiTree temp = T->lchild;
		T->lchild = temp->lchild;
		free(temp);
		temp = NULL;
		return OK;

	} else if (lans == 4) { //需要将T的左子树变成e的右子树
		BiTree temp = T->lchild;
		T->lchild = temp->rchild;
		free(temp);
		temp = NULL;
		return OK;
	} //在T的左子树中并未找到e
	int rans = DeleteNode(T->rchild, e, k + 1);

	if (rans == OK) {
		return OK;

	} else if (rans == 2) {
		T->rchild = NULL;
		return OK;

	} else if (rans == 3) {
		BiTree temp = T->rchild;
		T->rchild = temp->lchild;
		free(temp);
		temp = NULL;
		return OK;

	} else if (rans == 4) {
		BiTree temp = T->rchild;
		T->rchild = temp->rchild;
		free(temp);
		temp = NULL;
		return OK;
	}
	return 0;
}

status PreOrderTraverse(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：先序遍历二叉树T
	if (T == NULL)
		return ERROR;
	visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

status InOrderTraverse(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：中序遍历二叉树T
	if (T == NULL)
		return ERROR;
	InOrderTraverse(T->lchild);
	visit(T);
	InOrderTraverse(T->rchild);
	return OK;
}

status PostOrderTraverse(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：后序遍历二叉树T
	if (T == NULL)
		return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	visit(T);
	return OK;
}

status LevelOrderTraverse(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：层序遍历二叉树T
	if (T == NULL)
		return ERROR;
	BiTree Queue[20]; //定义一个先进先出的队列
	int i = 0, k = 0;
	Queue[i++] = T;

	while (k < i) {
		BiTree current = Queue[k++]; //依次从前到后访问队列
		visit(current);
		if (current->lchild) //有左孩子则将左孩子信息赋值到队列的末尾
			Queue[i++] = current->lchild;
		if (current->rchild) //有右孩子则将左孩子信息赋值到队列的末尾
			Queue[i++] = current->rchild;
	}
	return OK;
}

status InvertTree(BiTree &T) {
//初始条件：二叉树T已存在
//操作结果：将二叉树T左右子树互换位置
	if (T == NULL)
		return OK;
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;
	InvertTree(T->lchild);
	InvertTree(T->rchild);
	return OK;
}

BiTNode *LocateCommonAncestor(BiTree &T, KeyType e1, KeyType e2) {
//初始条件：二叉树T已存在
//操作结果：返回两个结点e1和e2的最近祖先
	if (T == NULL)
		return NULL;
	if (T->data.key == e1 || T->data.key == e2)
		return T;
	BiTree left = LocateCommonAncestor(T->lchild, e1, e2);
	BiTree right = LocateCommonAncestor(T->rchild, e1, e2);
	if (left && right)
		return T;
	return left != NULL ? left : right;
}

static int k = 0;

status JudgeBiTree(BiTree T) {
//初始条件：二叉树T已存在
//操作结果：二叉树T是为二叉排序树则返回OK，否则返回ERROR
	//按照先序遍历整个树，k保证先遍历的结点小于后遍历的结点
	int ans = 1; //采用乘法，只要出现一次不符合二叉排序的结点就等于0，否则就等于1
	if (T == NULL) //找到空结点
		return OK;
	ans *= JudgeBiTree(T->lchild); //首先访问左子树中的结点

	if (T->data.key >= k) { //当前结点的数据大于之前访问的结点
		k = T->data.key;
	} else //不满足则直接返回0；
		return ERROR;
	ans *= JudgeBiTree(T->rchild);
	return ans; //成功返回1，失败返回0
}


int main( ) {
	BiTree T = NULL, getT = NULL;
	int op = 1, ans, i = 0, begin = 0, e, LR, e2;
	TElemType value;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("    	1. CreateBiTree （创建二叉树）\n");
		printf("        2. DestroyBiTree （销毁二叉树）\n");
		printf("    	3. ClearBiTree （清空二叉树）\n");
		printf("        4. BiTreeEmpty （二叉树判空）\n");
		printf("    	5. BiTreeDepth （求二叉树深度）\n");
		printf("        6. LocateNode （查找结点）\n");
		printf("    	7. Assign （结点赋值）\n");
		printf("        8. LocateBrother （获取兄弟结点）\n");
		printf("    	9. InsertNode （插入结点）\n");
		printf("        10.DeleteNode （删除结点）\n");
		printf("    	11.PreOrderTraverse （前序遍历）\n");
		printf("        12.InOrderTraverse （中序遍历）\n");
		printf("        13.PostOrderTraverse （后序遍历）\n");
		printf("        14.LevelOrderTraverse （层序遍历）\n");
		printf("        15.InvertTree （翻转二叉树）\n");
		printf("        16.LocateParent （获取父亲结点）\n");
		printf("        17.NodeDepth （求结点的深度）\n");
		printf("        18.LocateCommonAncestor （获取最近祖先）\n");
		printf("        19.JudgeBiTree （判断二叉排序树）\n");
		printf("        0. Exit （退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("    请选择你的操作[0~19]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				if (begin != 0) {
					printf("创建失败，二叉树已存在");
				} else {
					printf("输入序列为二叉树带空子树的先序遍历结点序列\n关键字为0时，表示空子树，为 -1表示输入结束\n");
					TElemType definition[100];
					do {
						scanf("%d%s",
						      &definition[i].key, definition[i].others);
						printf("输入下一结点数据\n");
					} while (definition[i++].key != -1);
					ans = CreateBiTree(T, definition, 1);
					if (ans == OK) {
						printf("创建成功");
					} else
						printf("关键字不唯一");
					begin++;
				}
				i = 0;
				getchar();
				getchar();
				break;
			case 2:
				if (T == NULL)
					printf("销毁失败");
				else {
					ans = DestroyBiTree(T);
					if (ans == OK)
						printf("销毁成功");
					begin--;
				}
				getchar();
				getchar();
				break;
			case 3:
				if (T == NULL)
					printf("清除失败");
				else {
					ans = ClearBiTree(T);
					if (ans == OK)
						printf("清除成功");
				}
				getchar();
				getchar();
				break;
			case 4:
				ans = BiTreeEmpty(T);
				if (ans == OK)
					printf("二叉树为空");
				else
					printf("二叉树不为空");
				getchar();
				getchar();
				break;
			case 5:
				ans = BiTreeDepth(T);
				printf("二叉树深度为%d", ans);
				getchar();
				getchar();
				break;
			case 6:
				printf("请输入想要查找的关键字\n");
				scanf("%d", &e);
				getT = LocateNode(T, e);
				if (getT == NULL)
					printf("未找到");
				else {
					printf("找到了\n");
					visit(getT);
				}
				getchar();
				getchar();
				break;
			case 7:
				printf("请输入赋值的关键字，新赋值的数据\n");
				scanf("%d %d %s", &e, &value.key, value.others);
				ans = Assign(T, e, value);
				if (ans == 1)
					printf("赋值成功");
				else
					printf("赋值失败");
				getchar();
				getchar();
				break;
			case 8:
				printf("请输入关键字");
				scanf("%d", &e);
				getT = LocateBrother(T, e);
				if (getT == NULL)
					printf("无兄弟节点");
				else
					printf("已找到，且%d的兄弟节点为%d,%s",
					       e, getT->data.key, getT->data.others);
				getchar();
				getchar();
				break;
			case 9:
				printf("请输入关键字、左右、插入数据\n");
				scanf("%d %d %d %s", &e, &LR, &value.key, value.others);
				ans = InsertNode(T, e, LR, value);
				if (ans == 0)
					printf("插入失败");
				else
					printf("插入成功");
				getchar();
				getchar();
				break;
			case 10:
				printf("请输入想要删除的结点的关键字\n");
				scanf("%d", &e);
				ans = DeleteNode(T, e, 1);
				if (ans == 0)
					printf("删除失败");
				else
					printf("删除成功");
				getchar();
				getchar();
				break;
			case 11:
				printf("先序遍历:");
				ans = PreOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 12:
				printf("中序遍历:");
				ans = InOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 13:
				printf("后序遍历:");
				ans = PostOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 14:
				printf("层序遍历:");
				ans = LevelOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 15:
				ans = InvertTree(T);
				printf("翻转成功");
				getchar();
				getchar();
				break;
			case 16:
				printf("输入要获取父亲结点的关键字\n");
				scanf("%d", &e);
				getT = LocateParent(T, e, 1);
				if (getT) {
					printf("%d的父亲结点是");
					visit(getT);
				} else
					printf("获取失败");
				getchar();
				getchar();
				break;
			case 17:
				printf("输入要获取深度的结点关键字\n");
				scanf("%d", &e);
				ans = NodeDepth(T, e);
				if (ans == ERROR)
					printf("获取失败，关键字不存在");
				else
					printf("%d的深度为%d", e, ans);
				getchar();
				getchar();
				break;
			case 18:
				printf("输入要获取祖先的两个结点\n");
				scanf("%d %d", &e, &e2);
				getT = LocateCommonAncestor(T, e, e2);
				if (getT == NULL)
					printf("获取失败，关键字不存在");
				else {
					printf("最近祖先为");
					visit(getT);
				}
				getchar();
				getchar();
				break;
			case 19:
				ans = JudgeBiTree(T);
				if (ans == ERROR)
					printf("不是二叉排序树");
				else
					printf("是二叉排序树");
				k = 0; //重置静态变量，防止下一次使用该函数出现错误
				getchar();
				getchar();
				break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main()

/*
1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null

2 a 1 b 0 null  0 null 4 c 3 d  0 null  0 null 5 e  0 null  0 null -1 null
*/