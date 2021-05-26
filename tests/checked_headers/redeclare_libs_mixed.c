// Feature tests of typechecking bounds-safe
// interfaces for the C standard library.
//
// Test include files for all combinations of Checked C enabled/disabled,
// and implicit inclusion of checked headers enabled/disabled. By default, both
// are enabled.
//
// Checked headers are disabled for no Checked C.
// Already tested in redeclare_libs_explicit.c and redeclare_libs_implicit.c.
//    %clang -fno-checkedc-extension -E %s | FileCheck %s --check-prefix CHECK_DISABLED
//    %clang -fno-checkedc-extension -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_DISABLED
//
// Checked headers are enabled for Checked C and implicit inclusion.
// Already tested in redeclare_libs_explicit.c and redeclare_libs_implicit.c.
//    %clang -E %s | FileCheck %s --check-prefix CHECK_ENABLED
//
// Checked headers are enabled/disabled depending on whether foo.h or
// foo_checked.h is included for a system header file foo.h.
// RUN: %clang -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_MIXED


// C Standard
#include <assert_checked.h>
// CHECK_MIXED: assert_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <errno.h>
// CHECK_MIXED-NOT: errno_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <fenv_checked.h>
// CHECK_MIXED: fenv_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <inttypes.h>
// CHECK_MIXED-NOT: inttypes_checked_internal.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <math_checked.h>
// CHECK_MIXED: math_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <signal.h>
// CHECK_MIXED-NOT: signal_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <stdio_checked.h>
// CHECK_MIXED: stdio_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <stdlib.h>
// CHECK_MIXED-NOT: stdlib_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <string_checked.h>
// CHECK_MIXED: string_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#define _CHECKEDC_MOCKUP_THREADS 1
#include <threads.h>
// CHECK_MIXED-NOT: threads_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <time_checked.h>
// CHECK_MIXED: time_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

// Headers that are not in the C standard but are still present on Windows

#include <fcntl.h>
// CHECK_MIXED-NOT: fcntl_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <sys/stat_checked.h>
// CHECK_MIXED: stat_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <checkedc_extensions.h>
// CHECK_MIXED: checkedc_extensions.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on
