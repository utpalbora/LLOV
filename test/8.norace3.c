// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define M 200
#define N 200

int main() {
  double A[M], B[M][N], C[N], sum = 0.0;
#pragma omp parallel for firstprivate(sum)
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      sum += B[i][j] * C[j];
    }
    A[i] = sum;
    sum = 0.0;
  }
}
// CHECK: Region is Data Race Free.
// END
