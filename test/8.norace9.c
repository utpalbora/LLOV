// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 200

int main() {
  double A[N], C[N], sum0 = 0.0;
#pragma omp parallel for ordered
  for (int i = 0; i < N; i++) {
#pragma omp ordered
    sum0 += A[i] * C[i];
  }
}
// CHECK: Region Not Analyzed by the verifier.
// END
