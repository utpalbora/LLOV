// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N];
  for (int i = 1; i < N; i++)
#pragma omp simd
    for (int j = 1; j < N; j++)
      A[i][j] = A[i][j] + i + j;
}
// CHECK: Region is Data Race Free.
// END
