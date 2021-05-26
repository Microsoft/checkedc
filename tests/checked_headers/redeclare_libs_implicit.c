// Feature tests of typechecking bounds-safe
// interfaces for the C standard library.
//
// The following lines are for the LLVM test harness:
//
// Test include files in an unchecked scope
//
// RUN: %clang -fsyntax-only %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=0 %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=1 %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=2 %s
//
// Test include files in a checked scope.
//
// RUN: %clang -fsyntax-only  -DCHECKED_SCOPE=1 %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=0 -DCHECKED_SCOPE=1 %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=1 -DCHECKED_SCOPE=1 %s
// RUN: %clang -fsyntax-only -D_FORTIFY_SOURCE=2 -DCHECKED_SCOPE=1 %s
//
// Test include files for all combinations of Checked C enabled/disabled,
// and implicit inclusion of checked headers enabled/disabled. By default, both
// are enabled.
//
// Checked headers are disabled for no Checked C.
// RUN: %clang -fno-checkedc-extension -E %s | FileCheck %s --check-prefix CHECK_DISABLED
// RUN: %clang -fno-checkedc-extension -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_DISABLED
//
// Checked headers are enabled for Checked C and implicit inclusion.
// RUN: %clang -E %s | FileCheck %s --check-prefix CHECK_ENABLED
//
// Checked headers are disabled because implicit inclusion is disabled.
// RUN: %clang -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_DISABLED


#if CHECKED_SCOPE
#pragma CHECKED_SCOPE on
#endif

// C Standard
#include <assert.h>
// CHECK_ENABLED: assert_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: assert_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <errno.h>
// CHECK_ENABLED: errno_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: errno_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <fenv.h>
// CHECK_ENABLED: fenv_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: fenv_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <inttypes.h>
// CHECK_ENABLED: inttypes_checked_internal.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: inttypes_checked_internal.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <math.h>
// CHECK_ENABLED: math_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: math_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <signal.h>
// CHECK_ENABLED: signal_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: signal_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <stdio.h>
// CHECK_ENABLED: stdio_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: stdio_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <stdlib.h>
// CHECK_ENABLED: stdlib_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: stdlib_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <string.h>
// CHECK_ENABLED: string_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: string_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#define _CHECKEDC_MOCKUP_THREADS 1
#include <threads.h>
// CHECK_ENABLED: threads_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: threads_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <time.h>
// CHECK_ENABLED: time_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: time_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

// Headers that are not in the C standard but are still present on Windows

#include <fcntl.h>
// CHECK_ENABLED: fcntl_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: fcntl_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <sys/stat.h>
// CHECK_ENABLED: stat_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: stat_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on
