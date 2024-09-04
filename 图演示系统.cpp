#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 20

typedef enum {DG, DN, UDG, UDN} GraphKind; //有向图，有向网，无向图，无向网
typedef int status;
typedef int KeyType;

//顶点类型定义
typedef struct {
	KeyType  key;
	char others[20];
} VertexType;

//表结点类型定义
typedef struct ArcNode {
	int adjvex; //顶点位置编号
	struct ArcNode  *nextarc; //下一个表结点指针
} ArcNode;

//头结点及其数组类型定义
typedef struct VNode {
	VertexType data; //顶点信息
	ArcNode *firstarc; //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

//邻接表的类型定义
typedef  struct {
	AdjList vertices; //头结点数组
	int vexnum, arcnum; //顶点数、弧数
	GraphKind kind; //图的种类标志
} ALGraph;

//访问顶点
void visit(VertexType v) {
	printf("%d %s  ", v.key, v.others);
}

//输出顶点信息以及连接的其他顶点的序号
void print(ALGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		ArcNode *p = G.vertices[i].firstarc;
		visit(G.vertices[i].data);
		while (p) {
			printf(" %d", p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}

//根据V和VR构造图G并返回OK
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
	if (V[0].key == -1)
		return ERROR;//插入的点集为空
	int i, j, one = -1, two = -1, flag = 0;
	for (i = 0; VR[i][0] != -1; i++); //计算边数
	G.arcnum = i;
	for (i = 0; V[i].key != -1; i++); //计算点数
	if (i > MAX_VERTEX_NUM) //点数超过了最大的定义域时
		return ERROR;
	G.vexnum = i;
	for (i = 0; i < G.vexnum - 1; i++) //判断是否有不同结点关键字相同
		for (j = i + 1; j < G.vexnum; j++)
			if (V[i].key == V[j].key)
				return ERROR;

	for (i = 0; i < G.arcnum; i++) { //判断边连接的顶点是否存在
		for (j = 0; j < G.vexnum; j++) {
			if (VR[i][0] == V[j].key)
				break;
		}
		if (j == G.vexnum) { //遍历顶点集没有找到该边连接的顶点
			return ERROR;
		}
		for (j = 0; j < G.vexnum; j++) {
			if (VR[i][1] == V[j].key)
				break;
		}
		if (j == G.vexnum) {
			return ERROR;
		}
	}

	for (i = 0; i < G.vexnum; i++) { //顶点赋值给图
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	}

	for (i = 0; i < G.arcnum; i++) { //采用头插法插入相邻边，先插入的结点后输出
		flag = 0;
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][0] == G.vertices[j].data.key) { //找到边的第一个顶点在顶点集中的位置
				one = j;
				break;
			}
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][1] == G.vertices[j].data.key) { //找到边的第二个顶点在顶点集中的位置
				two = j;
				break;
			}
		if (one == two) //环，则不插入
			continue;
		ArcNode *q = G.vertices[one].firstarc;
		while (q) {
			if (q->adjvex == two) { //该结点的相邻结点已经出现过
				flag = 1;
				break;
			}
			q = q->nextarc;
		}
		if (flag == 1)
			continue;
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = two;
		p->nextarc = G.vertices[one].firstarc;
		G.vertices[one].firstarc = p;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = one;
		p->nextarc = G.vertices[two].firstarc;
		G.vertices[two].firstarc = p;
	}
	return OK;
}

//销毁无向图G,删除G的全部顶点和边，G不存在返回ERROR，存在并删除成功返回OK
status DestroyGraph(ALGraph &G) {
	int i;
	ArcNode *p = NULL, *q = NULL;
	for (i = 0; i < G.vexnum; i++) {
		p = G.vertices[i].firstarc;
		while (p) {
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	G.arcnum = 0;
	G.vexnum = 0;
	return OK;
}

//根据u在图G中查找顶点，查找成功返回位序，否则返回-1
int LocateVex(ALGraph G, KeyType u) {
	for (int i = 0; i < G.vexnum; i++) {
		if (u == G.vertices[i].data.key) {
			return i;
		}
	}
	return -1;
}

//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERRO
status PutVex(ALGraph &G, KeyType u, VertexType value) {
	for (int i = 0; i < G.vexnum; i++)
		if (value.key == G.vertices[i].data.key && value.key != u)
			return ERROR;
	int i = LocateVex(G, u);
	if (i == -1)
		return ERROR;
	G.vertices[i].data = value;
	return OK;
}

//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
int FirstAdjVex(ALGraph G, KeyType u) {
	for (int i = 0; i < G.vexnum; i++) {
		if (u == G.vertices[i].data.key) {
			return G.vertices[i].firstarc->adjvex;
		}
	}
	return -1;
}

//v对应G的一个顶点,w对应v的邻接顶点；
//操作结果是返回v的（相对于w）下一个邻接顶点的位序；
//如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
	for (int i = 0; i < G.vexnum; i++) {

		if (v == G.vertices[i].data.key) {
			ArcNode *p = G.vertices[i].firstarc;
			while (p) {
				if (G.vertices[p->adjvex].data.key == w) {
					if (p->nextarc != NULL)
						return p->nextarc->adjvex;
					else
						return -1;
				}
				p = p->nextarc;
			}
		}
	}
	return -1;
}

//在图G中插入顶点v，成功返回OK,否则返回ERROR
status InsertVex(ALGraph &G, VertexType v) {
	if (G.vexnum >= MAX_VERTEX_NUM)
		return ERROR;
	for (int i = 0; i < G.vexnum; i++)
		if (v.key == G.vertices[i].data.key)
			return ERROR;
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}

//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
status DeleteVex(ALGraph &G, KeyType v) {
	int pre_vexnum = G.vexnum; //保留原始的结点个数
	int del_arc_2 = 0; //记录被删的边数
	int k, i; //记录被删结点的位置序号
	for (i = 0; i < G.vexnum; i++) { //找到被删结点并删除，不会把之后结点前移
		if (G.vertices[i].data.key == v) { //找到了需要删的结点
			k = i;
			ArcNode *temp = G.vertices[i].firstarc;
			while (temp) {
				G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc; //依次删除连接该结点的所有边
				free(temp);
				temp = G.vertices[i].firstarc;
				del_arc_2++;
			}
			break;
		}
	}
	if (i == G.vexnum) //没有结点被删除，可能是输入的关键字并不在结点中
		return ERROR;

	for (int i = 0; i < G.vexnum; i++) { //删除其他顶点中与该顶点相关联的边
		if (G.vertices[i].data.key == v)
			continue; //跳过删除结点
		ArcNode *p = G.vertices[i].firstarc; //删除其他结点中的该边

		if (p != NULL && G.vertices[p->adjvex].data.key == v) { //如果删除的结点在第一个位置
			G.vertices[i].firstarc = p->nextarc;
			free(p);
			del_arc_2++; //删除了一个边，有重复
		} else if (p)

			while (p->nextarc) {
				if (G.vertices[p->nextarc->adjvex].data.key == v) {
					ArcNode *temp = p->nextarc;
					p->nextarc = temp->nextarc;
					free(temp);
					del_arc_2++;
					temp = NULL;
				} else
					p = p->nextarc;
			}
	}

	for (int i = 0; i < G.vexnum; i++) {
		ArcNode *p = G.vertices[i].firstarc; //将剩余的顶点重新分配序号

		while (p) {
			if (p->adjvex > k)
				p->adjvex--;
			p = p->nextarc;
		}
	}

	for (int i = k; i < G.vexnum - 1; i++) { //将被删结点之后的结点前移
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;
	G.arcnum = G.arcnum - del_arc_2 / 2;
	if (G.vexnum == 0) //图中已经删除完顶点
		return ERROR;
	return OK;
}

//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
status InsertArc(ALGraph &G, KeyType v, KeyType w) {
	if (v == w) //插入的边是环则插入失败
		return ERROR;
	for (int i = 0; i < G.vexnum; i++)
		if (v == G.vertices[i].data.key) //找到了插入边相邻的第一个结点
			for (int j = 0; j < G.vexnum; j++)
				if (w == G.vertices[j].data.key) { //找到了插入边相邻的第二个结点
					ArcNode *p = G.vertices[i].firstarc;
					while (p) {
						if (p->adjvex == j) //插入的边已经存在
							return ERROR;
						p = p->nextarc;
					} //退出循环，说明插入的边不存在
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->adjvex = i;
					p->nextarc = G.vertices[j].firstarc;
					G.vertices[j].firstarc = p;
					p = (ArcNode *)malloc(sizeof(ArcNode));
					p->adjvex = j;
					p->nextarc = G.vertices[i].firstarc;
					G.vertices[i].firstarc = p;
					G.arcnum++;
					return OK;
				}
	return ERROR;
}

//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
	int k = 0;

	for (int i = 0; i < G.vexnum; i++) {

		if (v == G.vertices[i].data.key) { //找到了第一个顶点的位置
			for (int j = 0; j < G.vexnum; j++) {
				if (w == G.vertices[j].data.key) { //找到了第二个顶点的位置
					ArcNode *p = G.vertices[i].firstarc;
					ArcNode *p_last = p;
					while (p) {
						if (p->adjvex == j) {
							if (p == p_last) {
								G.vertices[i].firstarc = p->nextarc;
								free(p);
								k++;
								break;
							} else {
								p_last->nextarc = p->nextarc;
								free(p);
								k++;
								break;
							}
						}
						p_last = p;
						p = p->nextarc;
					}
				}
			}
		} else if (w == G.vertices[i].data.key) {
			for (int j = 0; j < G.vexnum; j++) {
				if (v == G.vertices[j].data.key) { //找到了第二个顶点的位置
					ArcNode *p = G.vertices[i].firstarc;
					ArcNode *p_last = p;
					while (p) {
						if (p->adjvex == j) {
							if (p == p_last) {
								G.vertices[i].firstarc = p->nextarc;
								free(p);
								k++;
								break;
							} else {
								p_last->nextarc = p->nextarc;
								free(p);
								k++;
								break;
							}
						}
						p_last = p;
						p = p->nextarc;
					}
				}
			}
		}
	}
	if (k == 0)
		return ERROR;
	G.arcnum--;
	return OK;
}

//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
KeyType visited[maxsize] = {0}; //储存已经被访问过的结点
status DFSTraverse(ALGraph &G, int u) {
	printf("%d ", u);
	visited[u] = 1;
	ArcNode *p = G.vertices[u].firstarc;
	while (p) {
		if (visited[p->adjvex] == 0) {
			DFSTraverse(G, p->adjvex);
		}
		p = p->nextarc;
	}
	return OK;
}

//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
status BFSTraverse(ALGraph &G) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		visited[i] = 0;

	for (int i = 0; i < G.vexnum; i++) {

		if (visited[i] == 0) { //该结点
			visit(G.vertices[i].data);
			visited[i] = 1;
		}
		ArcNode *p = G.vertices[i].firstarc;

		while (p) {
			if (visited[p->adjvex] == 0) { //该结点的相邻结点还未被访问过
				visit(G.vertices[p->adjvex].data);
				visited[p->adjvex] = 1;
			}
			p = p->nextarc;
		}
	}
	return OK;
}

//求距离小于k的顶点集合，返回值为顶点个数，获取失败则返回ERROR
int VerticesSetLessThanK(ALGraph G, VertexType *V, KeyType v, int k) {
	int index = -1, num = 0, s = 1; //s是当前顶点距离目标顶点的路程，num记录总顶点个数
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			index = i;
	if (index == -1)
		return ERROR;
	KeyType visited[MAX_VERTEX_NUM] = {0}; //当结点未访问时是0，被访问过，则变为1，
	KeyType distance[MAX_VERTEX_NUM]; //记录与目标结点的距离
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		distance[i] = -1;
	visited[index] = 1;
	distance[index] = 0;
	V[num++] = G.vertices[index].data;
	while (s < k) { //求小于等于k的路径
		for (int i = 0; i < G.vexnum; i++) {
			if (distance[i] == s - 1) { //在上一轮刚被标记或者是第一轮
				ArcNode *p = G.vertices[i].firstarc;
				while (p) {
					if (visited[p->adjvex] == 0) { //未被访问
						visited[p->adjvex] = 1;
						distance[p->adjvex] = s;
						V[num++] = G.vertices[p->adjvex].data;
					}
					p = p->nextarc;
				}
			}
		}
		s++;
	}
	return num;
}

//求两个顶点的最短路径，返回值为两顶点距离，采用狄克斯特拉算法
int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
	int distance[MAX_VERTEX_NUM], visited[MAX_VERTEX_NUM] = {0};
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		distance[i] = -1;
	int index = -1, s = 1, flag = 0; //flag保证在一次操作中不是没有执行任务，s是当前路径长度
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			index = i;
	if (index == -1) //v顶点不存在
		return ERROR;
	visited[index] = 1;
	distance[index] = 0;
	while (1) {    //求小于等于k的路径
		flag = 0;
		for (int i = 0; i < G.vexnum; i++) {
			if (distance[i] == s - 1) { //在上一轮刚被标记或者是第一轮
				ArcNode *p = G.vertices[i].firstarc;
				while (p) {
					if (G.vertices[p->adjvex].data.key == w) { //找到了需要访问的另一个顶点
						return s;
					}
					if (visited[p->adjvex] == 0) { //未被访问
						visited[p->adjvex] = 1;
						distance[p->adjvex] = s;
						flag = 1; //表示有新的顶点被访问，则继续进行下一次循环，否则结束函数
					}

					p = p->nextarc;
				}
			}
		}
		if (flag == 0)
			return ERROR;
		s++;
	}
}

int main( ) {
	ALGraph G;
	int op = 1;
	int j, i = 0, begin = 0, k;
	KeyType v, w, u;
	VertexType V[30], value;
	KeyType VR[100][2];
	while (op) {
		system("cls");
		printf("\n");
		printf("   Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("    	1. CreateCraph （创建图）\n");
		printf("        2. DestroyGraph （销毁图）\n");
		printf("    	3. LocateVex （查找顶点）\n");
		printf("        4. PutVex  （顶点赋值）\n");
		printf("    	5. FirstAdjVex （获得第一邻接顶点）\n");
		printf("        6. NextAdjVex （获得下一邻接顶点）\n");
		printf("    	7. InsertVex （插入顶点）\n");
		printf("        8. DeleteVex （删除顶点）\n");
		printf("    	9. InsertArc （插入弧）\n");
		printf("        10.DeleteArc （删除弧）\n");
		printf("    	11.DFSTraverse （深度优先遍历）\n");
		printf("        12.BFSTraverse （广度优先遍历）\n");
		printf("        13.VertexType （距离小于k的顶点集）\n");
		printf("        14.ShortestPathLength （顶点最短路径）\n");
		printf("        20.print （输出结点信息）\n");
		printf("        0. Exit （退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("   请选择你的操作[0~14]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				if (begin == 1) {
					printf("创建失败，图已存在\n");
				} else {
					printf("请输入顶点数据\n");
					do {
						scanf("%d%s", &V[i].key, V[i].others);
					} while (V[i++].key != -1);
					i = 0;
					printf("请输入边的数据\n");
					do {
						scanf("%d%d", &VR[i][0], &VR[i][1]);
					} while (VR[i++][0] != -1);
					j = CreateCraph(G, V, VR);
					if (j == OK) {
						printf("创建成功");
						begin = 1;
					} else
						printf("创建失败");
				}
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyGraph(G);
				if ( j == OK) {
					printf("图销毁成功！\n");
					begin = 0;
				} else
					printf("图销毁失败！\n");
				getchar();
				getchar();
				break;
			case 3:
				printf("请输入想要查找的关键字");
				scanf("%d", &u);
				j = LocateVex(G, u);
				if (j == -1)
					printf("查找失败");
				else
					printf("查找成功\n%d %s", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 4:
				printf("输入顶点关键字并赋值\n");
				scanf("%d %d %s", &u, &value.key, value.others);
				j = PutVex(G, u, value);
				if (j == OK)
					printf("赋值成功\n");
				else
					printf("赋值失败！\n");
				getchar();
				getchar();
				break;
			case 5:
				printf("输入获取的关键字\n");
				scanf("%d", &u);
				j = FirstAdjVex(G, u);
				if ( j == -1)
					printf("查找失败\n");
				else
					printf("查找成功\n%d %s\n", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 6:
				printf("输入关键字的下一邻接点\n");
				scanf("%d %d", &v, &w);
				j = NextAdjVex(G, v, w);
				if ( j == -1)
					printf("获取失败\n");
				else
					printf("获取成功\n%d %s\n", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 7:
				printf("输入要插入的顶点关键字\n");
				scanf("%d %s", &value.key, value.others);
				j = InsertVex(G, value);
				if (j == OK)
					printf("插入成功\n");
				else
					printf("插入失败\n");
				getchar();
				getchar();
				break;
			case 8:
				printf("输入要删除的关键字\n");
				scanf("%d", &v);
				j = DeleteVex(G, v);
				if (j == ERROR)
					printf("删除失败");
				else
					printf("删除成功");
				getchar();
				getchar();
				break;
			case 9:
				printf("输入要插入的边\n");
				scanf("%d %d", &v, &w);
				j = InsertArc(G, v, w);
				if (j == ERROR)
					printf("插入失败");
				else
					printf("插入成功");
				getchar();
				getchar();
				break;
			case 10:
				printf("输入要删除的边\n");
				scanf("%d %d", &v, &w);
				j = DeleteArc(G, v, w);
				if (j == OK)
					printf("删除成功！\n");
				else
					printf("删除失败！\n");
				getchar();
				getchar();
				break;
			case 11:
				printf("深度优先遍历：\n");
				DFSTraverse(G, 0);
				for (i = 0; i < MAX_VERTEX_NUM; i++)
					visited[i] = 0;
				getchar();
				getchar();
				break;
			case 12:
				printf("广度优先遍历：\n");
				BFSTraverse(G);
				for (i = 0; i < MAX_VERTEX_NUM; i++)
					visited[i] = 0;
				getchar();
				getchar();
				break;
			case 13:
				printf("输入顶点关键字以及距离:\n");
				scanf("%d %d", &v, &k);
				for (i = 0; i < 30; i++) {
					V[i].key = 0;
					strcpy(V[i].others, "\0");
				}
				j = VerticesSetLessThanK(G, V, v, k);
				if (j == ERROR) {
					printf("获取失败");
				} else {
					printf("以获得顶点集V\n总个数为%d\n", j);
					for (i = 0; i < j; i++) {
						visit(V[i]);
					}
				}
				getchar();
				getchar();
				break;
			case 14:
				printf("输入两个顶点关键字:\n");
				scanf("%d %d", &v, &w);
				j = ShortestPathLength(G, v, w);
				if (j == ERROR) {
					printf("获取失败");
				} else {
					printf("最短距离为%d\n", j);
				}
				getchar();
				getchar();
				break;
			case 20:
				print(G);
				getchar();
				getchar();
				break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main()

/*
5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 7 8 -1 -1
*/