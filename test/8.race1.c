// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define M 200
#define N 200

int main() {
  double A[M], B[M][N], C[N], sum0 = 0.0;
  for (int i = 0; i < M; i++) {
#pragma omp parallel for // reduction(+:sum0)
    for (int j = 0; j < N; j++) {
      sum0 += B[i][j] * C[j];
    }
    A[i] = sum0;
  }
}
// CHECK: Data Race detected
// END
