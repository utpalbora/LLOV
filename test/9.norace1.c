// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
// XFAIL: *
#include <omp.h>
#define N 20

int main() {
  int sum = 0;
  for (int i = 0; i < N; i++) {
#pragma omp critical
    sum += i;
  }
  return sum;
}
// We do not support inter SCoP data races for now
// CHECK: Region is Data Race Free.
// END
