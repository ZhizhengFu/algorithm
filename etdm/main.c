// input:            n  : number of equations
//         a1 a2 ... an : lower diagonal
//         b1 b2 ... bn : main diagonal
//         c1 c2 ... cn : upper diagonal
//         d1 d2 ... dn : right side
// output: x1 x2 ... xn : solution
#include <stdio.h>
#define F(a) double a[n];for(i=0;i<n;i++)scanf("%lf", a+i);
#define G(a) a[i] = (a[i] - c[i] * a[i+1]) / b[i];
int n, i;
int main(){
    scanf("%d", &n);
    F(a) F(b) F(c) F(d)
    *a*=-1;n--;
    for(i=1;n-i;i++){
        a[i] /= b[i-1];
        b[i] -= a[i] * c[i-1];
        d[i] -= a[i] * d[i-1];
        a[i] *= -a[i-1];
    }i--;
    a[i] = (a[i] - c[i]) / b[i];
    d[i] /= b[i];
    for(--i;i+1;i--){ G(a) G(d) }
    a[n]=(d[n]-c[n]**d-a[n]*d[n-1])/(b[n]+a[n]*a[n-1]+c[n]**a);
    for(++i;n-i;i++) printf("x%d = %lf\n",i+1, d[i]+a[i]*a[n]);
    printf("x%d = %lf", n+1, a[i]);
}
