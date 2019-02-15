// Feature tests of typechecking of uses of checked scopes introduced by
// #pragma CHECKED_SCOPE with the _Bounds_only modifier.
//
// This builds the file checked_scope_pragma.c, #defining BOUNDS_ONLY to 1.
//
// The following line is for the LLVM test harness:
//
// RUN: %clang_cc1 -Wno-unused-value -Wno-pointer-bool-conversion -verify -verify-ignore-unexpected=note -DBOUNDS_ONLY=1 %S/checked_scope_pragma.c
//
#import <stdlib.h>

int main(void) {
  return EXIT_FAILURE;
}
