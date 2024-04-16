#include <stdio.h>
#include <stdlib.h>

// Lagrange polynomial
int n;
double *x, *y, *param;
double Lagrange(int n, double *x, double *y, double *param);
int main() {
  printf("Enter the number of points:");
  scanf("%d", &n);
  x = (double *)malloc(n * sizeof(double));
  y = (double *)malloc(n * sizeof(double));
  printf("Enter x:");
  for (int i = 0; i < n; i++) {
    scanf("%lf", x + i);
  }
  printf("Enter y:");
  for (int i = 0; i < n; i++) {
    scanf("%lf", y + i);
  }
  Lagrange(n, x, y, param);
  return 0;
}
