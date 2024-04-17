#include <stdio.h>
#include <stdlib.h>

// Lagrange polynomial
int n;
double *x, *y, *param, *temp, t1, t2;
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
  while (1) {
    printf("CTRL+C to exit or Enter a point to evaluate:");
    scanf("%lf", &t1);
    for (int i = 0; i < n; i++) {
      t2 = 0;
      double t3 = 1;
      for (int j = 0; j < i; j++) {
        t3 *= t1;
      }
      t2 += param[i] * t3;
    }
    printf("The value of the polynomial at %lf is %lf\n", t1, t2);
  }
  return 0;
}
void l(int j) {
  for (int i = 0; i < n; i++) {
    temp[i] = 0;
  }
  t1 = temp[0] = 1.0;
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
  for (int i = 0; i < n; i++) {
    temp[i] *= t1;
  }
}
void Lagrange() {
  for (int i = 0; i < n; i++) {
    l(i);
    for (int j = 0; j < n; j++) {
      param[j] += y[i] * temp[j];
    }
  }
  printf("\nThe Lagrange polynomial is:\n");
  for (int i = 0; i < n; i++) {
    printf("%lf", param[i]);
    if (i != 0) {
      printf("x^%d", i);
    }
    if (i != n - 1) {
      printf("+");
    }
  }
  printf("\n\n");
}
