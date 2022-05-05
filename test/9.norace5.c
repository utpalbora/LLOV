// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
// XFAIL: *
#include <omp.h>
#define N 100

int main() {
  int sum = 0;
#pragma omp ordered simd
  for (int i = 0; i < N; i++) {
    sum += i;
  }
  return sum;
}
// We do not support inter SCoP data races for now
// CHECK: Region is Data Race Free.
// END
