// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// XFAIL: *
// Taken from ompVerify, Fig. 3
#include <omp.h>
#define N 20

int main() {
  int A[N][N];
  int p1, p2, temp;
#pragma omp parallel private(p1, p2, temp)
  {
#pragma omp for
    for (p1 = 0; p1 < N; p1++)
#pragma omp parallel for
      for (p2 = 0; p2 < p1; p2++) {
        temp = A[p1][p2];
        A[p1][p2] = A[p2][p1];
        A[p2][p1] = temp;
      }
  }
}
// CHECK: Region is Data Race Free.
// END
