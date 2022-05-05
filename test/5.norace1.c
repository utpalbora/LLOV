// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N];
#pragma omp parallel for
  for (int i = 1; i < N; i++)
    for (int j = 0; j < N; j++)
      A[i][j] = A[i][j];
}
// CHECK: Region is Data Race Free.
// END
