// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 200

int main() {
  double A[N], C[N], sum0 = 0.0;
#pragma omp parallel for simd reduction(+ : sum0)
  for (int i = 0; i < N; i++) {
    sum0 += A[i] * C[i];
  }
}
// CHECK: Region is Data Race Free.
// END
