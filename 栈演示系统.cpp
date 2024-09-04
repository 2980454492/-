#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACKINCREMENT 10 //�洢�ռ�ķ�������

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

//ջ��˳��洢�ṹ
typedef struct {
	ElemType *base; //��ջ����֮ǰ������֮��base��ֵΪNULL
	ElemType *top; //ջ��ָ��
	int stacksize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
} SqStack;

status InitStack(SqStack &S) {
//��ʼ������ջ������
//�������������һ����ջS
	if (S.base) //ջ�Ѵ���
		return ERROR;
	S.base = (ElemType *)malloc(sizeof(ElemType) * STACKINCREMENT); //��̬����ռ�
	for (int i = 0; i < STACKINCREMENT; i++) //Ĭ�����е�Ԫ�ش���0����=0˵��û��Ԫ��
		S.base[i] = 0;
	S.top = S.base;
	S.stacksize = STACKINCREMENT;
	return OK;
}

status DestroyStack(SqStack &S) {
//��ʼ������ջS�Ѵ���
//�������������S��S��������
	if (!S.base) //ջ������
		return ERROR;
	free(S.base); //�ͷŶ��пռ�
	S.base = NULL;
	S.top = NULL;
	return OK;
}

status ClearStack(SqStack &S) {
//��ʼ������ջS�Ѵ���
//�����������S��Ϊ�ն���
	if (!S.base) //���в�����
		return ERROR;
	for (int i = 0; i < STACKINCREMENT; i++) //������ζ�����
		S.base[i] = 0;
	S.top = S.base;
	return OK;
}

status StackEmpty(SqStack S) {
//��ʼ������ջS�Ѵ���
//�����������SΪ��ջ������OK�����򷵻�ERROR
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (S.top == S.base) //ջΪ��
		return OK;
	return ERROR; //ջ��Ϊ��
}

status StackFull(SqStack S) {
//��ʼ������ջS�Ѵ���
//�����������S����������OK�����򷵻�ERROR
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (S.top == S.base + STACKINCREMENT) //ջ����
		return OK;
	return ERROR; //ջ��Ϊ��
}

int StackLength(SqStack S) {
//��ʼ������ջS�Ѵ���
//���������ջS��Ԫ�ظ���
	if (!S.base) //ջ������
		return INFEASIBLE;
	return S.top - S.base;
}

status GetTop(SqStack S, int &e) {
//��ʼ������ջS�Ѵ����ҷǿ�
//�����������e����S��ջ��Ԫ��
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (StackEmpty(S)) //ջΪ��
		return ERROR;
	e = *(S.top - 1); //ջԪ��
	return OK;
}

status Push(SqStack &S, int e) {
//��ʼ������ջS�Ѵ���
//�������������Ԫ��eΪS���µ�ջ��Ԫ��
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (StackFull(S)) //ջ����
		return ERROR;
	*(S.top) = e; //��Ԫ�ز���ջ��������ջ��ָ��
	S.top++;
	return OK;
}

status Pop(SqStack &S, int &e) {
//��ʼ������ջS�Ѵ����ҷǿ�
//���������ɾ��S��ջ��Ԫ�أ�����e������ֵ
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (StackEmpty(S)) //ջΪ��
		return ERROR;
	e = *(--S.top); //ջ��Ԫ�ظ�ֵ
	*(S.top) = 0; //ɾ��ջ��Ԫ��
	return OK;
}

status StackTraverse(SqStack S) {
//��ʼ������ջS�Ѵ����ҷǿ�
//�����������ջ�׵�ջ�����η���
	if (!S.base) //ջ������
		return INFEASIBLE;
	printf("ջ����:");
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
		printf("        1. InitStack ������ջ��\n");
		printf("        2. DestroyStack ������ջ��\n");
		printf("    	3. ClearStack �����ջ��\n");
		printf("        4. StackEmpty ��ջ�пգ�\n");
		printf("        5. StackFull ��ջ������\n");
		printf("    	6. StackLength ����ջ���ȣ�\n");
		printf("        7. GetTop ����ȡջ��Ԫ�أ�\n");
		printf("    	8. Push ����ջ��\n");
		printf("        9. Pop ����ջ��\n");
		printf("    	10.StackTraverse ��ջ�ı�����\n");
		printf("        0. Exit���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~10]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				ans = InitStack(S);
				if (ans)
					printf("�����ɹ�");
				else
					printf("����ʧ�ܣ�ջ�Ѵ���");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroyStack(S);
				if (ans)
					printf("���ٳɹ�");
				else
					printf("����ʧ��");
				getchar();
				getchar();
				break;
			case 3:
				ans = ClearStack(S);
				if (ans)
					printf("��ճɹ�");
				else
					printf("���ʧ��");
				getchar();
				getchar();
				break;
			case 4:
				ans = StackEmpty(S);
				if (ans == INFEASIBLE)
					printf("ջ������");
				else if (ans == ERROR)
					printf("ջ��Ϊ��");
				else
					printf("ջΪ��");
				getchar();
				getchar();
				break;
			case 5:
				ans = StackFull(S);
				if (ans == INFEASIBLE)
					printf("ջ������");
				else if (ans == ERROR)
					printf("ջ��Ϊ��");
				else
					printf("ջ����");
				getchar();
				getchar();
				break;
			case 6:
				ans = StackLength(S);
				if (ans == INFEASIBLE)
					printf("ջ������");
				else
					printf("ջ����Ϊ%d", ans);
				getchar();
				getchar();
				break;
			case 7:
				ans = GetTop(S, e);
				if (ans == INFEASIBLE)
					printf("��ȡʧ�ܣ�ջ������");
				else if (ans == ERROR)
					printf("��ȡʧ�ܣ�ջΪ��");
				else
					printf("��ȡ�ɹ���ջ��Ԫ��Ϊ%d", e);
				getchar();
				getchar();
				break;
			case 8:
				printf("�������ջ��Ԫ��\n");
				scanf("%d", &e);
				ans = Push(S, e);
				if (ans == OK)
					printf("��ջ�ɹ�");
				else if (ans == INFEASIBLE)
					printf("��ջʧ�ܣ�ջ������");
				else
					printf("��ջʧ�ܣ�ջ����");
				getchar();
				getchar();
				break;
			case 9:
				ans = Pop(S, e);
				if (ans == INFEASIBLE)
					printf("��ջʧ�ܣ�ջ������");
				else if (ans == ERROR)
					printf("��ջʧ�ܣ�ջΪ��");
				else
					printf("��ջ�ɹ�����ջԪ��Ϊ%d", e);
				getchar();
				getchar();
				break;
			case 10:
				ans = StackTraverse(S);
				if (ans == INFEASIBLE)
					printf("ջ������\n");
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