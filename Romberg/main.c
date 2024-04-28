#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 5000

typedef struct {
    int k;
    double a, b, epsilon;
    double *T;
} Polynomial;

double f(double x);
int trans(int d, int u);
int two(int k);
double sum(Polynomial *r, int n);
double absolute(double x);
void readInput(Polynomial *r);
void Romberg(Polynomial *r);
int main() {
    Polynomial r;
    readInput(&r);
    Romberg(&r);
}
void Romberg(Polynomial *r){
    r->k = 0;
    r->T = (double *)calloc(MAX, sizeof(double));
    r->T[0] = 0.5 * (r->b - r->a)*(f(r->a) + f(r->b));
    do{
        r->k++;
        r->T[trans(0,r->k)] = 0.5 * r->T[trans(0,r->k-1)] + 0.5 * (r->b-r->a)/two(r->k-1) * sum(r, two(r->k-1));
        for(int j=1;j<=r->k;j++){
            double tmp = (double)two(2*j);
            r->T[trans(j,r->k-j)] = tmp/(tmp-1) * r->T[trans(j-1,r->k-j+1)] - 1/(tmp-1)*r->T[trans(j-1,r->k-j)];
        }
    }while(absolute(r->T[trans(r->k,0)]-r->T[trans(r->k-1,0)])<r->epsilon);
    printf("The result is %lf\n", r->T[trans(r->k,0)]);
}
double absolute(double x){
    if(x<0)return -x;
    return x;
}
double sum(Polynomial *r, int n){
    double ans = 0;
    for(int k=0;k<=n-1;k++){
        ans += f(r->a + (k+0.5)*(r->b-r->a)/n);
    }
    return ans;
}
int trans(int d, int u){
    return (d+u)*(d+u+1)/2+d;
}
int two(int k){
    if(k==0)return 1;
    return 2*two(k-1);
}
double f(double x) {
    return x*x;
}
void readInput(Polynomial *r) {
    printf("Enter a:");
    scanf("%lf", &(r->a));
    printf("Enter b:");
    scanf("%lf", &(r->b));
    printf("Enter epsilon:");
    scanf("%lf", &(r->epsilon));
}
