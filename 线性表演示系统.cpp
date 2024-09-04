#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct { //˳���˳��ṹ���Ķ���
	ElemType *elem;
	int length;
	int listsize;
} SqList;

status InitList(SqList &L) {
	if (L.elem != NULL) {
		return INFEASIBLE;
	}
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList &L)

// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	L.elem = NULL;
	free(L.elem);
	return OK;
	/********** End **********/
}

status ClearList(SqList &L)

// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = 0;
	}
	L.length = 0;
	return OK;
	/********** End **********/
}

status ListEmpty(SqList L)

// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
	/********** End **********/
}

status ListLength(SqList L)

// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	return L.length;
	/********** End **********/
}

status GetElem(SqList L, int i, ElemType &e)

// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i > L.length || i < 1) {
		return ERROR;
	}
	e = L.elem[i - 1];
	return OK;
	/********** End **********/
}

int LocateElem(SqList L, ElemType e)

// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			return i;
		}
	}
	return 0;
	/********** End **********/
}

status PriorElem(SqList L, ElemType e, ElemType &pre)

// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������

	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			if (i == 1)
				return ERROR;
			else {
				pre = L.elem[i - 2];
				return OK;
			}
		}
	}
	return ERROR;
	/********** End **********/
}

status NextElem(SqList L, ElemType e, ElemType &next)

// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 1; i <= L.length; i++) {
		if (e == L.elem[i - 1]) {
			if (i == L.length)
				return ERROR;
			else {
				next = L.elem[i];
				return OK;
			}
		}
	}
	return ERROR;
	/********** End **********/
}

status ListInsert(SqList &L, int i, ElemType e)

// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i < 1 || i > L.length + 1) {
		return ERROR;
	}
	(int *)realloc(L.elem, sizeof(int *) * 11);
	int x;

	for (int x = L.length; x >= i; x--) {
		L.elem[x] = L.elem[x - 1];
	}
	L.elem[i - 1] = e;
	L.length++;
	return OK;
	/********** End **********/
}

status ListDelete(SqList &L, int i, ElemType &e)

// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	if (i < 1 || i > L.length) {
		return ERROR;
	}
	e = L.elem[i - 1];
	for (int x = i - 1; x < L.length - 1; x++) {
		L.elem[x] = L.elem[x + 1];
	}
	L.length--;
	return OK;
	/********** End **********/
}

status ListTraverse(SqList L)

// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	printf("�������Ա�");
	for (int i = 0; i < L.length; i++) {
		printf("%d", L.elem[i]);
		if (i < L.length - 1)
			printf(" ");
	}
	return OK;
	/********** End **********/
}

status MaxSubArray(SqList L) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	int sum = 0, result = 0;
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] >= 0) {
			sum += L.elem[i];
		} else {
			if (sum > result) {
				result = sum;
			}
			sum = 0;
		}
	}
	if (sum > result) {
		result = sum;
	}
	return result;
}

status SubArrayNum(SqList L, int k) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	int count = 0;
	for (int i = 0; i < L.length; i++) {
		int sum = 0;
		for (int j = i; j < L.length; j++) {
			sum += L.elem[j];
			if (sum == k)
				count++;
		}
	}
	return count;
}

status sortList(SqList &L) {
	if (L.elem == NULL) {
		return INFEASIBLE;
	}
	for (int i = 0; i < L.length - 1; i++) {
		for (int j = i + 1; j < L.length; j++) {
			if (L.elem[i] > L.elem[j]) {
				int temp = L.elem[i];
				L.elem[i] = L.elem[j];
				L.elem[j] = temp;
			}
		}
	}
	return OK;
}

status  SaveList(SqList L, char FileName[])

// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem == NULL)
		return INFEASIBLE;
	FILE *fp = fopen(FileName, "w");
	if (fp == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	for (int i = 0; i < L.length; i++) {
		fprintf(fp, "%d", L.elem[i]);
		fprintf(fp, " ");
	}
	fclose(fp);
	return OK;
	/********** End **********/
}

status  LoadList(SqList &L, char FileName[])

// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L.elem != NULL) {
		return INFEASIBLE;
	}
	L.elem = (ElemType *)malloc(sizeof(ElemType) * L.listsize);
	FILE *fp = fopen(FileName, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	for (int i = 0; i < L.length; i++) {
		fscanf(fp, "%d", &L.elem[i]);
	}
	fclose(fp);
	return OK;
	/********** End **********/
}

int main( ) {
	SqList L;
	L.elem = NULL;
	int op = 1;
	int j;
	ElemType i, e, pre, next;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("        1. InitList�����Ա�Ĵ�����\n");
		printf("        2. DestroyList���������Ա�\n");
		printf("    	3. ClearList��������Ա�\n");
		printf("        4. ListEmpty�����Ա��пգ�\n");
		printf("    	5. ListLength�������Ա��ȣ�\n");
		printf("        6. GetElem����ȡԪ�أ�\n");
		printf("    	7. LocateElem������Ԫ�أ�\n");
		printf("        8. PriorElem����ȡǰ��Ԫ�أ�\n");
		printf("    	9. NextElem����ȡ���Ԫ�أ�\n");
		printf("        10.ListInsert������Ԫ�أ�\n");
		printf("    	11.ListDelete��ɾ��Ԫ�أ�\n");
		printf("        12.ListTrabverse���������Ա�\n");
		printf("        13.MaxSubArray����ȡ���ͣ�\n");
		printf("        14.SubArrayNum����͸�����\n");
		printf("        15.sortList�����Ա�����\n");
		printf("        0. Exit���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~15]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				j = InitList(L);
				if ( j == OK)
					printf("���Ա����ɹ���\n");
				else
					printf("���Ա���ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
			case 2:
				j = DestroyList(L);
				if ( j == OK)
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
				if (j == TRUE)
					printf("���Ա�Ϊ�գ�\n");
				else if (j == FALSE)
					printf("���Ա�Ϊ�գ�\n");
				else
					printf("���Ա����ڣ�\n");
				getchar();
				getchar();
				break;
			case 5:
				j = ListLength(L);
				if ( j == INFEASIBLE)
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
				if ( j == INFEASIBLE)
					printf("���Ա����ڣ�\n");
				else if (j == ERROR)
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
				if (j == 0)
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
				if (ListTraverse(L) == INFEASIBLE)
					printf("���Ա����ڣ�\n");
				getchar();
				getchar();
				break;
			case 13:
				j = MaxSubArray(L);
				printf("����Ϊ%d\n", j);
				getchar();
				getchar();
				break;
			case 14:
				printf("����������������ĺ�\n");
				scanf("%d", &i);
				j = SubArrayNum(L, i);
				printf("�������к�Ϊ%d������������ĸ���Ϊ%d\n", i, j);
				getchar();
				getchar();
				break;
			case 15:
				sortList(L);
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