// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N];
#pragma omp parallel for
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N - 1; j++)
      A[i][j] = A[i][j + 1];
}
// CHECK: Region is Data Race Free.
// END
