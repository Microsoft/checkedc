// UNSUPPORTED: system-windows
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
// Checked headers are enabled because explicit inclusion overrides the
// disabling of implicit inclusion.
// RUN: %clang -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_ENABLED


#if CHECKED_SCOPE
#pragma CHECKED_SCOPE on
#endif


// Posix Headers
// These header files are not present in the Windows compilation environment.
#include <unistd_checked.h>
// CHECK_ENABLED: unistd_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: unistd_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <sys/socket_checked.h>
// CHECK_ENABLED: socket_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: socket_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <arpa/inet_checked.h>
// CHECK_ENABLED: inet_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: inet_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <grp_checked.h>
// CHECK_ENABLED: grp_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: grp_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <netdb_checked.h>
// CHECK_ENABLED: netdb_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: netdb_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <poll_checked.h>
// CHECK_ENABLED: poll_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: poll_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <pwd_checked.h>
// CHECK_ENABLED: pwd_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: pwd_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <syslog_checked.h>
// CHECK_ENABLED: syslog_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: syslog_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <utime_checked.h>
// CHECK_ENABLED: utime_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED: utime_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on
