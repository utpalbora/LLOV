// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define T 2000
#define M 20
#define N 20

int main() {
  double A[M][N], B[M][N];
  for (int t = 0; t < T; t++) {
#pragma omp parallel for
    for (int i = 1; i < M - 1; i++)
      for (int j = 1; j < N - 1; j++)
        B[i][j] = (0.2) * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[1 + i][j] +
                           A[i - 1][j]);
#pragma omp parallel for
    for (int i = 1; i < M - 1; i++)
      for (int j = 1; j < N - 1; j++)
        A[i][j] = (0.2) * (B[i][j] + B[i][j - 1] + B[i][1 + j] + B[1 + i][j] +
                           B[i - 1][j]);
  }
}
// CHECK: Region is Data Race Free.
// CHECK: Region is Data Race Free.
// END
