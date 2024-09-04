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
#define STACKINCREMENT 10 //�洢�ռ�ķ�������

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

//�������չ��������洢��ʾ
typedef enum {ATOM, LIST} ElemTag; //ATOM=0��ԭ�ӣ�LIST=1���ӱ�
typedef struct GLNode {
	ElemTag tag; //�������֣���������ԭ�ӽ��ͱ���
	union {
		ElemType atom; //ԭ�ӽ���ֵ��
		struct GLNode *hp; //����ı�ͷָ��
	};
	struct GLNode *tp; //�൱�������е�next��ָ����һԪ�ؽ��
} *GList; //���������

status InitGList(GList &L) {
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

status CreateGList(GList &L, char *S) {
//��ʼ������S�ǹ�������д��ʽ��
//�����������S���������L

}

status DestroyGList(GList &L) {
//��ʼ������ջS�Ѵ���
//�������������S��S��������
	if (!S.base) //ջ������
		return ERROR;
	free(S.base); //�ͷŶ��пռ�
	S.base = NULL;
	S.top = NULL;
	return OK;
}

status CopyGList(GList &T, GList L) {
//��ʼ�����������L����
//����������ɹ����L���Ƶõ������T

}

int GListLength(GList L) {
//��ʼ������ջS�Ѵ���
//���������ջS��Ԫ�ظ���
	if (!S.base) //ջ������
		return INFEASIBLE;
	return S.top - S.base;
}

int GListDepth(GList L) {
//��ʼ������ջS�Ѵ���
//���������ջS��Ԫ�ظ���
	if (!S.base) //ջ������
		return INFEASIBLE;
	return S.top - S.base;
}

status GListEmpty(GList L) {
//��ʼ������ջS�Ѵ���
//�����������SΪ��ջ������OK�����򷵻�ERROR
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (S.top == S.base) //ջΪ��
		return OK;
	return ERROR; //ջ��Ϊ��
}

status GetHead(GList L) {
//��ʼ������ջS�Ѵ����ҷǿ�
//�����������e����S��ջ��Ԫ��
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (StackEmpty(S)) //ջΪ��
		return ERROR;
	e = *(S.top - 1); //ջԪ��
	return OK;
}

status GetTail(GList L) {
//��ʼ������ջS�Ѵ����ҷǿ�
//�����������e����S��ջ��Ԫ��
	if (!S.base) //ջ������
		return INFEASIBLE;
	if (StackEmpty(S)) //ջΪ��
		return ERROR;
	e = *(S.top - 1); //ջԪ��
	return OK;
}

status InsertFirstGL(GList &L, ElemType e) {
//��ʼ�����������L����
//�������������Ԫ��e��Ϊ�����L�ĵ�һ��Ԫ��

}

status DeleteFirstGL(GList &L, ElemType &e) {
//��ʼ�����������L����
//���������ɾ�������L�ĵ�һ��Ԫ�أ�����e������ֵ

}

status GListTraverse(GList L) {
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
		printf("        1. InitGList �����������\n");
		printf("        2. DestroyGList �����ٹ����\n");
		printf("        3. DestroyGList �����ٹ����\n");
		printf("        4. CopyGList �����ƹ����\n")
		printf("    	5. GListLength ���������ȣ�\n");
		printf("        6. GListDepth ����������ȣ�\n")
		printf("        7. GListEmpty ��������пգ�\n");
		printf("        8. GetHead ����ȡ�����ͷԪ�أ�\n");
		printf("        9. GetTail ����ȡ�����βԪ�أ�\n");
		printf("    	10.InsertGListGL ������ͷԪ�أ�\n");
		printf("        11.DeleteGListGL ��ɾ��ͷԪ�أ�\n");
		printf("    	12.GListTraverse �������ı�����\n");
		printf("        0. Exit���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~12]:");
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