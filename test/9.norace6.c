// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>
#define N 40

int main() {
  int F[N], x = 1, y = 1;
#pragma omp parallel
  {
#pragma omp single firstprivate(x, y)
    for (int i = 3; i < N; i++) {
      F[i] = x + y;
      y = x;
      x = F[i];
    }
  }
  return 0;
}
// We do not support inter SCoP data races for now
// CHECK: Region is Data Race Free.
// END
