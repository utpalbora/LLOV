// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 20

int main() {
  int A[N][N];
#pragma omp parallel for
  for (int i = 1; i < N; i++)
    for (int j = 0; j < N; j++)
      // Array Out of Bound Access
      A[i][j] = A[i][j - 1];
}
// CHECK: Data Race detected
// END
