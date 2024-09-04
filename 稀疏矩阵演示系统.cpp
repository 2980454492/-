#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXSIZE 12500 //非零元个数的最大值为12500
typedef int status;
typedef int ElemType; //数据元素类型定义

//稀疏矩阵的三元顺序表存储表示
typedef struct {
	int i, j; //该非零元素的行下标和列下标
	ElemType e;
} Triple;

typedef struct {
	Triple data[MAXSIZE + 1]; //非零元三元组表，data[0]未使用
	int mu, nu, tu; //矩阵的行数，列数和非零元素个数
} TSMatrix;

status CreateSMattrix(TSMatrix &M) {
//初始条件：M不存在
//操作结果：创建稀疏矩阵M
	printf("请输入矩阵的行数、列数、非零元的个数\n");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
	for (int i = 1; i <= M.tu; i++) {
		printf("请输入第%d个元素的位置和值：", i);
		scanf("%d %d %d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
		if (M.data[i].i > M.mu || M.data[i].i < 1 || M.data[i].j > M.nu || M.data[i].j < 1) {
			printf("元素无意义，请重新输入\n");
			i--;
		}
		for (int j = 1; j < i; j++) {
			if (M.data[i].i == M.data[j].i && M.data[i].j == M.data[j].j) {
				printf("元素重复定义，请重新输入\n");
				i--;
			}
		}
	}
	return OK;
}

status DestroySMattrix(TSMatrix &M) {
//初始条件：M存在
//操作结果：销毁稀疏矩阵M
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
//初始条件：M存在
//操作结果：输出稀疏矩阵M
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
//初始条件：M存在
//操作结果：将稀疏矩阵M复制得到T
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
//初始条件：M,N存在，行数列数对应相等
//操作结果：求稀疏矩阵的和Q
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
//初始条件：M,N存在，行数列数对应相等
//操作结果：求稀疏矩阵的差Q
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
//初始条件：M,N存在，M的行数=N的列数
//操作结果：求稀疏矩阵的乘积
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
//初始条件：M存在
//操作结果：求稀疏矩阵M转置矩阵T
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
		printf("        1. CreateSMattrix （创建稀疏矩阵）\n");
		printf("        2. DestroySMattrix （销毁稀疏矩阵）\n");
		printf("    	3. PrintSMattrix （输出稀疏矩阵）\n");
		printf("        4. CopySMattrix （复制稀疏矩阵）\n");
		printf("        5. AddSMattrix （稀疏矩阵相加）\n");
		printf("    	6. SubtMattrix （稀疏矩阵相减）\n");
		printf("        7. MultSMattrix （稀疏矩阵乘积）\n");
		printf("    	8. TransposeSMattrix （稀疏矩阵转置）\n");
		printf("        0. Exit（退出菜单）\n");
		printf("----------------------------------------------\n");
		printf("    请选择你的操作[0~8]:");
		scanf("%d", &op);
		switch (op) {
			case 1:
				printf("1.创建矩阵M\n2.创建矩阵N\n");
				scanf("%d", &x);
				if (x == 1)
					ans = CreateSMattrix(M);
				else
					ans = CreateSMattrix(N);
				printf("创建成功");
				getchar();
				getchar();
				break;
			case 2:
				ans = DestroySMattrix(M);
				if (ans)
					printf("销毁成功");
				else
					printf("销毁失败");
				getchar();
				getchar();
				break;
			case 3:
				printf("1.输出矩阵M\n2.输出矩阵N\n3.输出矩阵T\n");
				scanf("%d", &x);
				if (x == 1)
					ans = PrintSMattrix(M);
				if (x == 2)
					ans = PrintSMattrix(N);
				if (x == 3)
					ans = PrintSMattrix(T);
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在\n");
				getchar();
				getchar();
				break;
			case 4:
				printf("将矩阵__复制得到矩阵__：\n1.矩阵M\n2.矩阵N\n3.矩阵T\n");
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
					printf("输入无效\n");
					getchar();
					getchar();
					break;
				}
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在");
				else
					printf("复制成功");
				getchar();
				getchar();
				break;
			case 5:
				ans = AddSMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在");
				else if (ans == ERROR)
					printf("相加错误");
				else
					printf("成功，T=M+N");
				getchar();
				getchar();
				break;
			case 6:
				ans = SubtMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在");
				else if (ans == ERROR)
					printf("相减错误");
				else
					printf("成功，T=M-N");
				getchar();
				getchar();
				break;
			case 7:
				ans = MultSMattrix(M, N, T);
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在");
				else if (ans == ERROR)
					printf("相乘错误");
				else
					printf("成功，T=M*N");
				getchar();
				getchar();
				break;
			case 8:
				ans = TransposeSMattrix(M, T);
				if (ans == INFEASIBLE)
					printf("稀疏矩阵不存在");
				else if (ans == ERROR)
					printf("转置错误");
				else
					printf("成功");
				getchar();
				getchar();
				break;
			case 0:
				break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}