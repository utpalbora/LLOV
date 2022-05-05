// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 200

int main() {
  int A[N], x = 0;
#pragma omp parallel for linear(x : 2)
  for (int i = 0; i < N; i++)
    A[i] = x;
}
// CHECK: Region is Data Race Free.
// END
