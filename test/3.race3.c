// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N][N];
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
#pragma omp parallel for
      for (int k = 1; k < N; k++)
        A[i][j][k] = A[i][j][k - 1];
}
// CHECK: Data Race detected
// END
