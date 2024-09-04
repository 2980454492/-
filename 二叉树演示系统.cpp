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

typedef struct BiTNode { //����������Ķ���
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void visit(BiTree T) { //����������
	printf("%d ", T->data.key);
}

status CreateBiTree(BiTree &T, TElemType definition[], int begin) {
//��ʼ�������������Ѵ���
//�����������definition���������T
	for (int i = 0; definition[i].key != -1; i++) {     //����Ƿ��йؼ�����ͬ�Ľ��
		for (int j = i + 1; definition[j].key != -1; j++) {
			if (definition[i].key == definition[j].key && definition[i].key != 0) {
				return ERROR;
			}
		}
	}
	static int k = 0;                  //��̬���������ڵݹ���k��ֵ���Դ����ϲ㺯��
	if (definition[k].key == -1) {
		return OK;
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	if (definition[k].key != 0) {          //��һ����㲻Ϊ��
		T->data.key = definition[k].key;
		strcpy(T->data.others, definition[k].others);
		k++;
		CreateBiTree(T->lchild, definition, begin + 1);
		CreateBiTree(T->rchild, definition, begin + 1);
	} else {           //��һ���Ϊ��
		k++;
		T = NULL;
	}
	if (begin == 1)
		k = 0;
	return OK;
}

status DestroyBiTree(BiTree &T) {
//��ʼ������������T�Ѵ���
//������������ٶ�����T
	if (T == NULL)
		return OK;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}

status ClearBiTree(BiTree &T) {
//��ʼ������������T�Ѵ���
//�����������������T���Ϊ����
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
//��ʼ������������T�Ѵ���
//�����������TΪ�ն��������򷵻�OK�����򷵻�ERROR
	if (T == NULL)
		return OK;
	else
		return ERROR;
}

int BiTreeDepth(BiTree T) {
//��ʼ������������T�Ѵ���
//�������������T�����
	if (T == NULL) {
		return 0;
	}
	int ldeep = 1 + BiTreeDepth(T->lchild);
	int rdeep = 1 + BiTreeDepth(T->rchild);
	return ldeep > rdeep ? ldeep : rdeep;
	/********** End **********/
}

int NodeDepth(BiTree T, KeyType e) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ���
//�������������Node�������
	if (T == NULL)
		return 0;
	if (T->data.key == e)
		return 1;
	int deep = NodeDepth(T->lchild, e) + NodeDepth(T->rchild, e);
	return deep == 0 ? 0 : deep + 1;
}

BiTNode *LocateNode(BiTree T, KeyType e) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ���
//������������ظý��ָ��
	if (T == NULL) { //�Ѿ�����Ҷ�ӽ�㣬�ͷ��ؿս��
		return NULL;
	}
	if (T->data.key == e) { //�ҵ��ˣ��򷵻ظý��
		return T;
	} else { //û���ҵ�����������Ѱ��
		BiTNode *leftResult = LocateNode(T->lchild, e);
		BiTNode *rightResult = LocateNode(T->rchild, e);
		if (leftResult != NULL) { //����������˵���ҵ���
			return leftResult; //���ظո��ҵ��Ľ��
		} else { //����������δ�ҵ�������������ҵ��ͷ����ҵ��Ľ�㣬δ�ҵ��ͷ��ؿ�
			return rightResult;
		}
	}
}

BiTNode *LocateParent(BiTree T, KeyType e, int k) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ���
//������������ظ����ָ��
	if (T == NULL)
		return NULL;
	if (T->data.key == e) { //k�ж��Ƿ�Ϊͷ���
		return k == 1 ? NULL : T;
	}
	BiTree Node = LocateNode(T, e);
	if (Node == NULL) //e��ֵ����ȷ
		return NULL;
	BiTree leftNode = LocateParent(T->lchild, e, k + 1);
	if (leftNode != NULL) { //e��T����������
		return T->lchild == Node ? T : leftNode;
	}
	BiTree rightNode = LocateParent(T->rchild, e, k + 1);
	if (rightNode != NULL) { //e��T����������
		return T->rchild == Node ? T : rightNode;
	}
	return NULL;
}

BiTNode *LocateBrother(BiTree T, KeyType e) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ���
//�������������ֵΪ�ֵܽ���ָ��
	BiTree ParentNode = LocateParent(T, e, 1);
	if (!ParentNode) //e�ĸ���㲻���ڣ��п�����e��ֵ����ȷ��e��ͷ���
		return NULL;
	BiTree Node = LocateNode(T, e); //eһ�������Ҳ�Ϊͷ��㣬Ҳһ�����ֵܽ��
	if (Node == ParentNode->lchild)
		return ParentNode->rchild;
	else
		return ParentNode->lchild;
}

status UnExistNode(BiTree T, KeyType value) {
//��ʼ�������������Ѵ���
//�����������value��T�д��ڣ��򷵻�ERROR�����򷵻�OK
	if (T == NULL) { //���˿ս��
		return OK;
	}
	if (T->data.key == value) { //�ؼ��ִ���
		return ERROR; //��ֵʧ�ܣ�����0
	}
	int ans = 1 * UnExistNode(T->lchild, value) * UnExistNode(T->rchild, value);
	//���ó˷���ֻҪ�ؼ��ִ��ھ�ʧ��
	if (ans == 0) //�ؼ��ִ���
		return ERROR;
	else //�ؼ��ֲ�����
		return OK;
}


status Assign(BiTree &T, KeyType e, TElemType value) {
//��ʼ������������T�Ѵ��ڣ�e��ĳ�����ؼ��֣�value�Ĺؼ�����T���ظ�
//�����������value����e�Ľ������
	BiTree Node = LocateNode(T, e); //�ҹؼ���Ϊe�Ľ��
	if (!Node) //e��ֵ����ȷ������ERROR
		return ERROR;
	if (!UnExistNode(T, value.key) && value.key != Node->data.key) { //�ؼ����ظ��Ҳ���e
		return ERROR; //��ֵʧ�ܣ�����0
	}
	Node->data = value;
	return OK;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ��֣�c�еĹؼ�����T���ظ�
//���������LR=0��1������cΪe������������������eԭ�е�����������������Ϊc��������
//LR=-1���뵽ͷ��㣬ԭ��������Ϊc��������
	if (LR == -1) { //����Ľ����ͷ���
		BiTree temp = (BiTree)malloc(sizeof(BiTNode));
		temp->data = c;
		temp->lchild = NULL;
		temp->rchild = T; //ԭ�������½���������
		T = temp;
		return OK;
	}
	BiTree Node = LocateNode(T, e); //�ҵ���Ҫ������ĸ����
	if (!Node) //e��ֵ����
		return 0;
	if (!UnExistNode(T, c.key) && c.key != Node->data.key) { //�ؼ����ظ��Ҳ���e
		return ERROR; //��ֵʧ�ܣ�����0
	}
	BiTree temp = (BiTree)malloc(sizeof(BiTNode));
	temp->data = c;
	temp->lchild = NULL;
	if (LR == 0) { //����
		temp->rchild = Node->lchild;
		Node->lchild = temp;
	} else if (LR == 1) { //�Һ���
		temp->rchild = Node->rchild;
		Node->rchild = temp;
	}
	return OK;
}

status DeleteNode(BiTree &T, KeyType e, int k) {
//��ʼ������������T�Ѵ��ڣ�e��T��ĳ�����ؼ���
//���������e��Ҷ�ӽ�㣬ֱ��ɾ����ֻ����������������������������������������e��λ�ã�
//����������������������������������e�����������뵽�����������ҽ���������
	if (T == NULL)
		return 0;
	if (e == T->data.key) { //�жϵĽ�������Ҫɾ���Ľ��
		if (k == 1) { //k���������ж�e�Ƿ�Ϊͷ���
			int ans = DeleteNode(T, e, k + 1); //�ݹ��Լ�������ͷ���ĺ��ӻ���ͷ���
			if (ans == OK) { //ͷ���
				return OK;
			} else if (ans == 2) { //ͷ�����ǹ������
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
		} else if (T->lchild == NULL && T->rchild == NULL) { //e��Ҷ�ӽ��
			free(T);
			T = NULL;
			return 2;
		} else if (T->lchild != NULL && T->rchild != NULL) { //e���Һ��Ӷ�����
			BiTree temp = T->lchild;
			while (temp->rchild) { //�ҵ�T�����������Ҳ࣬��Ҫ�ں������T��������
				temp = temp->rchild;
			}
			temp->rchild = T->rchild;
			return 3;
		} else if (T->lchild == NULL) { //ֻ���Һ���
			return 4;
		} else { //ֻ������
			return 3;
		}
	}
	int lans = DeleteNode(T->lchild, e, k + 1); //���

	if (lans == OK) { //OK˵���Ѿ����ɾ��������ֻ��һ�����˳��ݹ�
		return OK;

	} else if (lans == 2) { //e��Ҷ�ӽ�㣬ɾ����T����������Ϊ��
		T->lchild == NULL;
		return OK;

	} else if (lans == 3) { //��Ҫ��T�����������e��������
		BiTree temp = T->lchild;
		T->lchild = temp->lchild;
		free(temp);
		temp = NULL;
		return OK;

	} else if (lans == 4) { //��Ҫ��T�����������e��������
		BiTree temp = T->lchild;
		T->lchild = temp->rchild;
		free(temp);
		temp = NULL;
		return OK;
	} //��T���������в�δ�ҵ�e
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
//��ʼ������������T�Ѵ���
//����������������������T
	if (T == NULL)
		return ERROR;
	visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

status InOrderTraverse(BiTree T) {
//��ʼ������������T�Ѵ���
//����������������������T
	if (T == NULL)
		return ERROR;
	InOrderTraverse(T->lchild);
	visit(T);
	InOrderTraverse(T->rchild);
	return OK;
}

status PostOrderTraverse(BiTree T) {
//��ʼ������������T�Ѵ���
//����������������������T
	if (T == NULL)
		return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	visit(T);
	return OK;
}

status LevelOrderTraverse(BiTree T) {
//��ʼ������������T�Ѵ���
//����������������������T
	if (T == NULL)
		return ERROR;
	BiTree Queue[20]; //����һ���Ƚ��ȳ��Ķ���
	int i = 0, k = 0;
	Queue[i++] = T;

	while (k < i) {
		BiTree current = Queue[k++]; //���δ�ǰ������ʶ���
		visit(current);
		if (current->lchild) //��������������Ϣ��ֵ�����е�ĩβ
			Queue[i++] = current->lchild;
		if (current->rchild) //���Һ�����������Ϣ��ֵ�����е�ĩβ
			Queue[i++] = current->rchild;
	}
	return OK;
}

status InvertTree(BiTree &T) {
//��ʼ������������T�Ѵ���
//�����������������T������������λ��
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
//��ʼ������������T�Ѵ���
//��������������������e1��e2���������
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
//��ʼ������������T�Ѵ���
//���������������T��Ϊ�����������򷵻�OK�����򷵻�ERROR
	//�������������������k��֤�ȱ����Ľ��С�ں�����Ľ��
	int ans = 1; //���ó˷���ֻҪ����һ�β����϶�������Ľ��͵���0������͵���1
	if (T == NULL) //�ҵ��ս��
		return OK;
	ans *= JudgeBiTree(T->lchild); //���ȷ����������еĽ��

	if (T->data.key >= k) { //��ǰ�������ݴ���֮ǰ���ʵĽ��
		k = T->data.key;
	} else //��������ֱ�ӷ���0��
		return ERROR;
	ans *= JudgeBiTree(T->rchild);
	return ans; //�ɹ�����1��ʧ�ܷ���0
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
		printf("    	1. CreateBiTree ��������������\n");
		printf("        2. DestroyBiTree �����ٶ�������\n");
		printf("    	3. ClearBiTree ����ն�������\n");
		printf("        4. BiTreeEmpty ���������пգ�\n");
		printf("    	5. BiTreeDepth �����������ȣ�\n");
		printf("        6. LocateNode �����ҽ�㣩\n");
		printf("    	7. Assign ����㸳ֵ��\n");
		printf("        8. LocateBrother ����ȡ�ֵܽ�㣩\n");
		printf("    	9. InsertNode �������㣩\n");
		printf("        10.DeleteNode ��ɾ����㣩\n");
		printf("    	11.PreOrderTraverse ��ǰ�������\n");
		printf("        12.InOrderTraverse �����������\n");
		printf("        13.PostOrderTraverse �����������\n");
		printf("        14.LevelOrderTraverse �����������\n");
		printf("        15.InvertTree ����ת��������\n");
		printf("        16.LocateParent ����ȡ���׽�㣩\n");
		printf("        17.NodeDepth ���������ȣ�\n");
		printf("        18.LocateCommonAncestor ����ȡ������ȣ�\n");
		printf("        19.JudgeBiTree ���ж϶�����������\n");
		printf("        0. Exit ���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~19]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				if (begin != 0) {
					printf("����ʧ�ܣ��������Ѵ���");
				} else {
					printf("��������Ϊ������������������������������\n�ؼ���Ϊ0ʱ����ʾ��������Ϊ -1��ʾ�������\n");
					TElemType definition[100];
					do {
						scanf("%d%s",
						      &definition[i].key, definition[i].others);
						printf("������һ�������\n");
					} while (definition[i++].key != -1);
					ans = CreateBiTree(T, definition, 1);
					if (ans == OK) {
						printf("�����ɹ�");
					} else
						printf("�ؼ��ֲ�Ψһ");
					begin++;
				}
				i = 0;
				getchar();
				getchar();
				break;
			case 2:
				if (T == NULL)
					printf("����ʧ��");
				else {
					ans = DestroyBiTree(T);
					if (ans == OK)
						printf("���ٳɹ�");
					begin--;
				}
				getchar();
				getchar();
				break;
			case 3:
				if (T == NULL)
					printf("���ʧ��");
				else {
					ans = ClearBiTree(T);
					if (ans == OK)
						printf("����ɹ�");
				}
				getchar();
				getchar();
				break;
			case 4:
				ans = BiTreeEmpty(T);
				if (ans == OK)
					printf("������Ϊ��");
				else
					printf("��������Ϊ��");
				getchar();
				getchar();
				break;
			case 5:
				ans = BiTreeDepth(T);
				printf("���������Ϊ%d", ans);
				getchar();
				getchar();
				break;
			case 6:
				printf("��������Ҫ���ҵĹؼ���\n");
				scanf("%d", &e);
				getT = LocateNode(T, e);
				if (getT == NULL)
					printf("δ�ҵ�");
				else {
					printf("�ҵ���\n");
					visit(getT);
				}
				getchar();
				getchar();
				break;
			case 7:
				printf("�����븳ֵ�Ĺؼ��֣��¸�ֵ������\n");
				scanf("%d %d %s", &e, &value.key, value.others);
				ans = Assign(T, e, value);
				if (ans == 1)
					printf("��ֵ�ɹ�");
				else
					printf("��ֵʧ��");
				getchar();
				getchar();
				break;
			case 8:
				printf("������ؼ���");
				scanf("%d", &e);
				getT = LocateBrother(T, e);
				if (getT == NULL)
					printf("���ֵܽڵ�");
				else
					printf("���ҵ�����%d���ֵܽڵ�Ϊ%d,%s",
					       e, getT->data.key, getT->data.others);
				getchar();
				getchar();
				break;
			case 9:
				printf("������ؼ��֡����ҡ���������\n");
				scanf("%d %d %d %s", &e, &LR, &value.key, value.others);
				ans = InsertNode(T, e, LR, value);
				if (ans == 0)
					printf("����ʧ��");
				else
					printf("����ɹ�");
				getchar();
				getchar();
				break;
			case 10:
				printf("��������Ҫɾ���Ľ��Ĺؼ���\n");
				scanf("%d", &e);
				ans = DeleteNode(T, e, 1);
				if (ans == 0)
					printf("ɾ��ʧ��");
				else
					printf("ɾ���ɹ�");
				getchar();
				getchar();
				break;
			case 11:
				printf("�������:");
				ans = PreOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 12:
				printf("�������:");
				ans = InOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 13:
				printf("�������:");
				ans = PostOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 14:
				printf("�������:");
				ans = LevelOrderTraverse(T);
				getchar();
				getchar();
				break;
			case 15:
				ans = InvertTree(T);
				printf("��ת�ɹ�");
				getchar();
				getchar();
				break;
			case 16:
				printf("����Ҫ��ȡ���׽��Ĺؼ���\n");
				scanf("%d", &e);
				getT = LocateParent(T, e, 1);
				if (getT) {
					printf("%d�ĸ��׽����");
					visit(getT);
				} else
					printf("��ȡʧ��");
				getchar();
				getchar();
				break;
			case 17:
				printf("����Ҫ��ȡ��ȵĽ��ؼ���\n");
				scanf("%d", &e);
				ans = NodeDepth(T, e);
				if (ans == ERROR)
					printf("��ȡʧ�ܣ��ؼ��ֲ�����");
				else
					printf("%d�����Ϊ%d", e, ans);
				getchar();
				getchar();
				break;
			case 18:
				printf("����Ҫ��ȡ���ȵ��������\n");
				scanf("%d %d", &e, &e2);
				getT = LocateCommonAncestor(T, e, e2);
				if (getT == NULL)
					printf("��ȡʧ�ܣ��ؼ��ֲ�����");
				else {
					printf("�������Ϊ");
					visit(getT);
				}
				getchar();
				getchar();
				break;
			case 19:
				ans = JudgeBiTree(T);
				if (ans == ERROR)
					printf("���Ƕ���������");
				else
					printf("�Ƕ���������");
				k = 0; //���þ�̬��������ֹ��һ��ʹ�øú������ִ���
				getchar();
				getchar();
				break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main()

/*
1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null

2 a 1 b 0 null  0 null 4 c 3 d  0 null  0 null 5 e  0 null  0 null -1 null
*/