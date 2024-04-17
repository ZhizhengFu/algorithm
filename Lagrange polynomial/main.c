#include <stdio.h>
#include <stdlib.h>

// Lagrange polynomial
int n;
double *x, *y, *param, *temp;
void Lagrange();
void l(int j);
int main() {
  printf("Enter the number of points:");
  scanf("%d", &n);
  x = (double *)malloc(n * sizeof(double));
  y = (double *)malloc(n * sizeof(double));
  temp = (double *)malloc(n * sizeof(double));
  param = (double *)calloc(n, sizeof(double));
  printf("Enter x:");
  for (int i = 0; i < n; i++) {
    scanf("%lf", x + i);
  }
  printf("Enter y:");
  for (int i = 0; i < n; i++) {
    scanf("%lf", y + i);
  }
  Lagrange();
  return 0;
}
void l(int j) {
  double t1 = 1.0;
  double t2;
  for (int i = 0; i < n; i++)
    temp[i] = 0;
  temp[0] = 1;
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (i == j)
      continue;
    t1 *= (1.0 / (x[j] - x[i]));
    t2 = -x[i];
    temp[count + 1] = 1;
    int k = count;
    for (; k > 0; k--) {
      temp[k] = temp[k - 1] + t2 * temp[k];
    }
    temp[0] = t2 * temp[0];
    count++;
  }
  for (int i = 0; i < n - 1; i++) {
    temp[i] *= t1;
  }
}
void Lagrange() {
  for (int i = 0; i < n; i++) {
    l(i);
    for (int j = 0; j < n; j++) {
      param[i] += y[j] * temp[j];
    }
  }
  printf("The Lagrange polynomial is:\n");
  for (int i = 0; i < n; i++) {
    printf("%lf", param[i]);
    if (i != 0) {
      printf("x^%d", i);
    }
    if (i != n - 1) {
      printf("+");
    }
  }
}
