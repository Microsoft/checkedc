// UNSUPPORTED: system-windows
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


// Posix Headers
// These header files are not present in the Windows compilation environment.
#include <unistd_checked.h>
// CHECK_MIXED: unistd_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <sys/socket.h>
// CHECK_MIXED-NOT: socket_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <arpa/inet_checked.h>
// CHECK_MIXED: inet_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <grp.h>
// CHECK_MIXED-NOT: grp_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <netdb_checked.h>
// CHECK_MIXED: netdb_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <poll.h>
// CHECK_MIXED-NOT: poll_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <pwd_checked.h>
// CHECK_MIXED: pwd_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on

#include <syslog.h>
// CHECK_MIXED-NOT: syslog_checked.h
// CHECK_MIXED-NOT: #pragma CHECKED_SCOPE on

#include <utime_checked.h>
// CHECK_MIXED: utime_checked.h
// CHECK_MIXED: #pragma CHECKED_SCOPE on
