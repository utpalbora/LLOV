// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define M 20
#define N 20
#define O 20

int main() {
  double A[M][N], B[M][O], C[O][N];
#pragma omp parallel for
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      A[i][j] = 0.0;
      for (int k = 0; k < O; ++k)
        A[i][j] += B[i][k] * C[k][j];
    }
}
// CHECK: Region is Data Race Free.
// END
