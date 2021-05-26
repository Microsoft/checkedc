//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in syslog.h that               //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have syslog.h
#if defined __has_include_next && __has_include_next(<syslog.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <syslog.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __SYSLOG_CHECKED_H
#define __SYSLOG_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

// TODO: printing and scanning functions are still mostly
// unchecked because of the use of varargs.
// * There may not be enough arguments for the format string.
// * Any pointer arguments may not meet the requirements of the
//  format string.

void closelog(void);
void openlog (const char *__ident : itype(_Nt_array_ptr<const char>), int __option, int __facility);

// TODO: Is this condition right? I don't see any precedent in the Checked C
// system headers for __foo_chk without __builtin___foo_chk.
#if _FORTIFY_SOURCE == 0 || !defined(syslog)
#undef syslog
_Unchecked
void syslog(int priority, const char * format : itype(_Nt_array_ptr<const char>), ...);
#else
_Unchecked
void __syslog_chk(int priority, int flag, const char * format : itype(_Nt_array_ptr<const char>), ...);
#endif

/* TODO: Not sure how to get va_list included; stdio_checked.h might be the example to look at */
/* _Unchecked */
/* void vsyslog (int __pri, const char *__fmt  : itype(_Nt_array_ptr<const char>), va_list arg); */

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have syslog.h
#error "cannot include 'syslog_checked.h' because this system does not have the original 'syslog.h'"
#endif
