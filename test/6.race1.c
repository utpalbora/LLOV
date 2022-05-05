// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Fig. 1
#include <omp.h>
#define N 20

int main() {
  int x[N], b[N], L[N][N];
#pragma omp parallel for
  for (int i = 0; i < N; i++) {
    x[i] = b[i];
    for (int j = 0; j < i; j++)
      x[i] = x[i] - L[i][j] * x[j];
    x[i] = x[i] / L[i][i];
  }
}
// CHECK: Data Race detected
// END
