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
// Checked headers are disabled because implicit inclusion is disabled.
// RUN: %clang -DNO_IMPLICIT_INCLUDE_CHECKED_HDRS -E %s | FileCheck %s --check-prefix CHECK_DISABLED


// Posix Headers
// These header files are not present in the Windows compilation environment.
#include <unistd.h>
// CHECK_ENABLED: unistd_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: unistd_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <sys/socket.h>
// CHECK_ENABLED: socket_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: socket_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <arpa/inet.h>
// CHECK_ENABLED: inet_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: inet_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <grp.h>
// CHECK_ENABLED: grp_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: grp_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <netdb.h>
// CHECK_ENABLED: netdb_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: netdb_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <poll.h>
// CHECK_ENABLED: poll_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: poll_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <pwd.h>
// CHECK_ENABLED: pwd_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: pwd_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <syslog.h>
// CHECK_ENABLED: syslog_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: syslog_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on

#include <utime.h>
// CHECK_ENABLED: utime_checked.h
// CHECK_ENABLED: #pragma CHECKED_SCOPE on
// CHECK_DISABLED-NOT: utime_checked.h
// CHECK_DISABLED-NOT: #pragma CHECKED_SCOPE on
