// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Fig. 4
#include <omp.h>
#define N 20
#define M 20

int main() {
  int uold[N][M], u[N][M];
  int i, j;
  double b = 1.0, omega = 0.8, resid, error = 0.0;
#pragma omp parallel for private(j, resid) reduction(+ : error)
  for (i = 1; i < N; i++) {
    for (j = 1; j < M; j++) {
      resid = (uold[i][j] + uold[i - 1][j] + uold[i + 1][j] + uold[i][j - 1] +
               uold[i][j + 1]) /
              b;
      u[i][j] = uold[i][j] - omega * resid;
      error = error + resid * resid;
    }
  }
}
// CHECK: Region is Data Race Free.
// END
