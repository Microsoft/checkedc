//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in grp.h that                  //
// take pointer arguments.                                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

// The Windows environment may not have grp.h
#if defined __has_include_next && __has_include_next(<grp.h>)

#ifdef __checkedc
#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE off
#endif

#include_next <grp.h>

#ifdef __checkedc
#pragma CHECKED_SCOPE pop
#endif

#ifdef __checkedc
#ifndef __GRP_CHECKED_H
#define __GRP_CHECKED_H

#pragma CHECKED_SCOPE push
#pragma CHECKED_SCOPE on

int initgroups(const char *user : itype(_Nt_array_ptr<const char>), gid_t group);

#pragma CHECKED_SCOPE pop

#endif // guard
#endif // Checked C

#else // doesn't have grp.h
#error "cannot include 'grp_checked.h' because this system does not have the original 'grp.h'"
#endif
