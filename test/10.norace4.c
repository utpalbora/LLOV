// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 100

int main() {
  int sum = 0;
#pragma omp parallel num_threads(8)
  {
#pragma omp sections reduction(+ : sum)
    {
      for (int i = 0; i < N; i++) {
        sum += i;
      }
#pragma omp section
      for (int i = 0; i < N; i++) {
        sum += i * i;
      }
    }
  }
  return sum % (N * N);
}
// CHECK: Region is Data Race Free.
// END
