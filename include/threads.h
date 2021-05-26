//---------------------------------------------------------------------//
// Wrapper header file that excludes Checked-C-specific declarations   //
// if the compilation is not for Checked C, or if is for Checked C     //
// but the implicit inclusion of checked header files is disabled.     //
/////////////////////////////////////////////////////////////////////////


// C implementations may not support the C11 threads package or even the
// macro that says C11 threads are not supported.
#if defined __has_include_next && __has_include_next(<threads.h>)

#if !defined __checkedc || defined NO_IMPLICIT_INCLUDE_CHECKED_HDRS

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <threads.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#else // checkedc && implicit include enabled
#include <threads_checked.h>
#endif

#else // doesn't have threads.h
#error "cannot include 'threads.h' because this system does not have the original header, even though Checked C provides a wrapper for it"
#endif
