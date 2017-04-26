// Feature tests of dynamic checking in Checked C
//
// The following lines are for the LLVM test harness:
//
// RUN: %clang -fcheckedc-extension -Xclang -verify -o %t.exe %s
// RUN: %t.exe

// expected-no-diagnostics

#include <stdbool.h>
#include "../../../include/stdchecked.h"

int main(void) {
  dynamic_check(true);

  return 0;
}
