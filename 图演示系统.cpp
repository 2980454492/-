#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 20

typedef enum {DG, DN, UDG, UDN} GraphKind; //����ͼ��������������ͼ��������
typedef int status;
typedef int KeyType;

//�������Ͷ���
typedef struct {
	KeyType  key;
	char others[20];
} VertexType;

//�������Ͷ���
typedef struct ArcNode {
	int adjvex; //����λ�ñ��
	struct ArcNode  *nextarc; //��һ������ָ��
} ArcNode;

//ͷ��㼰���������Ͷ���
typedef struct VNode {
	VertexType data; //������Ϣ
	ArcNode *firstarc; //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];

//�ڽӱ�����Ͷ���
typedef  struct {
	AdjList vertices; //ͷ�������
	int vexnum, arcnum; //������������
	GraphKind kind; //ͼ�������־
} ALGraph;

//���ʶ���
void visit(VertexType v) {
	printf("%d %s  ", v.key, v.others);
}

//���������Ϣ�Լ����ӵ�������������
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

//����V��VR����ͼG������OK
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
	if (V[0].key == -1)
		return ERROR;//����ĵ㼯Ϊ��
	int i, j, one = -1, two = -1, flag = 0;
	for (i = 0; VR[i][0] != -1; i++); //�������
	G.arcnum = i;
	for (i = 0; V[i].key != -1; i++); //�������
	if (i > MAX_VERTEX_NUM) //�������������Ķ�����ʱ
		return ERROR;
	G.vexnum = i;
	for (i = 0; i < G.vexnum - 1; i++) //�ж��Ƿ��в�ͬ���ؼ�����ͬ
		for (j = i + 1; j < G.vexnum; j++)
			if (V[i].key == V[j].key)
				return ERROR;

	for (i = 0; i < G.arcnum; i++) { //�жϱ����ӵĶ����Ƿ����
		for (j = 0; j < G.vexnum; j++) {
			if (VR[i][0] == V[j].key)
				break;
		}
		if (j == G.vexnum) { //�������㼯û���ҵ��ñ����ӵĶ���
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

	for (i = 0; i < G.vexnum; i++) { //���㸳ֵ��ͼ
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	}

	for (i = 0; i < G.arcnum; i++) { //����ͷ�巨�������ڱߣ��Ȳ���Ľ������
		flag = 0;
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][0] == G.vertices[j].data.key) { //�ҵ��ߵĵ�һ�������ڶ��㼯�е�λ��
				one = j;
				break;
			}
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][1] == G.vertices[j].data.key) { //�ҵ��ߵĵڶ��������ڶ��㼯�е�λ��
				two = j;
				break;
			}
		if (one == two) //�����򲻲���
			continue;
		ArcNode *q = G.vertices[one].firstarc;
		while (q) {
			if (q->adjvex == two) { //�ý������ڽ���Ѿ����ֹ�
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

//��������ͼG,ɾ��G��ȫ������ͱߣ�G�����ڷ���ERROR�����ڲ�ɾ���ɹ�����OK
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

//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1
int LocateVex(ALGraph G, KeyType u) {
	for (int i = 0; i < G.vexnum; i++) {
		if (u == G.vertices[i].data.key) {
			return i;
		}
	}
	return -1;
}

//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERRO
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

//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
int FirstAdjVex(ALGraph G, KeyType u) {
	for (int i = 0; i < G.vexnum; i++) {
		if (u == G.vertices[i].data.key) {
			return G.vertices[i].firstarc->adjvex;
		}
	}
	return -1;
}

//v��ӦG��һ������,w��Ӧv���ڽӶ��㣻
//��������Ƿ���v�ģ������w����һ���ڽӶ����λ��
//���w�����һ���ڽӶ��㣬��v��w��Ӧ���㲻���ڣ��򷵻�-1��
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

//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
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

//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
status DeleteVex(ALGraph &G, KeyType v) {
	int pre_vexnum = G.vexnum; //����ԭʼ�Ľ�����
	int del_arc_2 = 0; //��¼��ɾ�ı���
	int k, i; //��¼��ɾ����λ�����
	for (i = 0; i < G.vexnum; i++) { //�ҵ���ɾ��㲢ɾ���������֮����ǰ��
		if (G.vertices[i].data.key == v) { //�ҵ�����Ҫɾ�Ľ��
			k = i;
			ArcNode *temp = G.vertices[i].firstarc;
			while (temp) {
				G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc; //����ɾ�����Ӹý������б�
				free(temp);
				temp = G.vertices[i].firstarc;
				del_arc_2++;
			}
			break;
		}
	}
	if (i == G.vexnum) //û�н�㱻ɾ��������������Ĺؼ��ֲ����ڽ����
		return ERROR;

	for (int i = 0; i < G.vexnum; i++) { //ɾ��������������ö���������ı�
		if (G.vertices[i].data.key == v)
			continue; //����ɾ�����
		ArcNode *p = G.vertices[i].firstarc; //ɾ����������еĸñ�

		if (p != NULL && G.vertices[p->adjvex].data.key == v) { //���ɾ���Ľ���ڵ�һ��λ��
			G.vertices[i].firstarc = p->nextarc;
			free(p);
			del_arc_2++; //ɾ����һ���ߣ����ظ�
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
		ArcNode *p = G.vertices[i].firstarc; //��ʣ��Ķ������·������

		while (p) {
			if (p->adjvex > k)
				p->adjvex--;
			p = p->nextarc;
		}
	}

	for (int i = k; i < G.vexnum - 1; i++) { //����ɾ���֮��Ľ��ǰ��
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;
	G.arcnum = G.arcnum - del_arc_2 / 2;
	if (G.vexnum == 0) //ͼ���Ѿ�ɾ���궥��
		return ERROR;
	return OK;
}

//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
status InsertArc(ALGraph &G, KeyType v, KeyType w) {
	if (v == w) //����ı��ǻ������ʧ��
		return ERROR;
	for (int i = 0; i < G.vexnum; i++)
		if (v == G.vertices[i].data.key) //�ҵ��˲�������ڵĵ�һ�����
			for (int j = 0; j < G.vexnum; j++)
				if (w == G.vertices[j].data.key) { //�ҵ��˲�������ڵĵڶ������
					ArcNode *p = G.vertices[i].firstarc;
					while (p) {
						if (p->adjvex == j) //����ı��Ѿ�����
							return ERROR;
						p = p->nextarc;
					} //�˳�ѭ����˵������ı߲�����
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

//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
	int k = 0;

	for (int i = 0; i < G.vexnum; i++) {

		if (v == G.vertices[i].data.key) { //�ҵ��˵�һ�������λ��
			for (int j = 0; j < G.vexnum; j++) {
				if (w == G.vertices[j].data.key) { //�ҵ��˵ڶ��������λ��
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
				if (v == G.vertices[j].data.key) { //�ҵ��˵ڶ��������λ��
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

//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
KeyType visited[maxsize] = {0}; //�����Ѿ������ʹ��Ľ��
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

//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
status BFSTraverse(ALGraph &G) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		visited[i] = 0;

	for (int i = 0; i < G.vexnum; i++) {

		if (visited[i] == 0) { //�ý��
			visit(G.vertices[i].data);
			visited[i] = 1;
		}
		ArcNode *p = G.vertices[i].firstarc;

		while (p) {
			if (visited[p->adjvex] == 0) { //�ý������ڽ�㻹δ�����ʹ�
				visit(G.vertices[p->adjvex].data);
				visited[p->adjvex] = 1;
			}
			p = p->nextarc;
		}
	}
	return OK;
}

//�����С��k�Ķ��㼯�ϣ�����ֵΪ�����������ȡʧ���򷵻�ERROR
int VerticesSetLessThanK(ALGraph G, VertexType *V, KeyType v, int k) {
	int index = -1, num = 0, s = 1; //s�ǵ�ǰ�������Ŀ�궥���·�̣�num��¼�ܶ������
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			index = i;
	if (index == -1)
		return ERROR;
	KeyType visited[MAX_VERTEX_NUM] = {0}; //�����δ����ʱ��0�������ʹ������Ϊ1��
	KeyType distance[MAX_VERTEX_NUM]; //��¼��Ŀ����ľ���
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		distance[i] = -1;
	visited[index] = 1;
	distance[index] = 0;
	V[num++] = G.vertices[index].data;
	while (s < k) { //��С�ڵ���k��·��
		for (int i = 0; i < G.vexnum; i++) {
			if (distance[i] == s - 1) { //����һ�ָձ���ǻ����ǵ�һ��
				ArcNode *p = G.vertices[i].firstarc;
				while (p) {
					if (visited[p->adjvex] == 0) { //δ������
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

//��������������·��������ֵΪ��������룬���õҿ�˹�����㷨
int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
	int distance[MAX_VERTEX_NUM], visited[MAX_VERTEX_NUM] = {0};
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		distance[i] = -1;
	int index = -1, s = 1, flag = 0; //flag��֤��һ�β����в���û��ִ������s�ǵ�ǰ·������
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			index = i;
	if (index == -1) //v���㲻����
		return ERROR;
	visited[index] = 1;
	distance[index] = 0;
	while (1) {    //��С�ڵ���k��·��
		flag = 0;
		for (int i = 0; i < G.vexnum; i++) {
			if (distance[i] == s - 1) { //����һ�ָձ���ǻ����ǵ�һ��
				ArcNode *p = G.vertices[i].firstarc;
				while (p) {
					if (G.vertices[p->adjvex].data.key == w) { //�ҵ�����Ҫ���ʵ���һ������
						return s;
					}
					if (visited[p->adjvex] == 0) { //δ������
						visited[p->adjvex] = 1;
						distance[p->adjvex] = s;
						flag = 1; //��ʾ���µĶ��㱻���ʣ������������һ��ѭ���������������
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
		printf("    	1. CreateCraph ������ͼ��\n");
		printf("        2. DestroyGraph ������ͼ��\n");
		printf("    	3. LocateVex �����Ҷ��㣩\n");
		printf("        4. PutVex  �����㸳ֵ��\n");
		printf("    	5. FirstAdjVex ����õ�һ�ڽӶ��㣩\n");
		printf("        6. NextAdjVex �������һ�ڽӶ��㣩\n");
		printf("    	7. InsertVex �����붥�㣩\n");
		printf("        8. DeleteVex ��ɾ�����㣩\n");
		printf("    	9. InsertArc �����뻡��\n");
		printf("        10.DeleteArc ��ɾ������\n");
		printf("    	11.DFSTraverse ��������ȱ�����\n");
		printf("        12.BFSTraverse ��������ȱ�����\n");
		printf("        13.VertexType ������С��k�Ķ��㼯��\n");
		printf("        14.ShortestPathLength ���������·����\n");
		printf("        20.print ����������Ϣ��\n");
		printf("        0. Exit ���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("   ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				if (begin == 1) {
					printf("����ʧ�ܣ�ͼ�Ѵ���\n");
				} else {
					printf("�����붥������\n");
					do {
						scanf("%d%s", &V[i].key, V[i].others);
					} while (V[i++].key != -1);
					i = 0;
					printf("������ߵ�����\n");
					do {
						scanf("%d%d", &VR[i][0], &VR[i][1]);
					} while (VR[i++][0] != -1);
					j = CreateCraph(G, V, VR);
					if (j == OK) {
						printf("�����ɹ�");
						begin = 1;
					} else
						printf("����ʧ��");
				}
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyGraph(G);
				if ( j == OK) {
					printf("ͼ���ٳɹ���\n");
					begin = 0;
				} else
					printf("ͼ����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 3:
				printf("��������Ҫ���ҵĹؼ���");
				scanf("%d", &u);
				j = LocateVex(G, u);
				if (j == -1)
					printf("����ʧ��");
				else
					printf("���ҳɹ�\n%d %s", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 4:
				printf("���붥��ؼ��ֲ���ֵ\n");
				scanf("%d %d %s", &u, &value.key, value.others);
				j = PutVex(G, u, value);
				if (j == OK)
					printf("��ֵ�ɹ�\n");
				else
					printf("��ֵʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 5:
				printf("�����ȡ�Ĺؼ���\n");
				scanf("%d", &u);
				j = FirstAdjVex(G, u);
				if ( j == -1)
					printf("����ʧ��\n");
				else
					printf("���ҳɹ�\n%d %s\n", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 6:
				printf("����ؼ��ֵ���һ�ڽӵ�\n");
				scanf("%d %d", &v, &w);
				j = NextAdjVex(G, v, w);
				if ( j == -1)
					printf("��ȡʧ��\n");
				else
					printf("��ȡ�ɹ�\n%d %s\n", G.vertices[j].data.key, G.vertices[j].data.others);
				getchar();
				getchar();
				break;
			case 7:
				printf("����Ҫ����Ķ���ؼ���\n");
				scanf("%d %s", &value.key, value.others);
				j = InsertVex(G, value);
				if (j == OK)
					printf("����ɹ�\n");
				else
					printf("����ʧ��\n");
				getchar();
				getchar();
				break;
			case 8:
				printf("����Ҫɾ���Ĺؼ���\n");
				scanf("%d", &v);
				j = DeleteVex(G, v);
				if (j == ERROR)
					printf("ɾ��ʧ��");
				else
					printf("ɾ���ɹ�");
				getchar();
				getchar();
				break;
			case 9:
				printf("����Ҫ����ı�\n");
				scanf("%d %d", &v, &w);
				j = InsertArc(G, v, w);
				if (j == ERROR)
					printf("����ʧ��");
				else
					printf("����ɹ�");
				getchar();
				getchar();
				break;
			case 10:
				printf("����Ҫɾ���ı�\n");
				scanf("%d %d", &v, &w);
				j = DeleteArc(G, v, w);
				if (j == OK)
					printf("ɾ���ɹ���\n");
				else
					printf("ɾ��ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 11:
				printf("������ȱ�����\n");
				DFSTraverse(G, 0);
				for (i = 0; i < MAX_VERTEX_NUM; i++)
					visited[i] = 0;
				getchar();
				getchar();
				break;
			case 12:
				printf("������ȱ�����\n");
				BFSTraverse(G);
				for (i = 0; i < MAX_VERTEX_NUM; i++)
					visited[i] = 0;
				getchar();
				getchar();
				break;
			case 13:
				printf("���붥��ؼ����Լ�����:\n");
				scanf("%d %d", &v, &k);
				for (i = 0; i < 30; i++) {
					V[i].key = 0;
					strcpy(V[i].others, "\0");
				}
				j = VerticesSetLessThanK(G, V, v, k);
				if (j == ERROR) {
					printf("��ȡʧ��");
				} else {
					printf("�Ի�ö��㼯V\n�ܸ���Ϊ%d\n", j);
					for (i = 0; i < j; i++) {
						visit(V[i]);
					}
				}
				getchar();
				getchar();
				break;
			case 14:
				printf("������������ؼ���:\n");
				scanf("%d %d", &v, &w);
				j = ShortestPathLength(G, v, w);
				if (j == ERROR) {
					printf("��ȡʧ��");
				} else {
					printf("��̾���Ϊ%d\n", j);
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
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main()

/*
5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 nil 5 6 5 7 6 7 7 8 -1 -1
*/