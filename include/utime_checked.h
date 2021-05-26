//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in utime.h that                //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have utime.h
#if defined __has_include_next && __has_include_next(<utime.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <utime.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __UTIME_CHECKED_H
#define __UTIME_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

extern int utime (const char *file : itype(_Nt_array_ptr<const char>),
                  const struct utimbuf *file_times : itype(_Ptr<const struct utimbuf>));

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have utime.h
#error "cannot include 'utime_checked.h' because this system does not have the original 'utime.h'"
#endif
