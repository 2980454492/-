#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

typedef struct LNode { //��������ʽ�ṹ�����Ķ���
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

status InitList(LinkList &L) {
//��ʼ���������Ա�����
//�������������һ���յ����Ա�L
	if (L != NULL) { //���Ա�Ϊ���򷵻�ERROR
		return ERROR;
	}
	L = (LinkList)malloc(sizeof(LNode)); //��̬����ռ�
	L->data = 0; //��ʼֵ��Ϊ0��
	L->next = NULL; //�ձ���׽��ָ���
	return OK;
}

status DestroyList(LinkList &L) {
//��ʼ���������Ա�L�Ѵ���
//���������ɾ�����Ա�
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	LinkList ne, q = L->next; //ǰ����
	while (q) { //ǰ��㲻Ϊ��
		ne = q->next; //���㸳ֵ
		free(q); //ɾ��ǰ���
		q = ne;
	}
	free(L); //�����Ա��ͷſռ�
	L = NULL; //�����Ա��ͷſռ�
	return OK;
}

status ClearList(LinkList &L) {
//��ʼ���������Ա�L�Ѵ���
//�����������L����Ϊ�ձ�
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	LinkList p = L->next, ne; //ǰ����
	while (p) { //ǰ��㲻Ϊ��
		ne = p->next; //���㸳ֵ
		free(p); //ɾ��ǰ���
		p = ne;
	}
	L->next = NULL; //�����Ա��׽��ָ���
	return OK;
}

status ListEmpty(LinkList L) {
//��ʼ���������Ա�L�Ѵ���
//�����������LΪ�ձ�����OK�����򷵻�ERROR
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	if (L->next == NULL) { //�׽��Ϊ��
		return OK;
	}
	return ERROR;
}

int ListLength(LinkList L) {
//��ʼ���������Ա�L�Ѵ���
//�������������L������Ԫ�صĸ���
	if (L == NULL) { //���Ա�����
		return -1;
	}
	int len = 0; //��ʼ������
	LinkList p = L->next;
	while (p) { //δ��βָ����ѭ��
		len++;
		p = p->next;
	}
	return len;
}

status GetElem(LinkList L, int i, ElemType &e) {
//��ʼ���������Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)
//�����������e����L�еĵ�i��Ԫ�ص�ֵ
	if (L == NULL) {
		return ERROR;
	}
	if (i < 1 || i > ListLength(L)) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	LinkList p = L;

	while (i > 0) { //�ҵ���i��Ԫ��
		i--;
		p = p->next;
	}
	e = p->data; //����i��Ԫ�ظ�ֵ��e
	return OK;
}

status LocateElem(LinkList L, ElemType e) {
//��ʼ���������Ա�L�Ѵ���
//�������������e�Ľ��λ��
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	int i = 1;
	LinkList p = L->next;
	while (p) { //δ��βָ��
		if (p->data == e) //�ҵ��˴���Ԫ���򷵻ؽ��λ��
			return i;
		i++;
		p = p->next;
	}
	return ERROR; //δ�ҵ����λ�÷���ERROR
}

status PriorElem(LinkList L, ElemType e, ElemType &pre) {
//��ʼ���������Ա�L�Ѵ���
//�����������ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	LinkList p = L, ne = L->next; //ǰ����
	while (ne) {
		if (e == ne->data) { //�ҵ��˴���Ԫ��
			if (p == L) //e�ǵ�һ��Ԫ�أ�û��ǰ��
				return ERROR;
			pre = p->data; //��ǰ����Ϣ��ֵ��pre
			return OK;
		}
		p = ne;
		ne = p->next;
	}
	return ERROR; //δ�ҵ�Ԫ��e
}

status NextElem(LinkList L, ElemType e, ElemType &next) {
//��ʼ���������Ա�L�Ѵ���
//�����������ȡ���Ա�L��Ԫ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	LinkList p = L->next, ne;
	if (p == NULL) //���Ա��ǿձ�
		return ERROR;
	ne = p->next;
	while (ne) { //��Ԫ�ش���
		if (e == p->data) { //�ҵ��˴���Ԫ��
			next = ne->data;
			return OK;
		}
		p = ne;
		ne = p->next;
	}
	return ERROR; //δ�ҵ�Ԫ��e
}

status ListInsert(LinkList &L, int i, ElemType e) {
//��ʼ���������Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)+1
//�����������L�е�i��λ��֮ǰ�����µ�Ԫ������e��L�ĳ���+1
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	if (i < 1 || i > ListLength(L) + 1) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	LinkList p = L, t = (LinkList)malloc(sizeof(LNode)); //��̬����һ���¿ռ�
	t->data = e;
	while (i-- > 1) { //Ѱ��λ��i
		p = p->next;
	}
	t->next = p->next; //�޸�ָ��λ��
	p->next = t;
	return OK;
}

status ListDelete(LinkList &L, int i, ElemType &e) {
//��ʼ���������Ա�L�Ѵ����ҷǿգ�1<=i<=ListLength(L)
//���������ɾ��L�е�i������Ԫ�أ���e������ֵ��L�ĳ���-1
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	if (i < 1 || i > ListLength(L)) { //i��ֵ����ȷ������ERROR
		return ERROR;
	}
	LinkList p = L;
	while (i-- > 1) { //Ѱ��λ��i��ǰ�����
		p = p->next;
	}
	LinkList t = p->next; //tΪλ��i�Ľ��ָ��
	if (t == NULL) {
		return ERROR;
	}
	e = t->data;
	p->next = t->next;
	free(t);
	return OK;
}

status ListTraverse(LinkList L) {
//��ʼ���������Ա�L�Ѵ���
//������������η���L�е�ÿ��Ԫ��
	if (L == NULL) { //���Ա�����
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
//��ʼ���������Ա�L�Ѵ���
//�����������L��ת
	if (L == NULL) {  //���Ա�����
		return ERROR;
	}
	LinkList p1 = L->next, p2 = p1->next, p3 = p1;
	p1->next = NULL; //���Ƚ���һ��Ԫ������ĩβ
	while (p2 != NULL) {
		p1 = p2;
		p2 = p2->next;
		p1->next = p3;
		p3 = p1;
	}
	L->next = p1; //�����һ��Ԫ�����ڿ�ͷ
	return OK;
}

status RemoveNthFromEnd(LinkList L, int n) {
//��ʼ���������Ա�L�Ѵ����ҷǿ�
//����������������е�����n�����
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	int len = ListLength(L);
	if (n > len || n < 1) { //n��ֵ����ȷ
		return ERROR;
	}
	LinkList p = L->next;
	for (int i = 0; i < len - n; i++) { //�ҵ�������n�����
		p = p->next;
	}
	return p->data;
}

status sortList(LinkList &L) {
//��ʼ���������Ա�L�Ѵ���
//�����������L��С��������
	if (L == NULL) { //���Ա�����
		return ERROR;
	}
	int flag = 0; //�����˳�����
	LinkList p1 = L, p2 = p1->next;
	while (1) { //����ð������ķ���
		flag = 0; //��ԭflag��ֵ

		while (p2->next != NULL) {
			if (p2->data > p2->next->data) {
				flag = 1; //��ʾ��Ԫ�ص�λ��Ҫ�ı�
				p1->next = p2->next; //ʵ����ָ�뷭ת
				p2->next = p1->next->next;
				p1->next->next = p2;
				p2 = p1->next;
			}
			p1 = p2;
			p2 = p2->next;
		}
		if (flag == 0) //�Ѿ�������������ֱ�ӷ���OK����ʡʱ��
			break;
		p1 = L; //һ��������������»ص�ͷ��������һ������
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
		printf("    	  1. InitList�����Ա�Ĵ�����\n");
		printf("    	  2. DestroyList���������Ա�\n");
		printf("    	  3. ClearList��������Ա�\n");
		printf("    	  4. ListEmpty�����Ա��пգ�\n");
		printf("    	  5. ListLength�������Ա��ȣ�\n");
		printf("    	  6. GetElem����ȡԪ�أ�\n");
		printf("          7. LocateElem������Ԫ�أ�\n");
		printf("          8. PriorElem����ȡǰ��Ԫ�أ�\n");
		printf("          9. NextElem����ȡ���Ԫ�أ�\n");
		printf("          10.ListInsert������Ԫ�أ�\n");
		printf("          11.ListDelete��ɾ��Ԫ�أ�\n");
		printf("          12.ListTrabverse���������Ա�\n");
		printf("          13.reverseList������ת��\n");
		printf("          14.RemoveNthFromEnd��������n����㣩\n");
		printf("          15.sortList����������\n");
		printf("          0. Exit���˳��˵���\n");
		printf("-------------------------------------------------\n");
		printf("     ��ѡ����Ĳ���[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList(L);
				if (j == OK)
					printf("���Ա����ɹ���\n");
				else
					printf("���Ա���ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList(L);
				if (j == OK)
					printf("���Ա����ٳɹ���\n");
				else
					printf("���Ա�����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 3:
				j = ClearList(L);
				if (j == OK)
					printf("���Ա���ճɹ���\n");
				else
					printf("���Ա����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 4:
				j = ListEmpty(L);
				if ( j == OK)
					printf("���Ա�Ϊ�գ�\n");
				else if (j == ERROR)
					printf("���Ա�Ϊ�գ�\n");
				else
					printf("���Ա����ڣ�\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength(L);
				if (j == -1)
					printf("���Ա����ڣ�\n");
				else
					printf("���Ա���Ϊ%d\n", ListLength(L));
				getchar();
				getchar();
				break;
			case 6:
				printf("����Ҫ��ȡ��Ԫ�ص�λ��\n");
				scanf("%d", &i);
				j = GetElem(L, i, e);
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
				j = LocateElem(L, e);
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
				j = PriorElem(L, e, pre);
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
				j = NextElem(L, e, next);
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
				j = ListInsert(L, i, e);
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
				j = ListDelete(L, i, e);
				if (j == ERROR)
					printf("ɾ��ʧ�ܣ�\n");
				else
					printf("ɾ���ɹ���\n");
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
				printf("��ת�ɹ�\n");
				getchar();
				getchar();
				break;
			case 14:
				printf("��������Ҫ��õĵ�����n��Ԫ��\n");
				scanf("%d", &i);
				j = RemoveNthFromEnd(L, i);
				if (j == ERROR)
					printf("n��ֵ����\n", i);
				else
					printf("������%d��Ԫ��Ϊ%d\n", i, j);
				getchar();
				getchar();
				break;
			case 15:
				j = sortList(L);
				printf("����ɹ�\n");
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