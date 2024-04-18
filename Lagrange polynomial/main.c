#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int n;
  double *x, *y, *param, *temp, t1, t2;
} Polynomial;

void Lagrange(Polynomial *p);
void l(Polynomial *p, int j);
void readInput(Polynomial *p);
void evaluatePolynomial(Polynomial *p);

int main() {
  Polynomial p;
  readInput(&p);
  Lagrange(&p);
  while (1) {
    evaluatePolynomial(&p);
  }
}

void readInput(Polynomial *p) {
  printf("Enter the number of points:");
  scanf("%d", &(p->n));
  p->x = (double *)malloc(p->n * sizeof(double));
  p->y = (double *)malloc(p->n * sizeof(double));
  p->temp = (double *)malloc(p->n * sizeof(double));
  p->param = (double *)calloc(p->n, sizeof(double));
  printf("Enter x:");
  for (int i = 0; i < p->n; i++) {
    scanf("%lf", p->x + i);
  }
  printf("Enter y:");
  for (int i = 0; i < p->n; i++) {
    scanf("%lf", p->y + i);
  }
}

void evaluatePolynomial(Polynomial *p) {
  printf("CTRL+C to exit or Enter a point to evaluate:");
  scanf("%lf", &(p->t1));
  for (int i = 0; i < p->n; i++) {
    p->t2 = 0;
    double t3 = 1;
    for (int j = 0; j < i; j++) {
      t3 *= p->t1;
    }
    p->t2 += p->param[i] * t3;
  }
  printf("The value of the polynomial at %lf is %lf\n", p->t1, p->t2);
}

void l(Polynomial *p, int j) {
  for (int i = 0; i < p->n; i++) {
    p->temp[i] = 0;
  }
  p->t1 = p->temp[0] = 1.0;
  int count = 0;
  for (int i = 0; i < p->n; i++) {
    if (i == j)
      continue;
    p->t1 *= (1.0 / (p->x[j] - p->x[i]));
    p->t2 = -p->x[i];
    p->temp[count + 1] = 1;
    int k = count;
    for (; k > 0; k--) {
      p->temp[k] = p->temp[k - 1] + p->t2 * p->temp[k];
    }
    p->temp[0] = p->t2 * p->temp[0];
    count++;
  }
  for (int i = 0; i < p->n; i++) {
    p->temp[i] *= p->t1;
  }
}

void Lagrange(Polynomial *p) {
  for (int i = 0; i < p->n; i++) {
    l(p, i);
    for (int j = 0; j < p->n; j++) {
      p->param[j] += p->y[i] * p->temp[j];
    }
  }
  printf("\nThe Lagrange polynomial is:\n");
  for (int i = 0; i < p->n; i++) {
    printf("%lf", p->param[i]);
    if (i != 0) {
      printf("x^%d", i);
    }
    if (i != p->n - 1) {
      printf("+");
    }
  }
  printf("\n\n");
}
