#include <stdio.h>
#include <math.h>

long double f1(long double x){ return sin(x)/x; }
long double f2(long double x){ return exp(-x*x); }
long double f3(long double x){ if(x==0)return 1; return log(1+x)/x; }
long double (*funcPtr[3])(long double) = {f1, f2, f3};
long double range[3][2] = {{0.1, 4}, {-2, 4}, {0, 1}};
long double Eps = 1e-7;

long double composite_trapezoidal(long double a, long double b, int n, long double (*f)(long double)){
    long double h = (b - a) / n;
    long double sum = 0.5 * (f(a) + f(b));
    long double x;
    for (int i = 1; i < n; i++) {
        x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

long double composite_simpson(long double a, long double b, int n, long double (*f)(long double)){
    long double h = (b - a) / n;
    long double sum = f(a) + f(b);
    long double x;
    for (int i = 1; i < n; i++) {
        x = a + i * h;
        sum += 4 * f(x + 0.5 * h) + 2 * f(x);
    }
    sum += 4 * f(a + 0.5 * h);
    return h / 6 * sum;
}

void calculate_integral(long double a, long double b, long double (*f)(long double), long double (*method)(long double, long double, int, long double (*)(long double))){
    int n = 1;
    long double result = method(a, b, n, f);
    long double new_result;

    while (1) {
        new_result = method(a, b, 2 * n, f);
        if (fabs(result - new_result) < Eps) break;
        n *= 2;
        result = new_result;
    }
    printf("积分结果: %.8Lf\n", result);
    printf("区间个数: %d\n", n);
    printf("基点个数: %d\n", n + 1);
}

int main(){
    for(int i=0;i<3;i++){
        printf("----------------------------------------------------------------------\n");
        printf("|                         测试 %d 开始！                              ｜\n",i+1);
        printf("----------------------------------------------------------------------\n");

        printf("\n复合梯形公式：\n");
        calculate_integral(range[i][0], range[i][1], funcPtr[i], composite_trapezoidal);

        printf("\n复合Simpson公式：\n");
        calculate_integral(range[i][0], range[i][1], funcPtr[i], composite_simpson);

        printf("\n龙贝格积分法：\n");
        long double T[2][100];
        T[0][0] = composite_trapezoidal(range[i][0], range[i][1], 1, funcPtr[i]);
        printf("T[0][0] = %.8Lf\n", T[0][0]);
        long double pow2j, pow4k;
        for (int j = 1; j < 100; j++) {
            pow2j = 1 << j;
            T[1][0] = composite_trapezoidal(range[i][0], range[i][1], pow2j, funcPtr[i]);
            printf("T[%d][0] = %.8Lf ", j, T[1][0]);
            for (int k = 1; k <= j; k++) {
                pow4k = 1 << (2 * k);
                T[1][k] = T[1][k - 1] + (T[1][k - 1] - T[0][k - 1]) / (pow4k - 1);
                printf("T[%d][%d] = %.8Lf ", j, k, T[1][k]);
            }
            printf("\n");
            if (fabs(T[1][j] - T[0][j - 1]) < Eps) {
                printf("积分结果: %.8Lf\n\n", T[1][j]);
                break;
            }
            for (int k = 0; k <= j; k++) {
                T[0][k] = T[1][k];
            }
        }
    }
}
