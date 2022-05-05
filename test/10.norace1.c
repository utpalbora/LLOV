// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
// XFAIL: *
// Polly not detecting SCoP. Need to fix
#include <omp.h>

int main() {
  int x = 0;
#pragma omp parallel num_threads(8)
  {
#pragma omp sections firstprivate(x)
    {
      { x = 1; }
#pragma omp section
      { x = 2; }
    }
  }
  return x;
}
// CHECK: Region is Data Race Free.
// END
