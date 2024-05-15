#include <stdio.h>
#include <math.h>

#define EPSILON 1e-7
#define MAX_ITERATIONS 20

long double f1(long double x){ return sin(x)/x; }
long double f2(long double x){ return exp(-x*x); }
long double f3(long double x){ return x ? log(1+x)/x : 1; }

long double trapezoidal(long double a, long double b, int n, long double (*f)(long double)){
    long double h = (b - a) / n, sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) sum += f(a + i * h);
    return h * sum;
}

long double simpson(long double a, long double b, int n, long double (*f)(long double)){
    long double h = (b - a) / n, sum = f(a) + f(b) + 4 * f(a + 0.5 * h);
    for(int i = 1; i < n; i++) sum += (2 * f(a + i * h) + 4 * f(a + (i + 0.5) * h));
    return h / 6 * sum;
}

void integral(long double a, long double b, long double (*f)(long double), long double (*method)(long double, long double, int, long double (*)(long double))){
    long double result = method(a, b, 1, f), new_result;
    int i = 1;
    for (new_result = method(a, b, 1 << i, f); (fabsl(result) <= 100 && fabsl(result - new_result) >= EPSILON) ||
        ( fabsl(result) > 100 && (fabsl((result - new_result) / new_result) >= EPSILON)); i++){
        result = new_result;
        new_result = method(a, b, 1 << (i + 1), f);
    }
    int ans1 = 1 << i, ans2 = (method==trapezoidal) ? ans1 + 1 : (ans1 << 1) + 1;
    printf("积分结果: %.8Lf\n区间个数: %d\n基点个数: %d\n", result, ans1, ans2);
}

int main(void){
    long double (*funcPtr[3])(long double) = {f1, f2, f3};
    long double range[3][2] = {{0.1, 4}, {-2, 4}, {0, 1}};
    for(int i=0;i<3;i++){
        printf("----------------------------------------------------------------------\n");
        printf("|                         测试 %d 开始！                              ｜",i+1);
        printf("\n----------------------------------------------------------------------\n");
        printf("\n复合梯形公式：\n");
        integral(range[i][0], range[i][1], funcPtr[i], trapezoidal);
        printf("\n复合Simpson公式：\n");
        integral(range[i][0], range[i][1], funcPtr[i], simpson);
        printf("\n龙贝格积分法：\n");
        long double T[2][MAX_ITERATIONS];
        T[0][0] = trapezoidal(range[i][0], range[i][1], 1, funcPtr[i]);
        printf("T[0][0] = %.8Lf\n", T[0][0]);
        for (int j = 1; j < MAX_ITERATIONS; j++) {
            T[1][0] = trapezoidal(range[i][0], range[i][1], 1 << j, funcPtr[i]);
            printf("T[%d][0] = %.8Lf ", j, T[1][0]);
            for (int k = 1; k <= j; k++) {
                T[1][k] = T[1][k - 1] + (T[1][k - 1] - T[0][k - 1]) / ((1 << (2 * k)) - 1);
                printf("T[%d][%d] = %.8Lf ", j, k, T[1][k]);
            }
            printf("\n");
            if ((fabsl(T[1][j]) <= 100 && (fabsl(T[1][j] - T[0][j - 1]) < EPSILON)) ||
                (fabsl(T[1][j]) > 100 && (fabsl((T[1][j] - T[0][j - 1]) / T[1][j]) < EPSILON))) {
                printf("积分结果: %.8Lf\n\n", T[1][j]);
                break;
            }
            for (int k = 0; k <= j; k++) T[0][k] = T[1][k];
        }
    }
}
