#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXSIZE 12500 //����Ԫ���������ֵΪ12500
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

//ϡ��������Ԫ˳���洢��ʾ
typedef struct {
	int i, j; //�÷���Ԫ�ص����±�����±�
	ElemType e;
} Triple;

typedef struct {
	Triple data[MAXSIZE + 1]; //����Ԫ��Ԫ���data[0]δʹ��
	int mu, nu, tu; //����������������ͷ���Ԫ�ظ���
} TSMatrix;

status CreateSMattrix(TSMatrix &M) {
//��ʼ������M������
//�������������ϡ�����M
	printf("��������������������������Ԫ�ĸ���\n");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
	for (int i = 1; i <= M.tu; i++) {
		printf("�������%d��Ԫ�ص�λ�ú�ֵ��", i);
		scanf("%d %d %d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
		if (M.data[i].i > M.mu || M.data[i].i < 1 || M.data[i].j > M.nu || M.data[i].j < 1) {
			printf("Ԫ�������壬����������\n");
			i--;
		}
		for (int j = 1; j < i; j++) {
			if (M.data[i].i == M.data[j].i && M.data[i].j == M.data[j].j) {
				printf("Ԫ���ظ����壬����������\n");
				i--;
			}
		}
	}
	return OK;
}

status DestroySMattrix(TSMatrix &M) {
//��ʼ������M����
//�������������ϡ�����M
	if (M.mu == 0 || M.nu == 0)
		return ERROR;
	for (int i = 1; i <= M.tu; i++) {
		M.data[i].e = 0;
		M.data[i].i = 0;
		M.data[i].j = 0;
	}
	M.mu = 0;
	M.nu = 0;
	M.tu = 0;
	return OK;
}

status PrintSMattrix(TSMatrix M) {
//��ʼ������M����
//������������ϡ�����M
	if (M.mu == 0 || M.nu == 0)
		return INFEASIBLE;
	for (int i = 1; i <= M.mu; i++) {
		for (int j = 1; j <= M.nu; j++) {
			int k = 1;
			for (k = 1; k <= M.tu; k++) {
				if (i == M.data[k].i && j == M.data[k].j) {
					printf("%d ", M.data[k].e);
					break;
				}
			}
			if (k == M.tu + 1)
				printf("0 ");
		}
		printf("\n");
	}
	return OK;
}

status CopySMattrix(TSMatrix M, TSMatrix &T) {
//��ʼ������M����
//�����������ϡ�����M���Ƶõ�T
	if (M.mu == 0 || M.nu == 0)
		return INFEASIBLE;
	for (int i = 1; i <= M.tu; i++) {
		T.data[i].e = M.data[i].e;
		T.data[i].i = M.data[i].i;
		T.data[i].j = M.data[i].j;
	}
	T.mu = M.mu;
	T.nu = M.nu;
	T.tu = M.tu;
	return OK;
}

status AddSMattrix(TSMatrix M, TSMatrix N, TSMatrix &T) {
//��ʼ������M,N���ڣ�����������Ӧ���
//�����������ϡ�����ĺ�Q
	if (M.mu == 0 || M.nu == 0 || N.mu == 0 || N.nu == 0)
		return INFEASIBLE;
	if (M.mu != N.mu || M.nu != N.nu)
		return ERROR;
	for (int i = 1; i <= M.tu; i++) {
		T.data[i].e = M.data[i].e;
		T.data[i].i = M.data[i].i;
		T.data[i].j = M.data[i].j;
	}
	T.mu = M.mu;
	T.nu = M.nu;
	T.tu = M.tu;
	for (int i = 1; i <= N.tu; i++) {
		int j = 1;
		for (; j <= M.tu; j++) {
			if (M.data[j].i == N.data[i].i && M.data[j].j == N.data[i].j) {
				T.data[j].e += N.data[i].e;
			}
		}
		if (j == M.tu + 1) {
			T.tu++;
			T.data[T.tu].e = N.data[i].e;
			T.data[T.tu].i = N.data[i].i;
			T.data[T.tu].j = N.data[i].j;
		}
	}
	for (int i = 1; i <= T.tu; i++) {
		if (T.data[i].e == 0) {
			T.data[i].e = T.data[T.tu].e;
			T.data[i].i = T.data[T.tu].i;
			T.data[i].j = T.data[T.tu].j;
			T.tu--;
			i--;
		}
	}
	return OK;
}

status SubtMattrix(TSMatrix M, TSMatrix N, TSMatrix &T) {
//��ʼ������M,N���ڣ�����������Ӧ���
//�����������ϡ�����Ĳ�Q
	if (M.mu == 0 || M.nu == 0 || N.mu == 0 || N.nu == 0)
		return INFEASIBLE;
	if (M.mu != N.mu || M.nu != N.nu)
		return ERROR;
	for (int i = 1; i <= M.tu; i++) {
		T.data[i].e = M.data[i].e;
		T.data[i].i = M.data[i].i;
		T.data[i].j = M.data[i].j;
	}
	T.mu = M.mu;
	T.nu = M.nu;
	T.tu = M.tu;
	for (int i = 1; i <= N.tu; i++) {
		int j = 1;
		for (; j <= M.tu; j++) {
			if (M.data[j].i == N.data[i].i && M.data[j].j == N.data[i].j) {
				T.data[j].e -= N.data[i].e;
			}
		}
		if (j == M.tu + 1) {
			T.tu++;
			T.data[T.tu].e = N.data[i].e;
			T.data[T.tu].i = N.data[i].i;
			T.data[T.tu].j = N.data[i].j;
		}
	}
	for (int i = 1; i <= T.tu; i++) {
		if (T.data[i].e == 0) {
			T.data[i].e = T.data[T.tu].e;
			T.data[i].i = T.data[T.tu].i;
			T.data[i].j = T.data[T.tu].j;
			T.tu--;
			i--;
		}
	}
	return OK;
}

status MultSMattrix(TSMatrix M, TSMatrix N, TSMatrix &T) {
//��ʼ������M,N���ڣ�M������=N������
//�����������ϡ�����ĳ˻�
	if (M.mu == 0 || M.nu == 0 || N.mu == 0 || N.nu == 0)
		return INFEASIBLE;
	if (M.nu != N.mu)
		return ERROR;
	T.mu = M.mu;
	T.nu = N.nu;
	int k = 1;
	for (int i = 1; i <= M.tu; i++) {
		for (int j = 1; j <= N.tu; j++) {
			if (M.data[i].j == N.data[j].i) {
				T.data[k].e += M.data[i].e * N.data[j].e;
				T.data[k].i = M.data[i].i;
				T.data[k].j = N.data[j].j;
				k++;
			}
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = i + 1; j <= k; j++) {
			if (T.data[i].i == T.data[j].i && T.data[i].j == T.data[j].j) {
				T.data[i].e += T.data[j].e;
				T.data[j].e = 0;
			}
		}
	}
	for (int i = 1; i <= k; i++) {
		if (T.data[i].e == 0) {
			T.data[i].e = T.data[k].e;
			T.data[i].i = T.data[k].i;
			T.data[i].j = T.data[k].j;
			k--;
			i--;
		}
	}
	T.tu = k;
	return OK;
}

status TransposeSMattrix(TSMatrix M, TSMatrix &T) {
//��ʼ������M����
//�����������ϡ�����Mת�þ���T
	if (M.mu == 0 || M.nu == 0)
		return INFEASIBLE;
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	for (int i = 1; i <= T.tu; i++) {
		T.data[i].e = M.data[i].e;
		T.data[i].i = M.data[i].j;
		T.data[i].j = M.data[i].i;
	}
	return OK;
}

int main() {
	TSMatrix M, N, T;
	int op = 1, ans, x, y;
	while (op) {
		system("cls");
		printf("\n");
		printf("    Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------\n");
		printf("        1. CreateSMattrix ������ϡ�����\n");
		printf("        2. DestroySMattrix ������ϡ�����\n");
		printf("    	3. PrintSMattrix �����ϡ�����\n");
		printf("        4. CopySMattrix ������ϡ�����\n");
		printf("        5. AddSMattrix ��ϡ�������ӣ�\n");
		printf("    	6. SubtMattrix ��ϡ����������\n");
		printf("        7. MultSMattrix ��ϡ�����˻���\n");
		printf("    	8. TransposeSMattrix ��ϡ�����ת�ã�\n");
		printf("        0. Exit���˳��˵���\n");
		printf("----------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~8]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				printf("1.��������M\n2.��������N\n");
				scanf("%d", &x);
				if (x == 1)
					ans = CreateSMattrix(M);
				else
					ans = CreateSMattrix(N);
				printf("�����ɹ�");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroySMattrix(M);
				if (ans)
					printf("���ٳɹ�");
				else
					printf("����ʧ��");
				getchar();
				getchar();
				break;
			case 3:
				printf("1.�������M\n2.�������N\n3.�������T\n");
				scanf("%d", &x);
				if (x == 1)
					ans = PrintSMattrix(M);
				if (x == 2)
					ans = PrintSMattrix(N);
				if (x == 3)
					ans = PrintSMattrix(T);
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���\n");
				getchar();
				getchar();
				break;
			case 4:
				printf("������__���Ƶõ�����__��\n1.����M\n2.����N\n3.����T\n");
				scanf("%d %d", &x, &y);
				if (x == 1 && y == 3)
					ans = CopySMattrix(M, T);
				else if (x == 1 && y == 2)
					ans = CopySMattrix(M, N);
				else if (x == 2 && y == 1)
					ans = CopySMattrix(N, M);
				else if (x == 2 && y == 3)
					ans = CopySMattrix(N, T);
				else if (x == 3 && y == 1)
					ans = CopySMattrix(T, M);
				else if (x == 3 && y == 2)
					ans = CopySMattrix(T, N);
				else {
					printf("������Ч\n");
					getchar();
					getchar();
					break;
				}
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���");
				else
					printf("���Ƴɹ�");
				getchar();
				getchar();
				break;
			case 5:
				ans = AddSMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���");
				else if (ans == ERROR)
					printf("��Ӵ���");
				else
					printf("�ɹ���T=M+N");
				getchar();
				getchar();
				break;
			case 6:
				ans = SubtMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���");
				else if (ans == ERROR)
					printf("�������");
				else
					printf("�ɹ���T=M-N");
				getchar();
				getchar();
				break;
			case 7:
				ans = MultSMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���");
				else if (ans == ERROR)
					printf("��˴���");
				else
					printf("�ɹ���T=M*N");
				getchar();
				getchar();
				break;
			case 8:
				ans = TransposeSMattrix(M, T);
				if (ans == INFEASIBLE)
					printf("ϡ����󲻴���");
				else if (ans == ERROR)
					printf("ת�ô���");
				else
					printf("�ɹ�");
				getchar();
				getchar();
				break;
			case 0:
				break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}