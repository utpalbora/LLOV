// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N][N];
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
#pragma omp simd
      for (int k = 1; k < N; k++)
        A[i][j][k] = A[i][j][k];
}
// CHECK: Region is Data Race Free.
// END
