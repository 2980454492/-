#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define QUEUEINCREMENT 10 //�洢�ռ�ķ�������

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

//���е�˳��洢�ṹ
typedef struct {
	ElemType *base; //��ʼ���Ķ�̬����洢�ռ�
	int front; //ͷָ�룬�����в��գ���ָ���ͷԪ��
	int rear;  //βָ�룬�����в��գ���ָ���βԪ�ص���һԪ��
} SqQueue;

status InitQueue(SqQueue &Q) {
//��ʼ���������в�����
//�������������һ���ն���Q
	if (Q.base) //�����Ѵ���
		return ERROR;
	Q.base = (ElemType *)malloc(sizeof(ElemType) * QUEUEINCREMENT); //��̬����ռ�
	for (int i = 0; i < QUEUEINCREMENT; i++) //Ĭ�����е�Ԫ�ش���0����=0˵��û��Ԫ��
		Q.base[i] = 0;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

status DestroyQueue(SqQueue &Q) {
//��ʼ����������Q�Ѵ���
//�������������Q��Q��������
	if (!Q.base) //���в�����
		return ERROR;
	free(Q.base); //�ͷŶ��пռ�
	Q.base = NULL;
	Q.front = 0; //����ͷβָ��
	Q.rear = 0;
	return OK;
}

status ClearQueue(SqQueue &Q) {
//��ʼ����������Q�Ѵ���
//�����������Q��Ϊ�ն���
	if (!Q.base) //���в�����
		return ERROR;
	for (int i = 0; i < QUEUEINCREMENT; i++) //������ζ�����
		Q.base[i] = 0;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

status QueueEmpty(SqQueue Q) {
//��ʼ����������Q�Ѵ���
//�����������QΪ�ն��У�����OK�����򷵻�ERROR
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (Q.front == Q.rear && !Q.base[Q.front]) //����Ϊ��
		return OK;
	return ERROR; //���в�Ϊ��
}

status QueueFull(SqQueue Q) {
//��ʼ����������Q�Ѵ���
//�����������Q����������OK�����򷵻�ERROR
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (Q.rear == Q.front && Q.base[Q.front]) //��������
		return OK;
	return ERROR; //���в�Ϊ��
}

int QueueLength(SqQueue Q) {
//��ʼ����������Q�Ѵ���
//�������������Q��Ԫ�ظ���
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (Q.rear == Q.front && Q.base[Q.front]) //��������
		return QUEUEINCREMENT;
	return (Q.rear - Q.front + QUEUEINCREMENT) % QUEUEINCREMENT;
}

status GetHead(SqQueue Q, int &e) {
//��ʼ����������Q�Ѵ����ҷǿ�
//�����������e����Q�Ķ�ͷԪ��
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (QueueEmpty(Q)) //����Ϊ��
		return ERROR;
	e = Q.base[Q.front]; //��ͷԪ��
	return OK;
}

status EnQueue(SqQueue &Q, int e) {
//��ʼ����������Q�Ѵ���
//�������������Ԫ��eΪQ���µĶ�βԪ��
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (QueueFull(Q)) //��������
		return ERROR;
	Q.base[Q.rear++] = e; //��Ԫ�ز����β�����ö�βָ��
	Q.rear %= QUEUEINCREMENT; //ѭ������
	return OK;
}

status DeQueue(SqQueue &Q, int &e) {
//��ʼ����������Q�Ѵ����ҷǿ�
//���������ɾ��Q�Ķ�ͷԪ�أ�����e������ֵ
	if (!Q.base) //���в�����
		return INFEASIBLE;
	if (QueueEmpty(Q)) //����Ϊ��
		return ERROR;
	e = Q.base[Q.front]; //ͷԪ�ظ�ֵ
	Q.base[Q.front++] = 0; //ɾ����ͷԪ��
	Q.front %= QUEUEINCREMENT;
	return OK;
}

status QueueTraverse(SqQueue Q) {
//��ʼ����������Q�Ѵ����ҷǿ�
//����������Ӷ�ͷ����β���η���
	if (!Q.base) //���в�����
		return INFEASIBLE;
	int i = Q.front;
	printf("���б���:");
	if (QueueEmpty(Q)) { //�������������Ƚ���ͷԪ�����
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
		printf("        1. InitQueue ���������У�\n");
		printf("        2. DestroyQueue �����ٶ��У�\n");
		printf("    	3. ClearQueue ����ն��У�\n");
		printf("        4. QueueEmpty �������пգ�\n");
		printf("        5. QueueFull ������������\n");
		printf("    	6. QueueLength ������г��ȣ�\n");
		printf("        7. GetHead ����ȡ��ͷԪ�أ�\n");
		printf("    	8. EnQueue �����ӣ�\n");
		printf("        9. DeQueue �����ӣ�\n");
		printf("    	10.QueueTraverse �����еı�����\n");
		printf("        0. Exit���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~10]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				ans = InitQueue(Q);
				if (ans)
					printf("�����ɹ�");
				else
					printf("����ʧ�ܣ������Ѵ���");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroyQueue(Q);
				if (ans)
					printf("���ٳɹ�");
				else
					printf("����ʧ��");
				getchar();
				getchar();
				break;
			case 3:
				ans = ClearQueue(Q);
				if (ans)
					printf("��ճɹ�");
				else
					printf("���ʧ��");
				getchar();
				getchar();
				break;
			case 4:
				ans = QueueEmpty(Q);
				if (ans == INFEASIBLE)
					printf("���в�����");
				else if (ans == ERROR)
					printf("���в�Ϊ��");
				else
					printf("����Ϊ��");
				getchar();
				getchar();
				break;
			case 5:
				ans = QueueFull(Q);
				if (ans == INFEASIBLE)
					printf("���в�����");
				else if (ans == ERROR)
					printf("���в�Ϊ��");
				else
					printf("��������");
				getchar();
				getchar();
				break;
			case 6:
				ans = QueueLength(Q);
				if (ans == INFEASIBLE)
					printf("���в�����");
				else
					printf("���г���Ϊ%d", ans);
				getchar();
				getchar();
				break;
			case 7:
				ans = GetHead(Q, e);
				if (ans == INFEASIBLE)
					printf("��ȡ�����в�����");
				else if (ans == ERROR)
					printf("��ȡʧ�ܣ�����Ϊ��");
				else
					printf("��ȡ�ɹ�����ͷԪ��Ϊ%d", e);
				getchar();
				getchar();
				break;
			case 8:
				printf("��������ӵ�Ԫ��\n");
				scanf("%d", &e);
				ans = EnQueue(Q, e);
				if (ans == OK)
					printf("���ӳɹ�");
				else if (ans == INFEASIBLE)
					printf("����ʧ�ܣ����в�����");
				else
					printf("����ʧ�ܣ���������");
				getchar();
				getchar();
				break;
			case 9:
				ans = DeQueue(Q, e);
				if (ans == INFEASIBLE)
					printf("����ʧ�ܣ����в�����");
				else if (ans == ERROR)
					printf("����ʧ�ܣ�����Ϊ��");
				else
					printf("���ӳɹ�������Ԫ��Ϊ%d", e);
				getchar();
				getchar();
				break;
			case 10:
				ans = QueueTraverse(Q);
				if (ans = INFEASIBLE)
					printf("���в�����\n");
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