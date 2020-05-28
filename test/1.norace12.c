// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define M 20
#define N 20

int main() {
  double A[M][N], C[M][N], alpha = 0.5, beta = 0.3;
#pragma omp parallel for
  for (int i = 0; i < M; i++) {
    for (int j = 0; j <= i; j++)
      C[i][j] *= beta;
    for (int k = 0; k < N; k++) {
      for (int j = 0; j <= i; j++)
        C[i][j] += alpha * A[i][k] * A[j][k];
    }
  }
}
// CHECK: Region is Data Race Free.
// END
