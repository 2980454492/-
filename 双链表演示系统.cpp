#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

//���Ա��˫������洢�ṹ
typedef struct DuLNode {
	ElemType data; //�������
	struct DuLNode *prior; //��һ���ָ��
	struct DuLNode *next; //��һ���ָ��
} DuLNode, *DuLinkList;

status InitList_DuL(DuLinkList &L) {
//��ʼ������˫��������
//�������������һ���յ�˫����L
	if (L != NULL) { //˫����Ϊ���򷵻�ERROR
		return ERROR;
	}
	L = (DuLinkList)malloc(sizeof(DuLNode)); //��̬����ռ�
	L->data = 0; //��ʼֵ��Ϊ0��
	L->next = NULL; //�ձ���׽��ָ���
	L->prior = NULL; //�ձ���׽�����һ���ָ���
	return OK;
}

status DestroyList_DuL(DuLinkList &L) {
//��ʼ������˫����L�Ѵ���
//���������ɾ��˫����
	if (L == NULL) { //˫��������
		return ERROR;
	}
	DuLinkList ne, q = L->next; //ǰ����
	while (q) { //ǰ��㲻Ϊ��
		ne = q->next; //���㸳ֵ
		free(q); //ɾ��ǰ���
		q = ne;
	}
	free(L); //��˫�����ͷſռ�
	L = NULL; //��˫�����ͷſռ�
	return OK;
}

status ClearList_DuL(DuLinkList &L) {
//��ʼ������˫����L�Ѵ���
//�����������L����Ϊ�ձ�
	if (L == NULL) { //˫��������
		return ERROR;
	}
	DuLinkList p = L->next, ne; //ǰ����
	while (p) { //ǰ��㲻Ϊ��
		ne = p->next; //���㸳ֵ
		free(p); //ɾ��ǰ���
		p = ne;
	}
	L->next = NULL; //��˫�����׽��ָ���
	return OK;
}

status ListEmpty_DuL(DuLinkList L) {
//��ʼ������˫����L�Ѵ���
//�����������LΪ�ձ�����OK�����򷵻�ERROR
	if (L == NULL) { //˫��������
		return ERROR;
	}
	if (L->next == NULL) { //�׽��Ϊ��
		return OK;
	}
	return ERROR;
}

int ListLength_DuL(DuLinkList L) {
//��ʼ������˫����L�Ѵ���
//�������������L������Ԫ�صĸ���
	if (L == NULL) { //˫��������
		return -1;
	}
	int len = 0; //��ʼ������
	DuLinkList p = L->next;
	while (p) { //δ��βָ����ѭ��
		len++;
		p = p->next;
	}
	return len;
}

status GetElem_DuL(DuLinkList L, int i, ElemType &e) {
//��ʼ������˫����L�Ѵ��ڣ�1<=i<=ListLength_DuL(L)
//�����������e����L�еĵ�i��Ԫ�ص�ֵ
	if (L == NULL) {
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L)) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	DuLinkList p = L;
	while (i > 0) { //�ҵ���i��Ԫ��
		i--;
		p = p->next;
	}
	e = p->data; //����i��Ԫ�ظ�ֵ��e
	return OK;
}

status LocateElem_DuL(DuLinkList L, ElemType e) {
//��ʼ������˫����L�Ѵ���
//�������������e�Ľ��λ��
	if (L == NULL) { //˫��������
		return ERROR;
	}
	int i = 1;
	DuLinkList p = L->next;
	while (p) { //δ��βָ��
		if (p->data == e) //�ҵ��˴���Ԫ���򷵻ؽ��λ��
			return i;
		i++;
		p = p->next;
	}
	return ERROR; //δ�ҵ����λ�÷���ERROR
}

status PriorElem_DuL(DuLinkList L, ElemType e, ElemType &pre) {
//��ʼ������˫����L�Ѵ���
//�����������ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR
	if (L == NULL) { //˫��������
		return ERROR;
	}
	DuLinkList p = L->next;
	while (p) { //Ԫ�ش���
		if (e == p->data) { //�ҵ��˴���Ԫ��
			if (p->prior == L)
				return ERROR;
			pre = p->prior->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR; //δ�ҵ�Ԫ��e
}

status NextElem_DuL(DuLinkList L, ElemType e, ElemType &next) {
//��ʼ������˫����L�Ѵ���
//�����������ȡ˫����L��Ԫ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR
	if (L == NULL) { //˫��������
		return ERROR;
	}
	DuLinkList p = L->next;
	while (p) { //Ԫ�ش���
		if (e == p->data) { //�ҵ��˴���Ԫ��
			if (p->next == NULL)
				return ERROR;
			next = p->next->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR; //δ�ҵ�Ԫ��e
}

status ListInsert_DuL(DuLinkList &L, int i, ElemType e) {
//��ʼ������˫����L�Ѵ��ڣ�1<=i<=ListLength(L)+1
//�����������L�е�i��λ��֮ǰ�����µ�Ԫ������e��L�ĳ���+1
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L) + 1) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	DuLinkList p = L, t = (DuLinkList)malloc(sizeof(DuLNode)); //��̬����һ���¿ռ�
	t->data = e;
	while (i-- > 1) { //Ѱ��λ��i
		p = p->next;
	}
	t->next = p->next; //�޸�ָ��λ��
	t->prior = p;
	if (t->next != NULL)
		p->next->prior = t;
	p->next = t;
	return OK;
}

status ListDelete_DuL(DuLinkList &L, int i, ElemType &e) {
//��ʼ������˫����L�Ѵ����ҷǿգ�1<=i<=ListLength(L)
//���������ɾ��L�е�i������Ԫ�أ���e������ֵ��L�ĳ���-1
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	if (i < 1 || i > ListLength_DuL(L)) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	DuLinkList p = L;
	while (i-- > 0) { //Ѱ��λ��i�Ľ��
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
//��ʼ������˫����L�Ѵ���
//������������η���L�е�ÿ��Ԫ��
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	DuLinkList p = L->next;
	printf("���������");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

status ListReverseTraverse_DuL(DuLinkList &L) {
//��ʼ������˫����L�Ѵ���
//������������η���L�е�ÿ��Ԫ��
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	DuLinkList p = L;
	while (p->next != NULL) {
		p = p->next;
	}
	printf("���������");
	while (p != L) {
		printf("%d ", p->data);
		p = p->prior;
	}
	return OK;
}

status reverseList_DuL(DuLinkList &L) {
//��ʼ������˫����L�Ѵ���
//�����������L��ת
	if (L == NULL) {  //˫��������
		return ERROR;
	}
	DuLinkList p1 = L->next, p2 = p1->next, p3 = p1;
	p1->next = NULL; //���Ƚ���һ��Ԫ������ĩβ
	p1->prior = p2;
	while (p2 != NULL) {
		p1 = p2;
		p2 = p2->next;
		p1->next = p3;
		p1->prior = p2;
		p3 = p1;
	}
	L->next = p1; //�����һ��Ԫ�����ڿ�ͷ
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
		printf("    	  1. InitList_DuL��˫����Ĵ�����\n");
		printf("    	  2. DestroyList_DuL������˫����\n");
		printf("    	  3. ClearList_DuL�����˫����\n");
		printf("    	  4. ListEmpty_DuL��˫�����пգ�\n");
		printf("    	  5. ListLength_DuL����˫�����ȣ�\n");
		printf("    	  6. GetElem_DuL����ȡԪ�أ�\n");
		printf("          7. LocateElem_DuL������Ԫ�أ�\n");
		printf("          8. PriorElem_DuL����ȡǰ��Ԫ�أ�\n");
		printf("          9. NextElem_DuL����ȡ���Ԫ�أ�\n");
		printf("          10.ListInsert_DuL������Ԫ�أ�\n");
		printf("          11.ListDelete_DuL��ɾ��Ԫ�أ�\n");
		printf("          12.ListTrabverse_DuL���������˫����\n");
		printf("          13.ListReverseTrabverse_DuL���������˫����\n");
		printf("          14.reverseList_DuL��˫����ת��\n");
		printf("          0. Exit���˳��˵���\n");
		printf("-------------------------------------------------\n");
		printf("     ��ѡ����Ĳ���[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList_DuL(L);
				if (j == OK)
					printf("˫�������ɹ���\n");
				else
					printf("˫������ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList_DuL(L);
				if (j == OK)
					printf("˫�������ٳɹ���\n");
				else
					printf("˫��������ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 3:
				j = ClearList_DuL(L);
				if (j == OK)
					printf("˫������ճɹ���\n");
				else
					printf("˫�������ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 4:
				j = ListEmpty_DuL(L);
				if ( j == OK)
					printf("˫����Ϊ�գ�\n");
				else if (j == ERROR)
					printf("˫����Ϊ�գ�\n");
				else
					printf("˫�������ڣ�\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength_DuL(L);
				if (j == -1)
					printf("˫�������ڣ�\n");
				else
					printf("˫������Ϊ%d\n", ListLength_DuL(L));
				getchar();
				getchar();
				break;
			case 6:
				printf("����Ҫ��ȡ��Ԫ�ص�λ��\n");
				scanf("%d", &i);
				j = GetElem_DuL(L, i, e);
				if (j == ERROR)
					printf("��ȡԪ��ʧ�ܣ�\n");
				else
					printf("�����е�%d��Ԫ����%d\n", i, e);
				getchar();
				getchar();
				break;
			case 7:
				printf("������Ҫ���ҵ�Ԫ��\n");
				scanf("%d", &e);
				j = LocateElem_DuL(L, e);
				if (j == ERROR)
					printf("��Ԫ�ز����ڣ�\n");
				else
					printf("��Ԫ�ص�λ�������%d\n", j);
				getchar();
				getchar();
				break;
			case 8:
				printf("������Ҫ���ҵ�Ԫ��\n");
				scanf("%d", &e);
				j = PriorElem_DuL(L, e, pre);
				if (j == ERROR)
					printf("����ʧ�ܣ�%dΪ��һ��Ԫ�ػ�%d�����ڣ�\n", e, e);
				else
					printf("%d��ǰ��Ԫ����%d\n", e, pre);
				getchar();
				getchar();
				break;
			case 9:
				printf("������Ҫ���ҵ�Ԫ��\n");
				scanf("%d", &e);
				j = NextElem_DuL(L, e, next);
				if (j == ERROR)
					printf("����ʧ�ܣ�%dΪ���һ��Ԫ�ػ�%d�����ڣ�\n", e, e);
				else
					printf("%d�ĺ��Ԫ����%d\n", e, next);
				getchar();
				getchar();
				break;
			case 10:
				printf("����Ҫ�����Ԫ�ص�λ���Լ�Ԫ��ֵ\n");
				scanf("%d %d", &i, &e);
				j = ListInsert_DuL(L, i, e);
				if (j == OK)
					printf("����ɹ���\n");
				else
					printf("����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 11:
				printf("������Ҫɾ��Ԫ�ص�λ��\n");
				scanf("%d", &i);
				j = ListDelete_DuL(L, i, e);
				if (j == ERROR)
					printf("ɾ��ʧ�ܣ�\n");
				else
					printf("ɾ���ɹ���\n");
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
				printf("��ת�ɹ�\n");
				getchar();
				getchar();
				break;
			case 0:
				break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main()