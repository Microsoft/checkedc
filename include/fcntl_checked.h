//---------------------------------------------------------------------//
// Bounds-safe interfaces for some functions in fcntl.h that           //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <fcntl.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __FCNTL_CHECKED_H
#define __FCNTL_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

_Unchecked
int open(const char *pathname : itype(_Nt_array_ptr<const char>), int flags, ...);

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C
