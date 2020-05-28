// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include <omp.h>

int main() {
  int x = 0;
#pragma omp parallel num_threads(8)
  {
#pragma omp sections // firstprivate(x)
    {
      { x = 1; }
#pragma omp section
      { x = 2; }
    }
  }
  return x;
}
// CHECK: Data Race detected
// END
