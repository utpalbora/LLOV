// RUN: clang %clangLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>

int main() {
  int x = 100, y = 200;
#pragma omp parallel num_threads(8)
  {
#pragma omp sections firstprivate(x) private(y)
    {
      { y = x * 3; }
#pragma omp section
      {
        y = 4 * x;
        x = y - x;
      }
    }
  }
  return 0;
}
// CHECK: Region is Data Race Free.
// END
